
ifeq ($(DEBUG), yes)
    CXX:=g++ -Wall -O0 -I boost
	OUT:=Debug
else
    CXX:=g++ -Wall -O3 -I boost
	OUT:=Release
endif

ifeq ($(shell uname -m), i686)
	LBITS := 32
else
ifeq ($(shell uname -m), x86_64)
	LBITS := 64
else
	LIBS_OBJS := error
endif
endif   
   
COMMON_OBJS_CPP := \
	sources/funcsim/config.cpp \
	sources/funcsim/core.cpp \
	sources/funcsim/flags.cpp \
	sources/funcsim/log.cpp \
	sources/funcsim/memory.cpp \
	sources/funcsim/operation.cpp \
	sources/funcsim/register_file.cpp \
	sources/funcsim/scheduler.cpp \
	sources/funcsim/main_functions.cpp
MAIN_OBJS_CPP := ${COMMON_OBJS_CPP} \
	sources/funcsim/main.cpp 
TEST_OBJS_CPP := ${COMMON_OBJS_CPP} \
	sources/funcsim/cout_wrapper.cpp \
	sources/funcsim/test.cpp
ASM_OBJS_CPP := \
	sources/asm/main.cpp \
	sources/asm/tokenan.cpp \
	sources/asm/semantican.cpp \
	sources/asm/assembler.cpp \
	sources/funcsim/log.cpp \
	sources/funcsim/memory.cpp \
	sources/funcsim/operation.cpp \
	sources/funcsim/register_file.cpp \
	sources/funcsim/core.cpp \
	sources/funcsim/flags.cpp

UNAME := $(shell uname -o)

ifeq ($(UNAME), GNU/Linux)	
	LIBS_OBJS := boost/libs/$(LBITS)/libboost_program_options-gcc44-1_44.a
else
ifeq ($(UNAME), Cygwin)
	LIBS_OBJS := boost/stage/lib/libboost_program_options.a
else
	LIBS_OBJS := error
endif	
endif	

MAIN_OBJS_O:=${MAIN_OBJS_CPP:sources/%.cpp=$(OUT)/build/%.o} \
		${LIBS_OBJS}
TEST_OBJS_O:=${TEST_OBJS_CPP:sources/%.cpp=$(OUT)/build/%.o} \
		${LIBS_OBJS}
ASM_OBJS_O:=${ASM_OBJS_CPP:sources/%.cpp=$(OUT)/build/%.o}

all: funcsim test asm
	
ifeq ($(DEBUG), yes)
Debug/build/%.o: sources/%.cpp OStest build_dirs
		$(CXX) $< -c -o $@		
else		
Release/build/%.o: sources/%.cpp OStest build_dirs
		$(CXX) $< -c -o $@		
endif		

ifeq ($(LIBS_OBJS), error)
OStest:
	@echo $(UNAME) $(LBITS)
	@echo "System isn't supported."
	@exit 2
else
OStest:	
	@echo $(UNAME) $(LBITS)
	@echo "system is supported."
endif	

build_dirs:
	mkdir -p $(OUT)/build/asm
	mkdir -p $(OUT)/build/test
	mkdir -p $(OUT)/build/funcsim

funcsim: $(MAIN_OBJS_O)
	$(CXX) $(MAIN_OBJS_O) -o $(OUT)/funcsim
    ifeq ($(DEBUG), yes)
		@echo "--- funcsim created ---"
    endif    

test: $(TEST_OBJS_O)
	$(CXX) $(TEST_OBJS_O) -o $(OUT)/test
    ifeq ($(DEBUG), yes)
		@echo "--- test created ---"
    endif    

asm: $(ASM_OBJS_O)
	$(CXX) $(ASM_OBJS_O) -o $(OUT)/asm
    ifeq ($(DEBUG), yes)
		@echo "--- asm created ---"
    endif    
	
clean:
	rm -rf $(OUT)/build
	rm -f $(OUT)/funcsim
	rm -f $(OUT)/test
	rm -f $(OUT)/asm
