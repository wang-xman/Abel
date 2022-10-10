#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "***********************************************"
echo "* Abel : Unittest : Header : json_plus_loader *"
echo "***********************************************"

echo "-- Compile sources to object files via Makefile --"
make

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./test_json_plus_loader.cpp -o ./test_json_plus_loader.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora lib --"
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
    $BLDDIR/dict.o \
    $BLDDIR/container.o \
    $BLDDIR/symbol.o \
    $BLDDIR/util.o \
    $BLDDIR/converter.o \
    $BLDDIR/delimiter.o \
    $BLDDIR/token.o \
    $BLDDIR/parser.o \
    $BLDDIR/container_parser.o \
    $BLDDIR/json_token.o \
    $BLDDIR/json_parser.o \
    $BLDDIR/json_plus_parser.o \
    $BLDDIR/container_loader.o \
    $BLDDIR/json_loader.o \
    $BLDDIR/json_plus_loader.o \
    ./test_json_plus_loader.o -L$DORA_LIBPATH \
    -o ./unittest_json_plus_loader.out -ldora

echo "-- Run executable --"
./unittest_json_plus_loader.out