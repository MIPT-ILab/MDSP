#!/bin/sh

CXX = g++ -Wall -g

OBJS_CPP = \
	main.cpp \
	tokenan.cpp \
	semantican.cpp \
	assembler.cpp \
	../funcsim/operation.cpp \
	../../pzaichenkov/memory.cpp

OBJS_O = ${OBJS_CPP:%.cpp=%.o}

all: $(OBJS_O)
	$(CXX) $(OBJS_O) -o mdsp-asm
%.o: %.cpp
	$(CXX) $(<) -c -o $(@)
clean:
	rm -rf funcsim $(OBJS_O)

