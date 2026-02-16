//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "commands.h"
/**
  * @brief Comando de ayuda.
  * 
  * Muestra una lista de comandos que el usuario puede ingresar para interactuar con el sistema opeativo.
  * 
  * 
  * @param args Argumentos del comando (aunque en esta seccion no son requeridos).
  */

void helpOS(char **args) {
    printf("Comandos disponibles:\n");
    printf("    *[ listar ]: Muestra contenido del directorio actual\n");
    printf("    *[ leer <archivo> ]: Muestra contenido de un archivo de texto\n");
    printf("    *[ tiempo ]: Muestra la fecha y hora actual\n");
    printf("    *[ calc <num1> <operador> <num2> ]: Realiza una operación aritmética\n");
    printf("    *[ ayuda ]: Muestra esta lista de comandos\n");
    printf("    *[ buscar <texto> <archivo> ]: Busca un texto dentro de un archivo\n");
    printf("    *[ estadisticas ] <archivo>: Muestra bytes, lineas y palabras del archivo\n");
    printf("    *[ renombrar ] <viejo> <nuevo>: Cambia el nombre de un archivo\n");
    printf("    *[ mover <origen> <destino> ]: Mueve un archivo de ubicación\n");
    printf("    *[ directorio ]: Muestra el directorio actual\n");
    printf("    *[ limpiar ]: Limpia la información mostrada en pantalla\n");    
    printf("    *[ salir ]: Terminar la ejecución del sistema operativo\n");

    (void) args;// Evita advertencias de variables no utilizadas
}
/**
 * @brief Comando de salida
 * Permite al usuario salir del sistema operativo de manera segura, mostrando un mensaje de despedida antes de finalizar la ejecución del programa.
 * 
 * @param args Argumentos del comando (nuevamente en esta seccion no son requeridos).
 */
void exitOS(char **args){
    printf("Saliendo de EAFITos. ¡Hasta luego!\n");
    exit(0);
    
    (void) args;// Evita advertencias de variables no utilizadas

}

/**
 * @brief Comando de tiempo
 * 
 * Muestra la fecha y hora actual del sistema en un formato legible para el usuario.
 * 
 * @param args Argumentos del comando (no requerido).
 */
void timeOS(char **args){
    time_t t = time(NULL);//Obtencion del tiempo actual
    struct tm tm = *localtime(&t);
    printf("Fecha y Hora del Sistema: %02d-%02d-%04d %02d:%02d:%02d\n",
        tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
        tm.tm_hour, tm.tm_min, tm.tm_sec);
    (void) args;
}