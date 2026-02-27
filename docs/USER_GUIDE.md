# GUIA PARA EJECUTAR EAFITos

## 1. ABRIR TERMINAL

Para poder iniciar el codigo de EAFITos necesitas abrir la terminal de tu computador y dentro del mismo ubicarte en la dirección de archivo donde descargaste el proyecto, esto puede hacerse del modo 

- Linux/Mac:
```bash
cd /Ubicacion/del/archivo/.../EAFITos
```

- Windows: 
```bash
cd "C:\Ubicacion\del\archivo\...\EAFITos "
```

Tras esto deberas abrir un entorno de Linux para poder ejecutar correctamente el codigo.


## 2. CONSTRUIR EL ENTORNO

A continuación debes ejecutar los siguientes 3 comandos en este orden:

- Limpiar el entorno.
```bash
make clean
```
- Preparar el entorno.
```bash
make 
```
- Ejecutar el sistema operativo.
```bash
make run
```

# 3. EJECUTAR EL SISTEMA OPERATIVO

Para este momento te deberias encontrar dentro del entorno del sistema operativo. Allí podrás escribir los siguientes comandos:

```bash
    * [ listar ]: Muestra contenido del directorio actual
    * [ leer <archivo> ]: Muestra contenido de un archivo de texto
    * [ tiempo ]: Muestra la fecha y hora actual
    * [ calc <num1> <operador> <num2> ]: Realiza una operación aritmética
    * [ ayuda ]: Muestra esta lista de comandos
    * [ buscar <texto> <archivo> ]: Busca un texto dentro de un archivo
    * [ estadisticas ] <archivo>: Muestra bytes, lineas y palabras del archivo
    * [ renombrar ] <viejo> <nuevo>: Cambia el nombre de un archivo
    * [ mover <origen> <destino> ]: Mueve un archivo de ubicación
    * [ directorio ]: Muestra el directorio actual
    * [ limpiar ]: Limpia la información mostrada en pantalla
    * [ usuario ]: Muestra información del usuario actual
    * [ salir ]: Terminar la ejecución del sistema operativo
```

# 4. SALIDA Y RE EJECUCIÓN

Para salir del programa unicamente debes escribir la palabra "salir" en la terminal y esto inmediatamente deberia volver tu entorno a en un sistema de Linux, si deseas volver a ingresar al sistema operativo es importante que sigas correctamente las instrucciones del paso 2 para preparar correctamente el entorno.