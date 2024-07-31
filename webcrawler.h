#ifndef CRAWLER_H
#define CRAWLER_H

#include <stddef.h>
#include "hashmap.h"
#include "container.h"

typedef struct {
	char *url;
	char *html;
	size_t length;
	int depth;
} webpage_t;


typedef struct bagnode {
    webpage_t *page;
    struct bagnode *next;
} bagnode_t;

typedef struct {
    bagnode_t *head;
} bag_t;




#endif
