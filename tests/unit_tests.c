#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

static void test_parsear_linea_separa_tokens(void) {
    char entrada[] = "ls -la /tmp\n";

    char **tokens = parsear_linea(entrada);

    assert(tokens != NULL);
    assert(tokens[0] != NULL && strcmp(tokens[0], "ls") == 0);
    assert(tokens[1] != NULL && strcmp(tokens[1], "-la") == 0);
    assert(tokens[2] != NULL && strcmp(tokens[2], "/tmp") == 0);
    assert(tokens[3] == NULL);

    free(tokens);
}

static void test_parsear_linea_vacia_retorna_solo_null(void) {
    char entrada[] = "   \t\n";

    char **tokens = parsear_linea(entrada);

    assert(tokens != NULL);
    assert(tokens[0] == NULL);

    free(tokens);
}

int main(void) {
    test_parsear_linea_separa_tokens();
    test_parsear_linea_vacia_retorna_solo_null();

    printf("[OK] Unit tests completadas.\n");
    return EXIT_SUCCESS;
}