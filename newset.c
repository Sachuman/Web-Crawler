#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "newset.h"


typedef struct View View;


struct View {
    char *key;
    View *next;
};


struct setof {
    View *head;
};



set_t* set_new(void){

    set_t *new_set = (set_t *)malloc(sizeof(set_t));
    if (new_set == NULL) {
        return NULL;
    }
    (*new_set).head = NULL;
    return new_set;


};

bool set_insert(set_t *set, const char *key){
    if(set ==NULL || key == NULL){
        return false;
    }

    else{
        View *present = set->head;
        while(present!= NULL){
            if(strcmp(present->key, key) == 0){
                return false;
            }

            present = present->next;
        }

        View *newNode = (View *)malloc(sizeof(View));
        
        newNode->key = (char *)malloc(strlen(key) + 1);
        
        strcpy(newNode->key, key);

        newNode->next = set->head;
        set->head = newNode;

        return true;

    }

    
};

void *set_find(set_t *set, const char *key){
    if(set == NULL || key == NULL){
        return NULL;
    }
    else{
        View *present = set->head;
        while (present != NULL) {
            if (strcmp(present->key, key) == 0) {
                return present->key;
            }
            present = present->next;
        }

    return NULL;
}

};

// void set_print(set_t *set, FILE *fp,
//             void (*itemprint)(FILE *fp, const char *key, void *item) )
//     {
//         if (set == NULL){
//             fprintf(fp, "(null)\n");
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
//             View *present = set->head;
       
//             for(; present != NULL; present = present->next){
//                 itemprint(fp, present->key, present->item);
//             }
        
//         }
        
//     };

// void set_iterate(set_t *set, void *arg,
//                 void (*itemfunc)(void *arg, const char *key, void *item) )
//     {
//     if (set == NULL || itemfunc == NULL) {
//         return;
//     }
//     else{
//         View *present = set->head;
//         while (present != NULL) {
//             itemfunc(arg, present->key, present->item);
//             present = present->next;
//         }
//     }

// };

void set_delete(set_t *set)
{
    if (set == NULL) {
        return;
    }

    View *present = set->head;
    while (present != NULL) {
        View *next = present->next;

        free(present->key);
        free(present);
        present = next;
    }

    free(set);

};