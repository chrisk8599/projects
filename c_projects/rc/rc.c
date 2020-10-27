
#include "rc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static struct strong_ref** list;
static size_t counter = 0;
static size_t done = 0;

/**
 * Returns an allocation of n bytes and creates an internal rc entry.
 *
 * If the ptr argument is NULL and deps is NULL, it will return a new
 * allocation
 *
 * If the ptr argument is not NULL and an entry exists, it will increment
 *  the reference count of the allocation and return a strong_ref pointer
 *
 * If the ptr argument is NULL and deps is not NULL, it will return
 * a new allocation but the count will correlate to the dependency
 * if the dependency is deallocated the reference count on the object will
 * decrement
 *
 * If the ptr argument is not NULL and an entry exists and dep is not
 * NULL, it will increment the count of the strong reference but the count
 * will be related to the dependency, if the dependency is deallocated the
 * reference count on the object will decrement
 */
 struct strong_ref* rc_alloc(void* ptr, size_t n, struct strong_ref* dep) {
 	if(ptr == NULL && dep == NULL){
 		struct strong_ref* ref = malloc(sizeof(struct strong_ref));
 		 ref->ptr = malloc(n);
     ref->entry.count =1 ;
		 ref->entry.n_deps = 0 ;
		 ref->entry.dep_capacity=0;
		 ref->entry.dep_list = NULL;
		  counter++;
			if(counter == 1){
				list = malloc(sizeof(struct strong_ref*));
        list[counter -1 ] = malloc(sizeof(struct strong_ref));
			}
			else{
				list = realloc(list,sizeof(struct strong_ref*)* counter);
        list[counter -1 ] = malloc(sizeof(struct strong_ref));
			}

			memcpy(list[counter -1 ], ref,sizeof(struct strong_ref));

			free(ref);
 		return list[counter-1];
 	}

 	else if(ptr!=NULL && dep==NULL){
 		for(size_t i = 0 ; i < counter ; i++){
 			if (list[i]->ptr == ptr){
 				list[i]->entry.count++;
        return list[i];
 			}
 		}
 	}

	else if(ptr==NULL && dep!=NULL){

				for(size_t i = 0 ; i < counter ; i++){
		 			if (list[i]->ptr == dep->ptr) {
		 				struct strong_ref* ref = malloc(sizeof(struct strong_ref));

						ref->ptr = malloc(n);
		        ref->entry.n_deps = 0 ;
						ref->entry.dep_capacity = 0;
		   		  ref->entry.dep_list = NULL;
						ref->entry.count = list[i]->entry.count;
            //


						if(list[i]->entry.dep_capacity==0){
							list[i]->entry.dep_list = malloc(sizeof(size_t)*(list[i]->entry.dep_capacity+1));
						}

						else{
							list[i]->entry.dep_list = realloc(	list[i]->entry.dep_list, sizeof(size_t)*(list[i]->entry.dep_capacity+1));
						}




						list[i]->entry.dep_list[list[i]->entry.dep_capacity] = counter;

						list[i]->entry.n_deps ++ ;
						list[i]->entry.dep_capacity ++ ;

						counter++;

						list = realloc(list,sizeof(struct strong_ref*)* counter);

            list[counter -1 ] = malloc(sizeof(struct strong_ref));


						memcpy(list[counter -1 ], ref,sizeof(struct strong_ref));

            free(ref);


			 			return list[counter-1];
		 			}
		 		}
	}

	else if(ptr!=NULL && dep!=NULL){

		for(size_t i = 0 ; i < counter ; i++){
			if (list[i]->ptr == ptr){

				list[i]->entry.count++;

        dep->entry.n_deps++;

        list[i]->entry.n_deps++;

				return list[i];
			}
		}
	}

   return NULL;
 }


/**
 * Downgrades a strong reference to a weak reference, this will decrement the
 * reference count by 1
 * If ref is NULL, the function will return an invalid weak ref object
 * If ref is a value that does not exist in the reference graph, it will return
 * an weak_ref object that is invalid
 *
 * If ref is a value that does exist in the reference graph, it will return
 *    a valid weak_ref object
 *
 * An invalid weak_ref object is where its entry_id field is set to
 *   0xFFFFFFFFFFFFFFFF
 *
 * @param strong_ref* ref (reference to allocation)
 * @return weak_ref (reference with an entry id)
 */
struct weak_ref rc_downgrade(struct strong_ref* ref) {
struct weak_ref r = { 0xFFFFFFFFFFFFFFFF };




	if(ref == NULL){
			return r;
	}
  else if(ref->entry.count == 0 ){
    return r;
  }
  else if(ref->entry.n_deps > ref->entry.dep_capacity){

    for(size_t i = 0 ; i < counter ; i ++){
      if(memcmp(ref,list[i],sizeof(struct strong_ref)) == 0){
        list[i]->entry.count -- ;

        if(list[i]->entry.count == 0){

          if(list[i]->entry.dep_capacity > 0 ){
            for(size_t j =0 ; j < list[i]->entry.dep_capacity;j++ ){
              list[list[i]->entry.dep_list[j]]->entry.count--;
            }
          }
          return r;
        }
        else{
          if(list[i]->entry.dep_capacity > 0 ){
            for(size_t j =0 ; j < list[i]->entry.dep_capacity;j++ ){
              list[list[i]->entry.dep_list[j]]->entry.count--;
            }
          }
        }
         struct weak_ref a = {i};
         return a;
      }
    }
	}

  else{
    for(size_t i = 0 ; i < counter ; i ++){
      if(memcmp(ref,list[i],sizeof(struct strong_ref)) == 0){
        list[i]->entry.count -- ;

        if(list[i]->entry.count == 0){

          if(list[i]->entry.dep_capacity > 0 ){
						for(size_t j =0 ; j < list[i]->entry.dep_capacity;j++ ){
							list[list[i]->entry.dep_list[j]]->entry.count--;
						}
          }
					return r;
        }
				else{
					if(list[i]->entry.dep_capacity > 0 ){
						for(size_t j =0 ; j < list[i]->entry.dep_capacity;j++ ){
							list[list[i]->entry.dep_list[j]]->entry.count--;
						}
          }
				}

         struct weak_ref a = {i};
         return a;
      }
    }
  }

return r;


}


/**
 * Upgrdes a weak reference to a strong reference.
 * The weak reference should check that the entry id is valid (bounds check)
 * If a strong reference no longer exists or has been deallocated, the return
 *   result should be null.
 */
 struct strong_ref* rc_upgrade(struct weak_ref ref) {

	if(done ==1){
		return NULL;
	}

 	if(ref.entry_id >= counter || ref.entry_id<0 || ref.entry_id == 0xFFFFFFFFFFFFFFFF){
 		return NULL;
 	}
 	else if(list[ref.entry_id]->entry.count ==0){

 		return NULL;

 	}
  else {
		list[ref.entry_id]->entry.count++;
    return list[ref.entry_id];
  }


 }


/**
 * Cleans up the reference counting graph.
 */
void rc_cleanup() {



	for(size_t i = counter-1 ; i >=0 ; i--){

		free(list[i]->ptr);
    if(list[i]->entry.dep_capacity >0){
      free(list[i]->entry.dep_list);
    }
    free(list[i]);

    if(i==0){
      break;

    }
	}

	done =1;
	free(list);

}
