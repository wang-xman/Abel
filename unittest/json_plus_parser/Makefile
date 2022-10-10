# Makefile for unittest header : json_plus_parser
CXX := g++
# For both g++ and clang++, use C++ 14
CXXFLAGS := -std=c++14 -g -Wall

ABELROOT := ${ABEL_ROOT}
INCDIR := ${ABELROOT}/include/
SRCDIR := ${ABELROOT}/src/
BLDDIR := ${ABELROOT}/build/

REQUIRED_SRC := error.cpp typefy.cpp object.cpp null.cpp bool.cpp text.cpp \
numeric.cpp integer.cpp double.cpp complex.cpp binary.cpp bitstring.cpp \
intrinsic.cpp symbol.cpp util.cpp converter.cpp delimiter.cpp \
token.cpp json_token.cpp \
parser.cpp container_parser.cpp json_parser.cpp json_plus_parser.cpp

SOURCES := $(addprefix ${SRCDIR}, ${REQUIRED_SRC})

OBJECTS := $(addprefix ${BLDDIR}, $(patsubst %.cpp, %.o, ${REQUIRED_SRC}))

all: ${OBJECTS}

$(OBJECTS): ${BLDDIR}%.o: ${SRCDIR}%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@ -I${INCDIR}

clean:
	rm -rf $(OBJECTS)
	find . -name "*~" -exec rm {} \;
	find . -name "*.o" -exec rm {} \;

.PHONY: all clean