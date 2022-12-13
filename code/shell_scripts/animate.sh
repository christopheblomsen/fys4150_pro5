#!/usr/bin/sh
PYTHON_PATH=python
DATA_PATH=data
echo $PYTHON_PATH
for file in $DATA_PATH/*.bin
do
    echo "Animating " $file
    save=$(basename -s '.bin' $file)
    python3 $PYTHON_PATH/anim.py $file $save
done
