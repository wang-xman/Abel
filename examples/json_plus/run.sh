#!/bin/sh
# Updated 09-10-2022

# Path to Abel shared lib and headers
ABEL_LIBPATH="$ABEL_ROOT/build"
ABEL_HEADER="$ABEL_ROOT/include"
# Path to shared lib must be explilcitly appended to the library path.
export LD_LIBRARY_PATH=$ABEL_ROOT/build:$LD_LIBRARY_PATH

echo "******************************"
echo "* Example - JSON Plus Format *"
echo "******************************"

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./json_plus.cpp -o ./json_plus.o -I $ABEL_HEADER

echo "-- Link object files with Abel shared lib --"
g++ -std=c++14 -g -Wall ./json_plus.o -L$ABEL_LIBPATH \
    -o ./run_json_plus.out -label

echo "-- Run executable --"
./run_json_plus.out