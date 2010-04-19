#!/bin/sh

CXX:=g++ -Wall

COMMON_OBJS_CPP := \
	funcsim/config.cpp \
	funcsim/core.cpp \
	funcsim/flags.cpp \
	funcsim/memory.cpp \
	funcsim/operation.cpp \
	funcsim/register_file.cpp
MAIN_OBJS_CPP := ${COMMON_OBJS_CPP} \
	funcsim/main.cpp
TEST_OBJS_CPP := ${COMMON_OBJS_CPP} \
	funcsim/cout_wrapper.cpp \
	funcsim/test.cpp
ASM_OBJS_CPP := \
	asm/main.cpp \
	asm/tokenan.cpp \
	asm/semantican.cpp \
	asm/assembler.cpp \
	funcsim/memory.cpp \
	funcsim/operation.cpp \
	funcsim/register_file.cpp 

MAIN_OBJS_O:=${MAIN_OBJS_CPP:%.cpp=build/%.o}
TEST_OBJS_O:=${TEST_OBJS_CPP:%.cpp=build/%.o}
ASM_OBJS_O:=${ASM_OBJS_CPP:%.cpp=build/%.o}

all: funcsim test asm

build/%.o: %.cpp build_dirs
	$(CXX) -c -o $@ $<

build_dirs:
	mkdir -p build/{asm,funcsim}

bin:
	mkdir -p bin

funcsim: $(MAIN_OBJS_O) bin
	$(CXX) $(MAIN_OBJS_O) -o bin/funcsim
	@echo "--- funcsim created ---"

test: $(TEST_OBJS_O) bin
	$(CXX) $(TEST_OBJS_O) -o bin/test
	@echo "--- test created ---"

asm: $(ASM_OBJS_O) bin
	$(CXX) $(ASM_OBJS_O) -o bin/asm
	@echo "--- asm created ---"

clean:
	rm -rf build bin

