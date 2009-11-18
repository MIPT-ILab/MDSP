#!/bin/csh

CXX:=g++ -Wall

OBJS_CPP := ${shell ls *.cpp}
OBJS:=${OBJS_CPP:%.cpp=%}
OBJS_O:=${OBJS_CPP:%.cpp=%.o}

all: $(OBJS_O)
	$(CXX) $(OBJS_O) -o funcsim

main.o: test.h

%.o: %.cpp %.h types.h
	$(CXX) -c $(<) -o $(@)

clean:
	rm -rf funcsim $(OBJS_O)

