# Makefile for unittest header: text
CXX := g++
# For both g++ and clang++
CXXFLAGS := -std=c++14 -g -Wall

ABELROOT := ${ABEL_ROOT}
INCDIR := ${ABELROOT}/include/
SRCDIR := ${ABELROOT}/src/
BLDDIR := ${ABELROOT}/build/

REQUIRED_SRC := error.cpp typefy.cpp object.cpp text.cpp

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