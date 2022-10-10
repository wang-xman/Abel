#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "***********************************"
echo "* Abel : Unittest : Header : null *"
echo "***********************************"

echo "-- Compile source file(s) via Makefile --"
make

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./test_null.cpp -o ./test_null.o \
    -I $INCDIR -I $DORA_HEADER

echo "-- Link object files --"
g++ -std=c++14 -g -Wall \
    $BLDDIR/typefy.o \
    $BLDDIR/object.o \
    $BLDDIR/error.o \
    $BLDDIR/null.o \
    ./test_null.o  \
    -L$DORA_LIBPATH \
    -o ./unittest_null.out -ldora

echo "-- Run executable --"
./unittest_null.out