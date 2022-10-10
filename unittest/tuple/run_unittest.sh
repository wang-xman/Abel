#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "************************************"
echo "* Abel : Unittest : Header : tuple *"
echo "************************************"

echo "-- Compile source file(s) via Makefile --"
make

echo "-- Compile local test source file(s) for Tuple --"
g++ -std=c++14 -g -Wall -c ./test_tuple.cpp -o ./test_tuple.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora library --"
g++ -std=c++14 -g -Wall \
    $BLDDIR/error.o \
    $BLDDIR/typefy.o \
    $BLDDIR/object.o \
    $BLDDIR/null.o \
    $BLDDIR/bool.o \
    $BLDDIR/text.o \
    $BLDDIR/numeric.o \
    $BLDDIR/integer.o \
    $BLDDIR/double.o \
    $BLDDIR/complex.o \
    $BLDDIR/binary.o \
    $BLDDIR/bitstring.o \
    $BLDDIR/intrinsic.o \
    $BLDDIR/list.o \
    $BLDDIR/tuple.o \
    ./test_tuple.o  \
    -L$DORA_LIBPATH \
    -o ./unittest_tuple.out -ldora

echo "-- Run executable --"
./unittest_tuple.out