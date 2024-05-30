#!/bin/bash

# verificare se esiste un file

file=processi.txt

if [[ ! -a $file ]]; then
    echo "$file non esiste"
    exit;

fi

#= SENZA spazio -> assegnamento
# = CON spazio -> comparazione
res=$(grep code $file)

if [[ $res = "" ]]; then
    echo "code non presente";
  else
    echo "code presente"  
    echo "$res";
fi