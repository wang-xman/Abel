#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "****************************************"
echo "* Abel : Unittest : Header : delimiter *"
echo "****************************************"

echo "-- Compile sources to object files --"
make

echo "-- Compile local source file(s) --"
g++ -std=c++11 -g -Wall -c ./test_delimiter.cpp -o ./test_delimiter.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora lib --"
g++ -std=c++11 -g -Wall \
    $BLDDIR/error.o \
    $BLDDIR/typefy.o \
    $BLDDIR/symbol.o \
    $BLDDIR/util.o \
    $BLDDIR/delimiter.o \
    ./test_delimiter.o -L$DORA_LIBPATH \
    -o ./unittest_delimiter.out -ldora

echo "-- Run executable --"
./unittest_delimiter.out