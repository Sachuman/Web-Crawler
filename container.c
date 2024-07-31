#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "container.h"


bag_t *bag_new(void) {
    bag_t *newBag = malloc(sizeof(bag_t));
    if (newBag == NULL) {
        fprintf(stderr, "Error try later!.\n");
        exit(EXIT_FAILURE);
    }
    newBag->head = NULL;
    return newBag;
}

void bag_insert(bag_t *pagesToCrawl, char *url, int depth) {
    webpage_t *newPage = malloc(sizeof(webpage_t));
    newPage->url = strdup(url);
    newPage->html = NULL;
    newPage->length = 0;
    newPage->depth = depth;
    bagnode_t *newNode = malloc(sizeof(bagnode_t));
    newNode->page = newPage;
    newNode->next = pagesToCrawl->head;
    pagesToCrawl->head = newNode;
}

int bag_contains(bag_t *pagesToCrawl, char *url) {
    bagnode_t *currentNode = pagesToCrawl->head;

    while (currentNode != NULL) {
        if (strcmp(currentNode->page->url, url) == 0) {
            return 1;
        }
        currentNode = currentNode->next;
    }

    return 0;
}



webpage_t *bag_ext(bag_t *pagesToCrawl) {
    if (pagesToCrawl->head == NULL) {
        return NULL; 
    }

    
    bagnode_t *currentNode = pagesToCrawl->head;
    pagesToCrawl->head = currentNode->next;

    webpage_t *currentPage = currentNode->page;
    free(currentNode);
    return currentPage;
}

int bag_empty(bag_t *pagesToCrawl) {
    return pagesToCrawl->head == NULL;
}

void bag_delete(bag_t *pagesToCrawl) {
    while (pagesToCrawl->head != NULL) {
        
        bagnode_t *currentNode = pagesToCrawl->head;
        pagesToCrawl->head = currentNode->next;
        free(currentNode->page->url);
        free(currentNode->page->html);
        free(currentNode->page);
        free(currentNode);
    }
    free(pagesToCrawl);
}
