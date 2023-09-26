#!/bin/bash
if [ $# -lt 3 ]; then
  exit
fi
a=0
b=.
c=$(($1+$2))
while [ $a -lt $c ]; do
  echo -n $b
  sleep $3
  a=$((a+1))
  if [ $a = $1 ]; then
    b=-
  elif [ $a = $c ]; then
    a=0
    b=.
  fi
done
