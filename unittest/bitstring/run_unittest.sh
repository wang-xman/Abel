#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "****************************************"
echo "* Abel : Unittest : Header : bitstring *"
echo "****************************************"

echo "-- Compile source file(s) via Makefile --"
make

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./test_bitstring.cpp -o ./test_bitstring.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files --"
g++ -std=c++11 -g -Wall \
    $BLDDIR/error.o \
    $BLDDIR/typefy.o \
    $BLDDIR/object.o \
    $BLDDIR/text.o \
    $BLDDIR/bitstring.o \
    ./test_bitstring.o  \
    -L$DORA_LIBPATH \
    -o ./unittest_bitstring.out -ldora

echo "-- Run executable --"
./unittest_bitstring.out