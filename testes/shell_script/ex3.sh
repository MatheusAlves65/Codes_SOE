#!/bin/bash

# Nome do arquivo que contém as URLs
arquivo_urls="sites.txt"

# Verifica se o arquivo existe
if [ -f "$arquivo_urls" ]; then
  # Loop para ler cada URL do arquivo e fazer o download
  while read -r url; do
    # Obtém o nome do arquivo a partir da URL
    nome_arquivo=$(basename "$url")

    # Realiza o download do arquivo
    wget "$url" -O "$nome_arquivo"

  done < "$arquivo_urls"
fi

