#!/bin/bash

# Função para subir N níveis na estrutura de pastas
up() {
  local niveis="$1"

  # Verifica se o argumento é um número inteiro positivo
  if [[ "$niveis" =~ ^[0-9]+$ ]]; then
    for ((i = 0; i < niveis; i++)); do
      cd ..
    done
  else
    echo "Por favor, forneça um número inteiro positivo como argumento."
  fi
}

# Chama a função "up" com o primeiro argumento fornecido
up "$1"
