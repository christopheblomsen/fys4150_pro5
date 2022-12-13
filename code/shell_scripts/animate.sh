#!/usr/bin/sh
PYTHON_PATH=python
DATA_PATH=data
ANIMATION="animation/"

if [ ! -d "$ANIMATION" ]; then
    echo "Directory not found and will be created"
    mkdir $ANIMATION
else
    echo "Directory found"
fi

for FILE in $DATA_PATH/*.bin
do
    echo "Animating " $FILE
    SAVE=$(basename -s '.bin' $FILE)
    python3 $PYTHON_PATH/anim.py $FILE $SAVE
    mv $(echo $SAVE.mp4) $ANIMATION
done
