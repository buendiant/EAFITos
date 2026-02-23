//Librerias
/**
 * @file file_commands.c
 * @brief Comandos que requieren la manipulacion de archivos.
 *
 * @copyright Copyright (c) 2026 EAFITOS.

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "commands.h"

/**
 * @brief Comando listar
 * 
 * Muestra una lista de archivos y directorios en el directorio actual.
 * 
 * @param args Argumentos del comando (en este caso no se requieren argumentos).
 */
void listOS(char **args) {
    DIR *d = opendir(".");      
    struct dirent *dir;
    char cwd[1024];

    if(getcwd(cwd, sizeof(cwd)) != NULL){
        printf("Directorio actual: %s\n", cwd);
    }
    if(d){
        printf("Archivos en el directorio actual:\n");

        while((dir=readdir(d)) != NULL){

            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                printf("  %s\n", dir->d_name);
            }        
        }

        closedir(d);
    }else{
        printf("No se pudo abrir el directorio actual\n");
    }
    (void) args;
}

/**
 * @brief Comando leer.
 * Permite abrir un archivo en modo lectura y muestra su contenido junto a la direccion del archivo, para que el usuario pueda verificar que se ha abierto el archivo correcto.
 * @param args Argumento del comando, args[1] obtiene nombre o la ruta del archivo a leer.
 * 
 */
void readOS(char **args){
    if(args[1]==NULL){
        printf("Error: Debes especificar un archivo para leer.\nDebe usarse del modo: leer <archivo>\n");
    }

    FILE *fp = fopen(args[1], "r");
    if(fp==NULL){
        printf("Error: No se pudo abrir el archivo %s\n", args[1]);
        return;
    }

    char c;
    while((c=fgetc(fp))!=EOF){
        putchar(c);
    }
    fclose(fp);

    printf("\n");
}