#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>

struct hash_map{
  size_t (*hash)(void*);
  int (*cmp)(void*,void*);
  void (*key_destruct)(void*);
  void (*value_destruct)(void*);
  struct chain ** lists;
  int n_entries;
  int total_entries;
  int newTotal;
  pthread_mutex_t lock;

}; //Modify this!

struct chain{
  struct node* head;
  int num ;
};

struct node{
  void* key;
  void* value;
  struct node* next;
};


struct hash_map* hash_map_new(size_t (*hash)(void*), int (*cmp)(void*,void*),
    void (*key_destruct)(void*), void (*value_destruct)(void*));

void hash_map_put_entry_move(struct hash_map* map, void* k, void* v);

void hash_map_remove_entry(struct hash_map* map, void* k);

void* hash_map_get_value_ref(struct hash_map* map, void* k);

void hash_map_destroy(struct hash_map* map);

#endif
