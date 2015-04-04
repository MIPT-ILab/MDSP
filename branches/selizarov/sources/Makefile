
ifeq ($(DEBUG), yes)
    CXX:=g++ -Wall -O0
else
    CXX:=g++ -Wall -O3
endif
    
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
	mkdir -p build/asm
	mkdir -p build/funcsim

bin:
	mkdir -p bin

funcsim: $(MAIN_OBJS_O) bin
	$(CXX) $(MAIN_OBJS_O) -o bin/funcsim
    ifeq ($(DEBUG), yes)
		@echo "--- funcsim created ---"
    endif    

test: $(TEST_OBJS_O) bin
	$(CXX) $(TEST_OBJS_O) -o bin/test
    ifeq ($(DEBUG), yes)
		@echo "--- test created ---"
    endif    

asm: $(ASM_OBJS_O) bin
	$(CXX) $(ASM_OBJS_O) -o bin/asm
    ifeq ($(DEBUG), yes)
		@echo "--- asm created ---"
    endif    

clean:
	rm -rf build bin

