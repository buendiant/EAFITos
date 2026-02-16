/**
 * @file shell.h
 * @brief Definición de la interfaz del shell EAFITos.
 * 
 * Este archivo contiene las declaraciones de funciones y constantes necesarias para implementar el shell del sistema operativo EAFITos.
 * 
 */
#ifndef SHELL_H
#define SHELL_H

#define MAX_CMD_INPUT 1024 // Tamaño máximo de entrada de comando.
#define DELIM " \t\r\n\a" //Caracteres delimitadores para separar los comandos y sus argumentos.

/**
 * @brief Incia el bucle principal del shell, que continuamente espera y procesa los comandos ingresados por el usuario hasta que se le indique salir del sistema operativo.
 * 
 */
void loop_shell();

/**
 * @brief lee la linea de entrada.
 * 
 * @return char* Puntero a una cadena de caracteres que contiene la línea de comando ingresada por el usuario.
 */
char *readLine(void);

/**
 * @brief Hace el recorrido de la linea de comandos ingresada.
 * 
 * @param linea Cadena de entrada que contiene el comando y sus argumentos.
 * @return char** Arreglo de cadenas de caracteres que contiene los comandos y argumentos separados.
 */
char **parsear_linea(char *linea);
/**
 * @brief Permite la ejecucion de comandos ingresados por el usuario.
 * 
 * @param args Lista de argumentos.
 */
void ejecutar(char **args);
#endif