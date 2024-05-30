#!/bin/bash
# se il primo argomento e' un numero maggiore di 10, stampa ok, altrimewnti stampa l'uso corretto del programma

value=$1

if [ $value -gt "10" ]
	then
	echo "l'argomento e' maggiore di 10"
elif [ $value -lt "10" ]
	then
	echo "argomento minore di 10"
else
	echo "l'argomento non e' un numero"
	echo "usage: greater <number>"
fi
