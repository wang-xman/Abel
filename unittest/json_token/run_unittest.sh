#!/bin/sh
DORA_LIBPATH="$DORA_ROOT/build"
DORA_HEADER="$DORA_ROOT/include"
export LD_LIBRARY_PATH=$DORA_ROOT/build:$LD_LIBRARY_PATH

# Abel directories
INCDIR="$ABEL_ROOT/include"
SRCDIR="$ABEL_ROOT/src"
BLDDIR="$ABEL_ROOT/build"

echo "*****************************************"
echo "* Abel : Unittest : Header : json_token *"
echo "*****************************************"

echo "-- Compile sources to object files --"
# Dependency : Exceptions
g++ -std=c++14 -g -Wall -c $SRCDIR/error.cpp -o $BLDDIR/error.o -I $INCDIR
# Dependency: Symbol
g++ -std=c++14 -g -Wall -c $SRCDIR/symbol.cpp -o $BLDDIR/symbol.o -I $INCDIR
# Dependency : Token
g++ -std=c++14 -g -Wall -c $SRCDIR/token.cpp -o $BLDDIR/token.o -I $INCDIR
# JSON  token
g++ -std=c++14 -g -Wall -c $SRCDIR/json_token.cpp -o $BLDDIR/json_token.o -I $INCDIR

echo "-- Compile local source file(s) --"
g++ -std=c++11 -g -Wall -c ./test_json_token.cpp -o ./test_json_token.o -I $INCDIR -I $DORA_HEADER

echo "-- Link object files with Dora lib --"
g++ -std=c++11 -g -Wall \
    $BLDDIR/error.o \
    $BLDDIR/symbol.o \
    $BLDDIR/token.o \
    $BLDDIR/json_token.o \
    ./test_json_token.o -L$DORA_LIBPATH \
    -o ./unittest_json_token.out -ldora

echo "-- Run executable --"
./unittest_json_token.out