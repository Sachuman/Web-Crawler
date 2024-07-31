#ifndef HASH_H_
#define HASH_H_

#include <stdbool.h>

typedef struct hashtableof hashtable_t;

hashtable_t *hashtable_new(const int num_slots);


bool hashtable_insert(hashtable_t *ht, const char *key);


void *hashtable_find(hashtable_t *ht, const char *key);


void hashtable_delete(hashtable_t *ht);


#endif 
