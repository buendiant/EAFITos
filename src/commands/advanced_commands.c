/**
 * @file advanced_commands.c
 * @brief Comandos avanzados (archivos): buscar y estadisticas.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h> 
#include <pwd.h>
#include <sys/types.h>

#include "commands.h"


/**
 * @brief Comando buscar
 * Este archivo
 * 
 * @param args 
 */
void buscarOS(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Uso: buscar <texto> <archivo>\n");
        return;
    }

    const char *texto = args[1];
    const char *archivo = args[2];

    FILE *f = fopen(archivo, "r");
    if (!f) {
        perror("buscar: fopen");
        return;
    }

    char line[4096];
    long linea = 0;
    long coincidencias = 0;

    while (fgets(line, sizeof(line), f)) {
        linea++;

        // Coincidencia simple (case-sensitive)
        if (strstr(line, texto) != NULL) {
            coincidencias++;
            printf("linea %ld: %s", linea, line);

            // Si la línea no trae '\n', lo añadimos para que se vea bien
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] != '\n') {
                printf("\n");
            }
        }
    }

    printf("Coincidencias: %ld\n", coincidencias);
    fclose(f);
}

// =============================
// estadisticas <archivo>
// =============================
void estadisticasOS(char **args) {
    // args[0] = "estadisticas"
    // args[1] = archivo
    if (args[1] == NULL) {
        printf("Uso: estadisticas <archivo>\n");
        return;
    }

    const char *archivo = args[1];

    // Bytes con stat()
    struct stat st;
    if (stat(archivo, &st) != 0) {
        perror("estadisticas: stat");
        return;
    }

    FILE *f = fopen(archivo, "r");
    if (!f) {
        perror("estadisticas: fopen");
        return;
    }

    long lineas = 0;
    long palabras = 0;
    long caracteres = 0;

    int c;
    int in_word = 0;
    int saw_any = 0;
    int last = 0;

    while ((c = fgetc(f)) != EOF) {
        saw_any = 1;
        caracteres++;
        last = c;

        if (c == '\n') {
            lineas++;
        }

        if (isspace((unsigned char)c)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            palabras++;
        }
    }

    // Si el archivo tuvo contenido y no terminó en '\n', cuenta la última línea
    if (saw_any && last != '\n') {
        lineas++;
    }

    fclose(f);

    printf("Archivo: %s\n", archivo);
    printf("Bytes: %lld\n", (long long)st.st_size);
    printf("Lineas: %ld\n", lineas);
    printf("Palabras: %ld\n", palabras);
    printf("Caracteres leidos: %ld\n", caracteres);
}

void renameOS(char **args){

    if(args[1]==NULL || args[2]==NULL){
        printf("Uso: renombrar <viejo> <nuevo>\n");
        return;
    }

    if(rename(args[1], args[2]) != 0){
        printf("Error: No se pudo renombrar el archivo.\n");
        return;
    }

    printf("Archivo renombrado correctamente.\n");
}

void moveOS(char **args){

    if(args[1]==NULL || args[2]==NULL){
        printf("Uso: mover <origen> <destino>\n");
        return;
    }

    if(rename(args[1], args[2]) != 0){
        printf("Error: No se pudo mover el archivo.\n");
        return;
    }

    printf("Archivo movido correctamente.\n");
}

void cleanOS(char **args){
    printf("\033[H\033[J");
    (void) args;
}

void dirOS(char **args){
    char ruta[PATH_MAX]; 
    if (getcwd(ruta, sizeof(ruta)) != NULL) {
        printf("Directorio actual: %s\n", ruta);
    } else {
        perror("Error al obtener el directorio");
    }
    (void) args;
}

void usuarioOS(char **args) {

    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL) {
        perror("Error obteniendo información del usuario");
        return;
    }

    printf("Información del usuario:\n");
    printf("Nombre: %s\n", pw->pw_name);
    printf("UID: %d\n", pw->pw_uid);
    printf("GID: %d\n", pw->pw_gid);
    printf("Directorio Home: %s\n", pw->pw_dir);
}
