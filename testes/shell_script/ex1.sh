#!/bin/bash

# Loop de 1 a 100 para criar os arquivos
for i in {1..100}; do
  # Nome do arquivo
  filename="teste${i}.txt"
  
  # Texto a ser escrito no arquivo
  content="Número do arquivo = ${i}"
  
  # Escrever o conteúdo no arquivo
  echo "$content" > "$filename"
  
  # Mensagem de confirmação
  echo "Arquivo $filename criado com sucesso!"
done
