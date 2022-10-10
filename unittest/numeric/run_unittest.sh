#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel library wide directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "**************************************"
echo "* Abel : Unittest : Header : numeric *"
echo "**************************************"

echo "-- Compile source file(s) via Makefile --"
make

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./test_numeric.cpp -o ./test_numeric.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora test suite --"
g++ -std=c++14 -g -Wall \
    $BLDDIR/typefy.o \
    $BLDDIR/object.o \
    $BLDDIR/numeric.o \
    ./test_numeric.o  \
    -L$DORA_LIBPATH \
    -o ./unittest_numeric.out -ldora

echo "-- Run executable --"
./unittest_numeric.out