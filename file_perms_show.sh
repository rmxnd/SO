#!/bin/bash

# Check the file exist and if we have execution permission

usage="<nome_file> -rwx"

# se il file esiste e hai il permesso di esecuzione
if [[ -e "$1" && -x "$1" ]]
	then
		echo "you have execution perms"
		exit 0

#se il file non esiste
elif [[ ! -e "$1" ]]
	then
		echo "file doesn't exist"
		exit 2

# se il file esiste ma non hai i permessi di esecuzione
elif [[ -e "$1" && ! -x "$1" ]]
	then
		echo "you DON'T have exedcution perms"
		exit 1

else
	echo "error"
	echo $usage
	exit 5
fi
