CXX:=g++
CXXFLAGS:= -Wall

ifeq ($(DEBUG), 1)
  ifeq ($(PROFILE), 1)
    CXXFLAGS:= $(CXXFLAGS) -pg
    LDFLAGS:= -pg
  endif
    CXXFLAGS:= $(CXXFLAGS) -O0 -g -c
else
    CXXFLAGS:= $(CXXFLAGS) -O3 -c
endif

#bin directory
BIN_DIR:=bin

#sources directory
SRC_DIR:=source
SRC_SIMMY_DIR:=$(SRC_DIR)/simmy

#all sources directories
SRC_DIRS := \
    $(SRC_DIR) \
    $(SRC_SIMMY_DIR)

#obj directory
OBJ_DIR:=obj

#all obj directories
OBJ_DIRS:=${SRC_DIRS:$(SRC_DIR)/%=$(OBJ_DIR)/%}

#include of source dirs
CXXFLAGS:= $(CXXFLAGS) -I $(SRC_DIR)

SIMMY_CPP_FILES := \
	$(SRC_SIMMY_DIR)/simmy.cpp \
	$(SRC_SIMMY_DIR)/executor.cpp \
	$(SRC_SIMMY_DIR)/decoder.cpp \
	$(SRC_SIMMY_DIR)/register.cpp	\
	$(SRC_SIMMY_DIR)/isa.cpp
	
#simmy objs file to archive in $(LIBPLIMDP)
SIMMY_OBJS_FILES:=${SIMMY_CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o}

#common rule for build
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR) $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

#building binaries
$(BIN_DIR)/libsimmy.a: $(SIMMY_OBJS_FILES)
	ar rcs $@ $^

$(BIN_DIR)/simmy: $(OBJ_DIR)/main.o $(BIN_DIR)/libsimmy.a
	g++ -L $(BIN_DIR) $< -l simmy -o $@

all: $(BIN_DIR)/simmy

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIRS)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

.PHONY: clean
