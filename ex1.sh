#!/bin/bash

for i {100..1}
do
nome_arquivo = "teste$(i).txt"
texto = "Numero do arquivo = $(i)"
echo "$texto" > $nome_arqui
 
done
