#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"
#include <pthread.h>
#include  <string.h>
#define INIT_BUCKETS 17


void putEntry(int idx, struct chain** lists, void* k,void* v){

    struct node* entry = malloc(sizeof(struct node));
    entry->key = k;
    entry->value = v;


    if(lists[idx] == 0){
        lists[idx] = malloc(sizeof(struct chain));
        lists[idx]->num = 0;
    }

    if(lists[idx]->num == 0){
      entry->next = NULL;
      lists[idx]->head = entry;
      lists[idx]->num ++;
    }
    else{
      entry->next = lists[idx]->head;
      lists[idx]->head = entry;
      lists[idx]->num ++;
    }

}

struct hash_map* hash_map_new(size_t (*hash)(void*), int (*cmp)(void*,void*),
    void (*key_destruct)(void*), void (*value_destruct)(void*)) {


  if(cmp == NULL || key_destruct == NULL || value_destruct == NULL || hash == NULL){
    return NULL;
  }

  struct hash_map* map = malloc(sizeof(struct hash_map));
  map->hash = hash;
  map->cmp =  cmp;
  map->key_destruct =  key_destruct;
  map->value_destruct =  value_destruct;
  map->lists = calloc(INIT_BUCKETS,sizeof(struct chain*));
  pthread_mutex_init(&(map->lock),NULL);
  map->n_entries = 0 ;
  map->total_entries = INIT_BUCKETS;
  map->newTotal = INIT_BUCKETS;

  return map;


}
/**
 * Puts an entry in the hashmap, associating a key with a value
 * If the key does not exists, a new entry should be created and the key
 * and value assumed to be owned by the hash map.
 * If an entry exists, old entry should be removed (hash_map_remove_entry).
 */
void hash_map_put_entry_move(struct hash_map* map, void* k, void* v) {
  pthread_mutex_lock(&(map->lock));
  if(map == NULL){
      pthread_mutex_unlock(&(map->lock));
    return;
  }

    size_t key = map->hash(k);
    size_t idx = key%map->total_entries;

    if(map->lists[idx] !=0){
      struct node * temp = map->lists[idx]->head;
      int a = 0;
      struct node* prev = NULL;
      while(temp!=NULL){
        if(map->cmp(k,temp->key) == 1){
          if(a == 0){
            map->lists[idx]->head = temp->next;
            map->key_destruct(temp->key);
            map->value_destruct(temp->value);
            free(temp);
            map->lists[idx]->num--;
            break;
          }
          else{
            prev->next = temp->next;
            map->key_destruct(temp->key);
            map->value_destruct(temp->value);
            free(temp);
            map->lists[idx]->num--;
            break;
          }
        }
        prev = temp;
        a++;
        temp = temp->next;
      }
    }


    struct node* entry = malloc(sizeof(struct node));
    entry->key = k;
    entry->value = v;


    if(map->lists[idx] == 0){

      if(map->lists[idx] == 0){
        map->lists[idx] = malloc(sizeof(struct chain));

        // pthread_mutex_lock(&(map->lists[idx]->lock));
        map->lists[idx]->num = 0;
      }

    }
    // else{
    //       pthread_mutex_lock(&(map->lists[idx]->lock));
    // }


    if(map->lists[idx]->num == 0){
      entry->next = NULL;
      map->n_entries ++;
      map->lists[idx]->head = entry;
      map->lists[idx]->num ++;
    }
    else{
      entry->next = map->lists[idx]->head;
      map->lists[idx]->head = entry;
      map->n_entries ++;
      map->lists[idx]->num ++;
    }

        // pthread_mutex_unlock(&(map->lists[idx]->lock));




    if(map->n_entries >= (map->total_entries/4)*3){


     if(map->n_entries >= (map->total_entries/4)*3){

     map->newTotal = map->total_entries*4;

     struct chain** new = calloc(map->newTotal,sizeof(struct chain*));

     int total = map->total_entries;

     // pthread_mutex_lock(&(map->lock));


     for(int i = 0 ; i < total; i++){
       if(map->lists[i]!=0){
         // pthread_mutex_lock(&(map->lists[i]->lock));
         struct node * a = map->lists[i]->head;
         while(a!=NULL){
           size_t keys = map->hash(a->key);
           size_t index = keys%map->newTotal;
           putEntry(index,new,a->key,a->value);
           a = a->next;
         }

       }
     }



     map->total_entries = map->newTotal;


     // for(int i = 0 ; i < total; i++){
     //   if(map->lists[i]!=0){
     //    pthread_mutex_unlock(&(map->lists[i]->lock));
     //  }
     // }

     struct chain** old  = map->lists;
     map->lists = new;


     // pthread_mutex_unlock(&(map->lock));

     for(int i = 0 ; i < total; i++){
       if(old[i]!=0){
         struct node * a = old[i]->head;
         while(a!=NULL){
           struct node* next = a->next;
           free(a);
           a = next;
         }

         free(old[i]);
       }
     }

     free(old);
}


   }

   pthread_mutex_unlock(&(map->lock));
}

void hash_map_remove_entry(struct hash_map* map, void* k) {
  pthread_mutex_lock(&(map->lock));
  size_t key = map->hash(k);
  size_t idx = key%map->total_entries;


      if(map->lists[idx] !=0){
        struct node * temp = map->lists[idx]->head;
        int a = 0;
        struct node* prev = NULL;
        while(temp!=NULL){
          if(map->cmp(k,temp->key) == 1){
            if(a == 0){
              map->lists[idx]->head = temp->next;
              map->key_destruct(temp->key);
              map->value_destruct(temp->value);
              free(temp);
              map->lists[idx]->num--;
                pthread_mutex_unlock(&(map->lock));
              return;
            }
            else{
              prev->next = temp->next;
              map->key_destruct(temp->key);
              map->value_destruct(temp->value);
              free(temp);
              map->lists[idx]->num--;
          pthread_mutex_unlock(&(map->lock));
              return;
            }
          }
          prev = temp;
          a++;
          temp = temp->next;
        }
      }

  pthread_mutex_unlock(&(map->lock));

}

void* hash_map_get_value_ref(struct hash_map* map, void* k) {
  pthread_mutex_lock(&(map->lock));

  size_t key = map->hash(k);
  size_t idx = key%map->total_entries;

  if(map == NULL){
      pthread_mutex_unlock(&(map->lock));
    return NULL;
  }

  if(map->lists[idx] !=0){



    struct node * temp = map->lists[idx]->head;
    while(temp!=NULL){
      if(map->cmp(temp->key,k)==1){
        pthread_mutex_unlock(&(map->lock));
        return temp->value;
      }
      temp = temp->next;
    }
    pthread_mutex_unlock(&(map->lock));
    return NULL;
  }
  else{
    pthread_mutex_unlock(&(map->lock));
    return NULL;
  }


}

void hash_map_destroy(struct hash_map* map) {

  if(map ==NULL){
    return;
  }

  if(map->n_entries != 0){

    for(int i = 0 ; i < map->total_entries ; i ++){
      if(map->lists[i] != 0){
        struct node * temp = map->lists[i]->head;
        while(temp!=NULL){
          struct node * next = temp->next;
          map->key_destruct(temp->key);
          map->value_destruct(temp->value);
          free(temp);
          temp = next;
        }
        free(map->lists[i]);
      }
    }


  }

  free(map->lists);
  free(map);
}
