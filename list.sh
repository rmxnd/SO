#!/bin/bash

usage="usage <IN_DIR> <OUTPUT_FILE>"


if [[ ! -d $1 ]]; then
    echo $usage
    echo "directory $1 non trovata"
    exit
fi

start_dir=$(pwd)
cd $1

files=$(ls)

# torno nella directory di prima
 cd $start_dir

# scarto le sotto_directory, iterando l'elenco dei files
for f in $files
do
    if [[ ! -d $1/$f ]]; then
        # scrive in append sul file
        echo $f >> $2
    fi
done