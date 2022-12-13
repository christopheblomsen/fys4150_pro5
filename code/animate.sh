#!/usr/bin/sh

for file in ./data/*.bin
do
    echo "Animating " $file
    save=$(basename -s '.bin' $file)
    python3 anim.py $file $save
done
