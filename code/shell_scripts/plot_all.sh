#!/usr/bin/sh
PYTHON_PATH=python
DATA="data/"

if [ ! -d "$DATA" ]; then
    echo "Directory not found will simulate all"
    ./run_all.sh
else
    echo "Directory found and will visualize"
fi


for FILE in $PYTHON_PATH/*py
do
    if [ $FILE = "$PYTHON_PATH/functions.py" ]; then
        continue
    elif [ $FILE = "$PYTHON_PATH/anim.py" ]; then
        continue
    fi

    echo "Running " $FILE
    python3 $FILE
done
