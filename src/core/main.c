#include <stdio.h>
#include "shell.h"
int main() {
    printf("--------------------------------------------------------------[EAFITos]--------------------------------------------------------------\n");
    printf("Bienvenido a EAFITos, el sistema operativo de la Universidad EAFIT\n");
    printf("A continuacion escriba el comando que desea ejecutar, o escriba 'ayuda' para ver la lista de comandos disponibles\n");
    loop_shell();
    return 0;
}


