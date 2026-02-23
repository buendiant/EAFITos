# EAFITOS

Proyecto en **C** que implementa una shell y utilidades básicas del sistema, organizado por módulos (`commands`, `core`, `utils`) y con scripts de compilación y pruebas.

##  Estructura del proyecto

```
eafitos/
│
├── docs/            # Documentación del proyecto
├── include/         # Archivos .h
├── src/             # Código fuente en C
│   ├── commands/
│   ├── core/
│   └── utils/
├── scripts/         # Scripts de build y formato
├── tests/           # Pruebas
├── Makefile         # Compilación principal
└── README.md
```

##  Requisitos

* GCC o Clang
* Make
* Linux / WSL recomendado

Instalar en Ubuntu/WSL:

```bash
sudo apt update
sudo apt install build-essential
```

##  Compilación

Desde la raíz del proyecto:

bash
make


Esto generará el ejecutable del proyecto.

Para limpiar archivos compilados:

bash
make clean


##  Ejecución

bash
./eafitos


##  Tests

El proyecto incluye una suite base de pruebas unitarias en tests/unit_tests.c y un runner en tests/tests_runner.sh.

Para ejecutarlas:

bash
make test


### ¿Cómo crear una prueba unitaria y registrarla en tests?

1. Crea una función static dentro de tests/unit_tests.c con el patrón test_<modulo>_<comportamiento>().
2. Usa assert(...) para validar el resultado esperado.
3. Si la función que pruebas devuelve memoria dinámica (como parsear_linea), libera la memoria al final de la prueba.
4. Registra la prueba llamándola desde main() en tests/unit_tests.c.
5. Ejecuta make test para compilar y correr las pruebas.

Ejemplo corto:

c
static void test_parsear_linea_vacia_retorna_solo_null(void) {
    char entrada[] = "   \t\n";
    char **tokens = parsear_linea(entrada);

    assert(tokens != NULL);
    assert(tokens[0] == NULL);

    free(tokens);
}

##  .gitignore

El proyecto incluye un `.gitignore` configurado para:

* Archivos compilados de C (`*.o`, ejecutables, etc.)
* Carpetas `build/` y `bin/`
* Archivos temporales del sistema y editores
* Logs y coverage

Esto evita subir binarios y archivos innecesarios al repositorio.

##  Integrantes

* Juan Antonio Buendia Sanchez
* Juan Pablo Parra Elmasri
* Ismael García Ceballos
* Alessandro Soccol Mejía


---

Proyecto desarrollado con fines educativos.

