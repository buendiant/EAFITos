#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"

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
