#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "utils.h"

int require_args(char **args, int required, const char *uso) {
    if (!args) {
        eafitos_error("argumentos", "args es NULL");
        if (uso) eafitos_usage(uso);
        return 0;
    }

    for (int i = 1; i <= required; i++) {
        if (args[i] == NULL) {
            eafitos_error("argumentos", "faltan argumentos requeridos");
            if (uso) eafitos_usage(uso);
            return 0;
        }
    }
    return 1;
}

int parse_double(const char *s, double *out) {
    if (!s || !out) return 0;

    errno = 0;
    char *endptr = NULL;
    double value = strtod(s, &endptr);

    if (s == endptr) return 0;          // no parseó nada
    if (errno != 0) return 0;           // overflow/underflow
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) return 0;
        endptr++;
    }

    *out = value;
    return 1;
}

int str_is_empty(const char *s) {
    if (!s) return 1;
    while (*s) {
        if (!isspace((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

void trim_newline(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}
