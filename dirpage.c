#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "container.h"
#include "dirpage.h"

#define CRAWLER_FILE ".crawler"


bool pagedir_init(const char *pageDirectory) {

	char findcrawler[strlen(pageDirectory) + strlen(CRAWLER_FILE) + 2];
    sprintf(findcrawler, "%s/%s", pageDirectory, CRAWLER_FILE);

    FILE *filecrawler = fopen(findcrawler, "w");
    if(filecrawler == NULL){
		fprintf(stderr, "Error");
		exit(1);

    }

	fclose(filecrawler);
    return true;


}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {

	char findingfile[strlen(pageDirectory) + 12];
	sprintf(findingfile, "%s/%d", pageDirectory, documentID);

	FILE *thefile = fopen(findingfile, "w");
	if(thefile == NULL){
		fprintf(stderr, "Error");
		exit(1);
	}

	fprintf(thefile, "%s\n", page->url);
    fprintf(thefile, "%d\n", page->depth);
	fwrite(page->html, sizeof(char), page->length, thefile);
	fclose(thefile);

}
