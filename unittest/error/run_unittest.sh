#!/bin/sh

DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "************************************"
echo "* Abel : Unittest : Header : error *"
echo "************************************"

echo "-- Compile source files --"
g++ -std=c++14 -g -Wall -c $SRCDIR/error.cpp -o $BLDDIR/error.o -I $INCDIR

echo "-- Compile local source files --"
g++ -std=c++14 -g -Wall -c ./test_error.cpp -o ./test_error.o \
    -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora lib --"
g++ -std=c++14 -g -Wall $BLDDIR/error.o ./test_error.o  \
    -L$DORA_LIBPATH -o ./unittest_error.out -ldora

echo "-- Run executable --"
./unittest_error.out