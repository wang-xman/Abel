#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "**************************************"
echo "* Abel : Unittest : Header : integer *"
echo "**************************************"

echo "-- Compile source file(s) via Makefile --"
make

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./test_integer.cpp -o ./test_integer.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora library --"
g++ -std=c++14 -g -Wall \
    $BLDDIR/error.o \
    $BLDDIR/typefy.o \
    $BLDDIR/object.o \
    $BLDDIR/numeric.o \
    $BLDDIR/integer.o \
    $BLDDIR/bool.o \
    ./test_integer.o  \
    -L$DORA_LIBPATH \
    -o ./unittest_integer.out -ldora

echo "-- Run executable --"
./unittest_integer.out