/**
 * @file parser.c
 * @brief Implementación de funciones para leer y parsear la línea de comandos en el shell de EAFITos.
 * 
 * @copyright Copyright (c) 2026 EAFITOS.
 * 
 */

#include <stdio.h>  // Para getline, perror, fprintf, stdin
#include <stdlib.h> // Para malloc, realloc, free, exit
#include <string.h> // Para strtok
#include "shell.h"

/**
 * @brief Lee la línea de comando ingresada por el usuario.
 * Esta función utiliza getline para leer una línea completa de entrada desde stdin, asignando dinámicamente el buffer necesario para almacenar la línea. 
 * Si ocurre un error al leer la línea, se muestra un mensaje de error y se termina la ejecución del programa.
 * 
 * @return char* 
 */
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

/**
 * @brief Parsea una línea de comandos en tokens separados por delimitadores.
 * Esta función toma una línea de comandos como entrada y la divide en tokens separados por delimitadores definidos en `DELIM`. 
 * Los tokens se almacenan en un arreglo dinámico de cadenas de caracteres, que es devuelto por la función.
 * 
 * @param linea El parametro ingresado por el usuario.
 * @return char**  Un arreglo de cadenas de caracteres que contiene los tokens separados. 
 */
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