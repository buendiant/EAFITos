#include <stdlib.h>
#include <string.h>
#include "utils.h"

void *xmalloc(size_t n) {
    if (n == 0) n = 1;
    void *ptr = malloc(n);
    if (!ptr) {
        eafitos_error("memoria", "malloc falló");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *xrealloc(void *ptr, size_t n) {
    if (n == 0) n = 1;
    void *new_ptr = realloc(ptr, n);
    if (!new_ptr) {
        eafitos_error("memoria", "realloc falló");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

char *xstrdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *copy = (char *)xmalloc(len);
    memcpy(copy, s, len);
    return copy;
}
