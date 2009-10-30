#!/bin/csh

CXX:=g++ -Wall

OBJS_CPP := ${shell ls *.cpp}
OBJS:=${OBJS_CPP:%.cpp=%}
OBJS_O:=${OBJS_CPP:%.cpp=%.o}
OBJS_I:=${OBJS:%=%.i}

all: $(OBJS_O)
	$(CXX) $(OBJS_O) -o funcsim

%.o:%.cpp
	$(CXX) $(<) -c -o $(@)

clean:
	rm -rf funcsim $(OBJS_O)

