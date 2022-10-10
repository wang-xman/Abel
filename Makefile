# Makefile treate a shared library: libabel.so
# Note that the build directory must exist
CXX := g++
# For both GNU g++ and clang++
CXXFLAGS := -g -Wall -std=c++14
# Directories
INCDIR := ${ABEL_ROOT}/include/
SRCDIR := ${ABEL_ROOT}/src/
BLDDIR := ${ABEL_ROOT}/build/

SOURCES := $(wildcard ${SRCDIR}*.cpp)
OBJECTS := $(patsubst ${SRCDIR}%.cpp, ${BLDDIR}%.o, ${SOURCES})

SHRDLIB := ${BLDDIR}libabel.so

all: ${SHRDLIB}

${SHRDLIB}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -shared -o $@

${OBJECTS}: ${BLDDIR}%.o: ${SRCDIR}%.cpp
	${CXX} ${CXXFLAGS} -c $< -fPIC -o $@ -I${INCDIR}

clean_objects:
	rm -rf $(OBJECTS)

.PHONEY: all clean_objects