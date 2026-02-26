#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "utils.h"

void eafitos_error(const char *contexto, const char *detalle) {
    if (contexto && detalle) {
        fprintf(stderr, "Error (%s): %s\n", contexto, detalle);
    } else if (contexto) {
        fprintf(stderr, "Error: %s\n", contexto);
    } else {
        fprintf(stderr, "Error desconocido.\n");
    }
}

void eafitos_perror(const char *contexto) {
    if (contexto) {
        fprintf(stderr, "Error (%s): %s\n", contexto, strerror(errno));
    } else {
        fprintf(stderr, "Error del sistema: %s\n", strerror(errno));
    }
}

void eafitos_usage(const char *uso) {
    if (uso) {
        fprintf(stderr, "Uso: %s\n", uso);
    }
}
