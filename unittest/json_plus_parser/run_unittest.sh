#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "***********************************************"
echo "* Abel : Unittest : Header : json_plus_parser *"
echo "***********************************************"

echo "-- Compile sources to object files via Makefile --"
make

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./test_json_plus_parser.cpp -o ./test_json_plus_parser.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files together with Dora test suite --"
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
    $BLDDIR/symbol.o \
    $BLDDIR/util.o \
    $BLDDIR/converter.o \
    $BLDDIR/delimiter.o \
    $BLDDIR/token.o \
    $BLDDIR/json_token.o \
    $BLDDIR/parser.o \
    $BLDDIR/container_parser.o \
    $BLDDIR/json_parser.o \
    $BLDDIR/json_plus_parser.o \
    ./test_json_plus_parser.o -L$DORA_LIBPATH \
    -o ./unittest_json_plus_parser.out -ldora

echo "-- Run executable --"
./unittest_json_plus_parser.out