#ifndef CURL_WRAPPER_H
#define CURL_WRAPPER_H

#include <stddef.h>

char * download(const char *url, size_t *size_out);

#endif
