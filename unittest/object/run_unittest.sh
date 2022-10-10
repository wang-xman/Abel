#!/bin/sh

# Path to Dora shared library.
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "*************************************"
echo "* Abel : Unittest : Header : object *"
echo "*************************************"

echo "-- Compile sources to objects via Makefile --"
make

echo "-- Compile local source file(s) --"
g++ -std=c++14 -c ./test_object.cpp -o ./test_object.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora lib --"
g++ -std=c++14 $BLDDIR/error.o \
    $BLDDIR/typefy.o \
    $BLDDIR/object.o \
    ./test_object.o \
    -L$DORA_LIBPATH \
    -o ./unittest_object.out -ldora

echo "-- Run executable --"
./unittest_object.out