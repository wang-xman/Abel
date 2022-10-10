#!/bin/sh
# Updated 09-10-2022

# Path to Abel shared lib and headers
ABEL_LIBPATH="$ABEL_ROOT/build"
ABEL_HEADER="$ABEL_ROOT/include"
# Path to shared lib must be explilcitly appended to the library path.
export LD_LIBRARY_PATH=$ABEL_ROOT/build:$LD_LIBRARY_PATH

echo "***************************"
echo "* Example - Standard JSON *"
echo "***************************"

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./standard_json.cpp -o ./standard_json.o -I $ABEL_HEADER

echo "-- Link object files with Abel shared lib --"
g++ -std=c++14 -g -Wall ./standard_json.o -L$ABEL_LIBPATH \
    -o ./run_standard_json.out -label

echo "-- Run executable --"
./run_standard_json.out