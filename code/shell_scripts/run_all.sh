#!/usr/bin/sh
INPUT=input_files

for file in $INPUT/*csv
do
    echo "Simulating " $file
    ./main $file
done
