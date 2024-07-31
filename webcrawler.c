#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "container.h"
#include "hashmap.h"
#include "webcrawler.h"
#include "libcurl.h"
#include "fetchurls.h"
#include "dirpage.h"

static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth);
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth);
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);

int main(const int argc, char *argv[]) {
    char *seedURL;
    char *pageDirectory;
    int maxDepth;
    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);

    pagedir_init(pageDirectory);

    crawl(seedURL, pageDirectory, maxDepth);

    free(seedURL);
    free(pageDirectory);

    return 0;
}

static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
    if (argc != 4) {
        fprintf(stderr, "Error  %s  in seedURL or pageDirectory or maxDepth\n", argv[0]);
        exit(1);
    }

    *seedURL = strdup(argv[1]);
    *pageDirectory = strdup(argv[2]);
    *maxDepth = atoi(argv[3]);

    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "Error: Invalid.\n");
        exit(1);
    }
}

static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {

    hashtable_t *pagesSeen = hashtable_new(1000);
    hashtable_insert(pagesSeen, seedURL);
    bag_t *pagesToCrawl = bag_new();
    int documentID = 1;

    webpage_t *seedPage = malloc(sizeof(webpage_t));
    seedPage->url = strdup(seedURL);
    seedPage->depth = 0;
    seedPage->html = NULL;
    seedPage->length = 0;

    bag_insert(pagesToCrawl, seedPage->url, seedPage->depth);
    
    free(seedPage->url);
    free(seedPage->html);
    free(seedPage);

    while (!bag_empty(pagesToCrawl)) {
        webpage_t *currentPage = bag_ext(pagesToCrawl);

        printf("%d   Fetched: %s\n", currentPage->depth, currentPage->url);

        printf("%d   Scanning: %s\n", currentPage->depth, currentPage->url);

        sleep(1);

        currentPage->html = download(currentPage->url, &(currentPage->length));

        if (currentPage->html != NULL) {
            pagedir_save(currentPage, pageDirectory, documentID++);

            if (currentPage->depth < maxDepth) {
                pageScan(currentPage, pagesToCrawl, pagesSeen);
            }
        }
        else{
            fprintf(stderr, "Invalid URL\n");
            exit(1);
        }

        free(currentPage->url);
        free(currentPage->html);
        free(currentPage);

    }
   
    hashtable_delete(pagesSeen);
    bag_delete(pagesToCrawl);
}

void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {

    char *html = page->html;
    char *url = page->url;

    while (1) {

        char *beginlink = strstr(html, "<a");
        if (beginlink == NULL) {
            break;  
        }

        
        char *beginhref = strstr(beginlink, "href=");
        if (beginhref == NULL) {
            
            html = beginlink + 2;
            continue;
        }

        beginhref += strcspn(beginhref, "\"'"); 
        beginhref += strspn(beginhref, "\"'");  

        char *endthelink = strpbrk(beginhref, "\"'");
        if (endthelink == NULL) {
            break; 
        }


        size_t urlLength = endthelink - beginhref;
        char *Iextractedtheurls = strndup(beginhref, urlLength);

        if (strchr(Iextractedtheurls, '#') != NULL) {
            free(Iextractedtheurls);
            html = endthelink + 1;
            continue;
        }
        
        char *Inormalization = normalizeURL(url, Iextractedtheurls);

        
        if (Inormalization != NULL && isInternalURL(url, Inormalization) && Inormalization[0] != '#' && Inormalization[strlen(Inormalization) - 1] != '#') {
            
            if (hashtable_insert(pagesSeen, Inormalization)) {
                printf("%d      Found: %s\n", page->depth + 1, Inormalization);

                
                webpage_t *newPage = malloc(sizeof(webpage_t));
                newPage->url = Inormalization;
                newPage->depth = page->depth + 1;
                newPage->html = NULL; 
                newPage->length = 0;

                
                bag_insert(pagesToCrawl, newPage->url, newPage->depth);
                printf("%d      Added: %s\n", page->depth + 1, Inormalization);
                free(newPage->url);
                free(newPage->html);
                free(newPage);

            } else {
                printf("%d      Found: %s\n", page->depth + 1, Inormalization);
                printf("%d      IgnDupl: %s\n", page->depth + 1, Inormalization);
                free(Inormalization); 
            }
        } else {
            printf("%d      Found: %s\n", page->depth + 1, Inormalization);
            printf("%d   IgnExtrn: %s\n", page->depth + 1, Inormalization);
            free(Inormalization); 
        }

        free(Iextractedtheurls); 

        html = endthelink + 1;
    }
}
