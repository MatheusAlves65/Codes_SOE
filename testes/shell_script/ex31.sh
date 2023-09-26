#!/bin/bash

# Nome do arquivo que contém as URLs
arquivo_urls="sites.txt"

# Verifica se o arquivo existe e faz o download dos arquivos
[ -f "$arquivo_urls" ] && wget -i "$arquivo_urls"
