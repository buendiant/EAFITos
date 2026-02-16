/**
 * @file shell_loop.c
 * @brief 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "commands.h"


char *nombreComandos[] = {
    "listar",
    "leer",
    "tiempo",
    "calc",
    "ayuda",
    "salir",
    "buscar",
    "estadisticas"

};

void (*funcionesComandos[])(char **) = {
    &listOS,
    &readOS,
    &timeOS,
    &calcOS,
    &helpOS,
    &exitOS,
    &buscarOS,
    &estadisticasOS

};

int numcom(){
    return sizeof(nombreComandos) / sizeof(char *);
}

void ejecutar(char **args){
    if((args[0])==NULL){
        return;
    }

    for(int i=0; i<numcom(); i++){
        if(strcmp(args[0], nombreComandos[i])==0){
            funcionesComandos[i](args);
            return;
        }
    }

    printf("Comando no reconocido: %s\n", args[0]);
}


void loop_shell(){
    char *line;
    char **args;
    int status = 1;
    do{
        printf("EAFITos>");

        line = readLine();
        args = parsear_linea(line);
        ejecutar(args);

        free(line);
        free(args);
    }while(status);
}