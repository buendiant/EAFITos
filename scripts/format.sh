#!/bin/bash


echo "Formateando código fuente de EAFITos..."

if ! command -v clang-format &> /dev/null; then
    echo "⚠️  ADVERTENCIA: clang-format no encontrado."
    echo "   Por favor instálalo para usar este script: sudo apt install clang-format"
    exit 1
fi


echo "   Procesando archivos en src/..."
find src -name "*.c" -o -name "*.h" -exec clang-format -i -style=Google {} +

echo "   Procesando archivos en include/..."
find include -name "*.h" -exec clang-format -i -style=Google {} +

echo "✅ Formato aplicado correctamente."