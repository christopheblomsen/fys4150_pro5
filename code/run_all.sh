#!/usr/bin/sh

for file in ./input_files/*csv
do
    echo "Simulating " $file
    ./main $file
done

for file in ./*.bin
do
    echo "Animating " $file
    save=$(basename -s '.csv' $file)
    python3 anim.py $file $save
done
