#!/usr/bin/sh
INPUT=input_files
DATA="data/"

if [ ! -d "$DATA" ]; then
    echo "Directory not found and will be created"
    mkdir $DATA
else
    echo "Directory found"
fi

mv $INPUT/double* $INPUT/no* $INPUT/single* $INPUT/triple* .

for FILE in $INPUT/problem*csv
do
    echo "Simulating " $FILE
    BIN=$(echo $(basename -s '.csv' $FILE).bin)
    ./main $FILE
    mv $BIN $DATA
done

mv *slit*csv $INPUT
