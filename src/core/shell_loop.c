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
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "shell.h"
#include "commands.h"

#define LOG_DIR_PATH "tests"
#define LOG_FILE_PATH "tests/command_history.txt"

static void quitar_salto(char *texto) {
    size_t largo;

    if (texto == NULL) {
        return;
    }

    largo = strlen(texto);
    if (largo > 0 && texto[largo - 1] == '\n') {
        texto[largo - 1] = '\0';
    }
}

static void escribir_encabezado(FILE *log_file, const char *linea_original) {
    time_t ahora;
    struct tm *tm_info;
    char fecha[64] = "fecha_desconocida";
    char comando[1024] = {0};

    if (linea_original != NULL) {
        snprintf(comando, sizeof(comando), "%s", linea_original);
        quitar_salto(comando);
    }

    ahora = time(NULL);
    tm_info = localtime(&ahora);
    if (tm_info != NULL) {
        strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", tm_info);
    }

    fprintf(log_file, "===== [%s] =====\n", fecha);
    fprintf(log_file, "Input: %s\n", comando);
    fprintf(log_file, "Output:\n");
}

static void ejecutar_y_registrar(char **args, const char *linea_original) {
    FILE *log_file;
    FILE *tmp;
    int out_copia;
    int err_copia;
    int tmp_fd;
    char buffer[512];
    size_t leidos;

    if (args == NULL || args[0] == NULL) {
        return;
    }

    mkdir(LOG_DIR_PATH, 0777);
    log_file = fopen(LOG_FILE_PATH, "a");
    if (log_file == NULL) {
        ejecutar(args);
        return;
    }

    escribir_encabezado(log_file, linea_original);

    /* 'salir' termina el proceso (exit), por eso se registra manualmente */
    if (strcmp(args[0], "salir") == 0) {
        fprintf(log_file, "Saliendo de EAFITos. ¡Hasta luego!\n\n");
        fclose(log_file);
        ejecutar(args);
        return;
    }

    tmp = tmpfile();
    if (tmp == NULL) {
        ejecutar(args);
        fprintf(log_file, "[No se pudo capturar output]\n\n");
        fclose(log_file);
        return;
    }

    fflush(stdout);
    fflush(stderr);

    out_copia = dup(STDOUT_FILENO);
    err_copia = dup(STDERR_FILENO);
    tmp_fd = fileno(tmp);

    if (out_copia == -1 || err_copia == -1 || tmp_fd == -1) {
        if (out_copia != -1) {
            close(out_copia);
        }
        if (err_copia != -1) {
            close(err_copia);
        }
        fclose(tmp);
        ejecutar(args);
        fprintf(log_file, "[No se pudo capturar output]\n\n");
        fclose(log_file);
        return;
    }

    dup2(tmp_fd, STDOUT_FILENO);
    dup2(tmp_fd, STDERR_FILENO);

    ejecutar(args);

    fflush(stdout);
    fflush(stderr);

    dup2(out_copia, STDOUT_FILENO);
    dup2(err_copia, STDERR_FILENO);
    close(out_copia);
    close(err_copia);

    rewind(tmp);
    while ((leidos = fread(buffer, 1, sizeof(buffer), tmp)) > 0) {
        fwrite(buffer, 1, leidos, stdout);
        fwrite(buffer, 1, leidos, log_file);
    }

    fprintf(log_file, "\n");
    fclose(tmp);
    fclose(log_file);
}

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
    "usuario",
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
    &usuarioOS,
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
        ejecutar_y_registrar(args, line);

        free(line);
        free(args);
    }while(status);
}