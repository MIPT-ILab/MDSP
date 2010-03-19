#!/bin/sh

CXX:=g++ -Wall

COMMON_OBJS_CPP := \
	funcsim/core.cpp \
	funcsim/cout_wrapper.cpp \
	funcsim/flags.cpp \
	funcsim/memory.cpp \
	funcsim/operation.cpp \
	funcsim/register_file.cpp
MAIN_OBJS_CPP := ${COMMON_OBJS_CPP} \
	funcsim/main.cpp
TEST_OBJS_CPP := ${COMMON_OBJS_CPP} \
	funcsim/test.cpp

MAIN_OBJS_O:=${MAIN_OBJS_CPP:%.cpp=%.o}
TEST_OBJS_O:=${TEST_OBJS_CPP:%.cpp=%.o}

funcsim: $(MAIN_OBJS_O)
	mkdir -p bin
	$(CXX) $(MAIN_OBJS_O) -o bin/funcsim

test: $(TEST_OBJS_O)
	mkdir -p bin
	$(CXX) $(TEST_OBJS_O) -o bin/test

clean:
	rm -f bin/funcsim bin/test $(MAIN_OBJS_O) $(TEST_OBJS_O)

all: funcsim

