#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "***********************************"
echo "* Abel : Unittest : Header : util *"
echo "***********************************"

echo "-- Compile sources to object files --"
# Dependecy : error
g++ -std=c++14 -g -Wall -c $SRCDIR/error.cpp -o $BLDDIR/error.o -I $INCDIR
# Dependecy : typefy
g++ -std=c++14 -g -Wall -c $SRCDIR/typefy.cpp -o $BLDDIR/typefy.o -I $INCDIR
# Dependency: symbol
g++ -std=c++14 -g -Wall -c $SRCDIR/symbol.cpp -o $BLDDIR/symbol.o -I $INCDIR
# util
g++ -std=c++14 -g -Wall -c $SRCDIR/util.cpp -o $BLDDIR/util.o -I $INCDIR

echo "-- Compile local source file(s) --"
g++ -std=c++14 -g -Wall -c ./test_util.cpp -o ./test_util.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora lib --"
g++ -std=c++14 -g -Wall \
    $BLDDIR/error.o \
    $BLDDIR/typefy.o \
    $BLDDIR/symbol.o \
    $BLDDIR/util.o \
    ./test_util.o -L$DORA_LIBPATH \
    -o ./unittest_util.out -ldora

echo "-- Run executable --"
./unittest_util.out