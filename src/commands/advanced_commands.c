/**
 * @file advanced_commands.c
 * @brief Comandos avanzados (archivos): buscar y estadisticas.
 * 
 * @copyright Copyright (c) 2026 EAFITOS.

 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h> 

#include "commands.h"

/**
 * @brief Buscar un texto dentro de un archivo.
 * Permite al usuario buscar un texto específico dentro de un archivo, mostrando las líneas donde se encuentra el texto junto con el número de línea.
 * Esto se hace del modo: buscar <texto> <archivo>.
 * 
 * Se logra mediante la apertura del archivo en modo lectura, la lectura línea por línea y la búsqueda del texto utilizando strstr.
 * Primero se verifica que el usuario haya ingresado correctamente los 2 argumentos requeridos y la direccion del archivo sea correcta.
 * De ser así, se muestra cada línea que contiene el texto buscado junto con su número de línea, y al finalizar se muestra el número total de coincidencias encontradas.
 * 
 * @param args Argumentos del comando, donde args[1] es el texto a buscar y args[2] es el nombre o ruta del archivo donde se realizará la búsqueda.
 * 
 */
void searchOS(char **args) {
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
/**
 * @brief Mostrar estadísticas de un archivo (Comando avanzado de Archivo).
 * Permite al usuario obtener estadísticas básicas de un archivo, como el número de bytes, líneas y palabras que contiene.
 * Esto se hace del modo: estadisticas <archivo>. Donde archivo puede ser la ruta o el nombre del archivo del cual se quieren obtener las estadísticas.
 * Primero se verifica que el usuario haya ingresado un archivo o ruta existente, luego se obtiene el tamaño del archivo utilizando stat() y se cuentan las líneas, palabras y caracteres leyendo el archivo carácter por carácter.
 * 
 * @param args Argumentos del comando, donde args[1] es el nombre o ruta del archivo del cual se mostrarán las estadísticas.
 */
void statisticsOS(char **args) {
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
/**
 * @brief Renombrar un archivo (Comando avanzado de Archivo).
 * Permite al usuario cambiar el nombre de un archivo existente a un nuevo nombre especificado. 
 * Esto se hace del modo: renombrar <viejo> <nuevo>, donde "viejo" es el nombre actual del archivo y "nuevo" es el nuevo nombre que se desea asignar al archivo.
 * Para esto se verifica primero que el usuario haya ingresado ambos argumentos necesarios, luego se utiliza la función rename() para cambiar el nombre del archivo. Si la operación es exitosa, se muestra un mensaje de confirmación; de lo contrario, se muestra un mensaje de error.
 * @param args 
 */
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

/**
 * @brief Mover la ubicacion de un archivo (Comando avanzado de Archivo).
 * Permite al usuario mover un archivo de una ubicación a otra dentro del sistema de archivos. Esto se hace del modo: mover <origen> <destino>, donde "origen" es la ruta actual del archivo y "destino" es la nueva ruta a la que se desea mover el archivo.
 * Para esto se verifica que el usuario haya ingresado correctamente las rutas de origen y destino, luego se utiliza la función rename() para mover el archivo. 
 * Si la operación es exitosa, se muestra un mensaje de confirmación; de lo contrario, se muestra un mensaje de error.
 * @param args Argumentos del comando, donde args[1] o ruta del archivo a mover y args[2] es la nueva ubicación.
 */
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

/**
 * @brief Limpiar la pantalla (Comando Avanzado del Sistema).
 * Permite al usuario eliminar la informacion vista en pantalla para tener una vista limpia.
 * Esto se logra mediante el uso de secuencias de escape ANSI para limpiar la pantalla y mover el cursor a la posición inicial.
 * 
 * @param args Argumentos del comando (en este caso no se requieren argumentos).
 */
void cleanOS(char **args){
    printf("\033[H\033[J");
    (void) args;
}
/**
 * @brief Mostrar el directorio actual (Comando Avanzado del Sistema).
 * Permite al usuario ver la ruta del directorio actual en el que se encuentra trabajando dentro del sistema de archivos.
 * Esto se logra utilizando la función getcwd() para obtener la ruta del directorio actual y mostrarla al usuario. 
 * Si ocurre un error al obtener el directorio, se muestra un mensaje de error.
 * 
 * @param args Argumentos del comando (en este caso no se requieren argumentos).
 */
void dirOS(char **args){
    char ruta[PATH_MAX]; 
    if (getcwd(ruta, sizeof(ruta)) != NULL) {
        printf("Directorio actual: %s\n", ruta);
    } else {
        perror("Error al obtener el directorio");
    }
    (void) args;
}