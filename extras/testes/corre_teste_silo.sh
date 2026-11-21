#!/bin/bash
# Compila e corre o teste interno do Silo com perda 0% e perda 100%, com AddressSanitizer.
# Correr a partir da pasta do projeto:  bash extras/testes/corre_teste_silo.sh
set -e
RAIZ="$(pwd)"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

for PERDA in 0 100; do
   mkdir -p "$TMP/p$PERDA"
   cp "$RAIZ"/*.cpp "$RAIZ"/*.h "$TMP/p$PERDA/"
   rm "$TMP/p$PERDA/main.cpp"
   sed -i "s/silo_prob_perda = [0-9]*;/silo_prob_perda = $PERDA;/" "$TMP/p$PERDA/Settings.h"
   cp "$RAIZ/extras/testes/teste_silo.cpp" "$TMP/p$PERDA/"
   g++ -std=c++20 -Wall -Wextra -pedantic -fsanitize=address,undefined -g \
       "$TMP/p$PERDA"/*.cpp -I"$TMP/p$PERDA" -o "$TMP/teste$PERDA"
   echo "=== silo_prob_perda = $PERDA ==="
   "$TMP/teste$PERDA"
done
