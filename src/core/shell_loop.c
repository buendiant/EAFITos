/**
 * @file shell_loop.c
 * @brief Implementación del bucle principal del shell de EAFITos.
 * 
 * @copyright Copyright (c) 2026 EAFITOS.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "commands.h"

/**
 * @brief Arreglo de nombres de comandos.
 * Esto permite identifdicar el comando ingresado por el usuario y ejecutar la función correspondiente.
 */
char *nombreComandos[] = {
    "listar",
    "leer",
    "tiempo",
    "calc",
    "ayuda",
    "buscar",
    "estadisticas",
    "renombrar",
    "mover",
    "directorio",
    "limpiar",
    "salir"
};

/**
 * @brief Arreglo de funciones de comandos.
 * Este arreglo contiene punteros a las funciones que implementan cada comando, permitiendo ejecutarlos correctamente cuando el usuario los ingresa gracias a estar indexados en el mismo orden que los nombres de comandos.
 */
void (*funcionesComandos[])(char **) = {
    &listOS,
    &readOS,
    &timeOS,
    &calcOS,
    &helpOS,
    &searchOS,
    &statisticsOS,
    &renameOS,
    &moveOS,
    &dirOS,
    &cleanOS,
    &exitOS
};

/**
 * @brief NumCom 
 * Retorna el número de comandos total ingresados por el usuario para poder iterar sobre ellos y ejecutar el comando correcto.
 * 
 * @return int Número de comandos registrados.
 */
int numcom(){
    return sizeof(nombreComandos) / sizeof(char *);
}

/**
 * @brief Ejecutar.
 * Permite la ejecución de los comandos ingresados desde la consola, comparando el comando ingresado con los comandos registrados y ejecutando la función correspondiente si se encuentra una coincidencia. Si el comando no es reconocido, se muestra un mensaje de error.
 * 
 * @param args Arreglo de argumentos del comando.
 */
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

/**
 * @brief Bucle principal del shell.
 * Este bucle se ejecuta continuamente, esperando la entrada del usuario, leyendo la línea de comando, parseándola en argumentos y ejecutando el comando correspondiente. El bucle se mantiene activo hasta que el usuario ingresa el comando de salida, lo que hace que el sistema operativo termine su ejecución.
 *   *line: Puntero a la cadena de caracteres que contiene la línea de comando ingresada por el usuario.
 *   * **args: Arreglo de cadenas de caracteres que contiene los comandos y argumentos separados.
 */
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