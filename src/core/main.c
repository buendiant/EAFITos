/**
 * @file main.c
 * @brief Punto de entrada del sistema operativo EAFITos.
 * Este archivo contiene la función principal del sistema operativo EAFITos, que inicia el shell y da la bienvenida al usuario. 
 * Aqui se muestra un mensaje de bienvenida y se llama a la función loop_shell() para iniciar el bucle principal del shell, que espera y procesa los comandos ingresados por el usuario.
 * 
 */
#include <stdio.h>
#include "shell.h"
int main() {
    printf("--------------------------------------------------------------[EAFITos]--------------------------------------------------------------\n");
    printf("Bienvenido a EAFITos, el sistema operativo de la Universidad EAFIT\n");
    printf("A continuacion escriba el comando que desea ejecutar, o escriba 'ayuda' para ver la lista de comandos disponibles\n");
    loop_shell();
    return 0;
}


