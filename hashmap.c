#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "newset.h"
#include "hashmap.h"



struct hashtableof{
    set_t **setarray;
    int thenumberpara;
};

hashtable_t* hashtable_new(const int num_slots){
    hashtable_t *hash_new = (hashtable_t*)malloc(sizeof(hashtable_t));
    if(hash_new == NULL){
        return NULL;
    }
    hash_new->thenumberpara = num_slots;
    hash_new->setarray = (set_t **)(malloc)(num_slots * sizeof(set_t *));
    if(hash_new->setarray == NULL){
        return NULL;
    }
    int i = 0;
    while (i < num_slots) {
        *(hash_new->setarray + i) = set_new();
        i++;
    }

    return hash_new;
};

bool hashtable_insert(hashtable_t *ht, const char *key){
    if (ht == NULL || key == NULL){
        return NULL;
    }
    else{
        int valv =  strlen(key) % ht->thenumberpara;
        return set_insert(ht->setarray[valv], key);

    }
};


void *hashtable_find(hashtable_t *ht, const char *key){

    if(ht == NULL || key == NULL){
        return NULL;
    }

    int valv = strlen(key) % ht->thenumberpara;
    return set_find(*(ht->setarray+valv), key);
};


// void hashtable_print(hashtable_t *ht, FILE *fp,
//                      void (*itemprint)(FILE *fp, const char *key, void *item)){
//         if (ht == NULL){
//             return;
//         }
//         else if (fp == NULL)
//         {
//             return;
//         }
//         else if(itemprint== NULL){
//             fprintf(fp, "()\n");
//             return;
//         }
//         else{
//             int i = 0;
//             while (i < ht->thenumberpara) {
//                 set_print(*(ht->setarray+i), fp, itemprint);
//                 i++;
//             }
//         }
//     };

// void hashtable_iterate(hashtable_t *ht, void *arg,
//                void (*itemfunc)(void *arg, const char *key, void *item) )
//     {
//         if (ht == NULL || itemfunc == NULL) {
//         return;
//     }
//     else{
//         int i = 0;
//         while (i < ht->thenumberpara) {
//             set_iterate(*(ht->setarray+i), arg, itemfunc);
//             i++;
//         }
//     }
// };


void hashtable_delete(hashtable_t *ht){
    if (ht == NULL){
        return;
    }
    else{
        int i = 0;
        while (i < ht->thenumberpara) {
            set_delete(*(ht->setarray+i));
            i++;
        }
    }
    free(ht->setarray);
    free(ht);
};


