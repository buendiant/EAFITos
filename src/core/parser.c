
#include <stdio.h>  // Para getline, perror, fprintf, stdin
#include <stdlib.h> // Para malloc, realloc, free, exit
#include <string.h> // Para strtok
#include "shell.h"


char *readLine(void) {
    char *linea = NULL;
    size_t bufsize = 0; // getline asignará el buffer necesario
    ssize_t linelen = getline(&linea, &bufsize, stdin);
    if (linelen == -1) {
        perror("Error al leer la línea");
        exit(EXIT_FAILURE);
    }
    return linea;
}

char **parsear_linea(char *linea) {
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Error de asignación de memoria\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(linea, DELIM);
    while (token != NULL) {
        tokens[position++] = token;

        if (position >= bufsize) {
            bufsize *= 2;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Error de reasignación de memoria\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIM);
    }
    tokens[position] = NULL; // Termina el arreglo con NULL
    return tokens;
}