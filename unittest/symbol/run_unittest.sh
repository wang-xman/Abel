#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "*************************************"
echo "* Abel : Unittest : Header : symbol *"
echo "*************************************"

echo "-- Compile sources to object files --"
# Dependecy : error
g++ -std=c++11 -g -Wall -c $SRCDIR/error.cpp -o $BLDDIR/error.o -I $INCDIR
# Dependecy : typefy
g++ -std=c++11 -g -Wall -c $SRCDIR/typefy.cpp -o $BLDDIR/typefy.o -I $INCDIR
# Source
g++ -std=c++14 -g -Wall -c $SRCDIR/symbol.cpp -o $BLDDIR/symbol.o -I $INCDIR

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./test_symbol.cpp -o ./test_symbol.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora lib --"
g++ -std=c++14 -g -Wall \
    $BLDDIR/error.o \
    $BLDDIR/typefy.o \
    $BLDDIR/symbol.o \
    ./test_symbol.o -L$DORA_LIBPATH \
    -o ./unittest_symbol.out -ldora

echo "-- Run executable --"
./unittest_symbol.out