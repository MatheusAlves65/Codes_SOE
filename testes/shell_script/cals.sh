#!/bin/bash
while [ $# -ge 2 ]; do
  mes="$1"
  ano="$2"
  cal "$mes" "$ano"  # Exibe o calend



  shift 2  # Move para os próximos dois argumentos
done
