/**
 * @file commands.h
 * @brief Interfaz para los comandos del sistemas.
 *
 */
#ifndef COMMANDS_H
#define COMMANDS_H

//COMANDOS
/**
* --- BASICOS ----
 * @brief Lista de archivos.
 */
void listOS(char **args);
/**
 * @brief Lectura de archivos.
 */
void readOS(char **args);
/**
 * @brief Tiempo que registra el sistema.
 */
void timeOS(char **args);
/**
 * @brief Calculadora basica.
 */
void calcOS(char **args);
/**
 * @brief Lista de ayuda.
 */
void helpOS(char **args);
/**
 * @brief Salir del sistema operativo.
 *
 */
void exitOS(char **args);

// --- AVANZADOS (archivos) ---
void buscarOS(char **args);
void estadisticasOS(char **args);

/**
 * @brief Retorna el número de comandos registrados.
 */
int numcom();
#endif