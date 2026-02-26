#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>  // size_t

/* =========================
 * Error handling
 * ========================= */
void eafitos_error(const char *contexto, const char *detalle);
void eafitos_perror(const char *contexto);
void eafitos_usage(const char *uso);

/* =========================
 * Helpers
 * ========================= */
int require_args(char **args, int required, const char *uso);
int parse_double(const char *s, double *out);
int str_is_empty(const char *s);
void trim_newline(char *s);

/* =========================
 * Memory manager
 * ========================= */
void *xmalloc(size_t n);
void *xrealloc(void *ptr, size_t n);
char *xstrdup(const char *s);

#endif
