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

```bash
make
```

Esto generará el ejecutable del proyecto.

Para limpiar archivos compilados:

```bash
make clean
```

##  Ejecución

```bash
./eafitos
```

##  Tests

el proyecto incluye pruebas:

```bash
make test
```

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

