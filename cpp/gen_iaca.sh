#!/bin/bash
cd build-iaca-$1
make -j 4
echo > iaca.txt
for f in bitgoo/CMakeFiles/bitgoo_lib.dir/*/*.o; do
    echo Processing $f...
    echo ================================== >> iaca.txt
    echo $f >> iaca.txt
    echo ================================== >> iaca.txt
    ~/iaca-lin64/iaca -arch SKL --trace $(basename $f).trace $f >> iaca.txt;
done


