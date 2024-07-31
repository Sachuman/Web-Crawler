#ifndef BAG_H
#define BAG_H

#include <stdbool.h>  
#include "webcrawler.h"  


bag_t *bag_new(void);
int bag_contains(bag_t *pagesToCrawl, char *url);
void bag_insert(bag_t *pagesToCrawl, char *url, int depth);

webpage_t *bag_ext(bag_t *pagesToCrawl);

int bag_empty(bag_t *pagesToCrawl);

void bag_delete(bag_t *pagesToCrawl);

#endif
