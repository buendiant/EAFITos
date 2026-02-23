#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build/tests"

mkdir -p "$BUILD_DIR"

echo "[1/2] Compilando unit tests..."
gcc -Wall -Wextra -I"$ROOT_DIR/include" \
    "$ROOT_DIR/tests/unit_tests.c" \
    "$ROOT_DIR/src/core/parser.c" \
    -o "$BUILD_DIR/unit_tests"

echo "[2/2] Ejecutando unit tests..."
"$BUILD_DIR/unit_tests"

echo "[OK] Tests finalizadas correctamente."