#!/bin/bash


echo "Construyendo EAFITos..."

make"$@"

if[$? -eq 0]; then
    echo "Compilación exitosa."
else
    echo "Error durante la construccion."
fi