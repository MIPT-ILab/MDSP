#!/bin/sh

#
#   With -DDEBUG_OUTPUT gcc defines the DEBUG_OUTPUT preprocessor variable
#
#   Use the first line to disable DEBUG_OUTPUT
#   Use the second line to enable DEBUG_OUTPUT
#
CXX = g++ -Wall -g
#CXX = g++ -Wall -g -DDEBUG_OUTPUT

OBJS_CPP = \
	main.cpp \
	tokenan.cpp \
	semantican.cpp \
	assembler.cpp \
	../../funcsim/operation.cpp \
	../../funcsim/memory.cpp

OBJS_O = ${OBJS_CPP:%.cpp=%.o}

all: $(OBJS_O)
	$(CXX) $(OBJS_O) -o mdsp-asm
%.o: %.cpp
	$(CXX) $(<) -c -o $(@)
clean:
	rm -rf funcsim $(OBJS_O)

