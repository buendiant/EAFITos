/**
 * @file system_commands.c
 * @brief  Comandos 
 * 
 * Este archivo contiene funciones que implementan operaciones que requieren comunicacion directa con el sistema aritmetico del computador
 * 
 * 

 */
#include <stdio.h>
#include <stdlib.h>
#include "commands.h"

/**
 * @brief Comando calc.
 * 
 * Realiza operaciones aritmeticas basicas (suma, resta, multiplicacion y division) entre dos numeros ingresados por el usuario.
 * 
 * @param args Los argumentos que requiere el comando para poder realziar la operacion que concistyen en:
 *  - num1: El primer numero de la operacion.
 *  - operador: El operador aritmetico que se desea usar (puede ser +, -, *, /).
 *  - num2: El segundo numero de la operacion.
 *  Separados respectivamente por espacios, del modo: calc <num1> <operador> <num2>.
 * 
 */

 void calcOS(char **args){

    // Verificacion de que se han proporcionado los argumentos necesarios para realizar la operacion
    if(args[1]==NULL || args[2]==NULL || args[3]==NULL){
        printf("Error: Debes proporcionar dos numeros y un operador para realizar la operacion.\n");
        printf("Uso: calc <num1> <operador> <num2>\n");
        return;
    }
    //De ser asi, convertimos los datos a flotantes para poder realizar las operaciones aritmeticas, y almacenamos el resultado 

    float num1 = atof(args[1]);
    char op = args[2][0];
    float num2 = atof(args[3]);
    float res = 0;

    switch(op){
        case '+':
            res = num1 + num2;
            break;
        case '-':
            res = num1 - num2;
            break;
        case '*':
            res = num1 * num2;
            break;
        case '/':
        //Evitamos que el usuario realice una division entre cero, la cual generaria un error
            if(num2 == 0){
                printf("Error: No se puede dividir por cero.\n");
                return;
            }
            res = num1 / num2;
            break;
        default:
            printf("Error: Operador no reconocido. Usa +, -, *, o /.\n");
            return;
    }
    printf("Resultado: %.2f\n", res);//Se limita el resutlado a 2 decimales
}
