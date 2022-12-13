#!/usr/bin/sh

for file in ./input_files/*csv
do
    echo "Simulating " $file
    ./main $file
done
