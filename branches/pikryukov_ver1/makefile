CXX:=g++
CXXFLAGS:= -Wall

#bin directory
BIN_DIR:=bin/Makefile

#obj directory
OBJ_DIR:=obj/Makefile

ifeq ($(DEBUG), 1)
  ifeq ($(PROFILE), 1)
    CXXFLAGS:= $(CXXFLAGS) -pg
    LDFLAGS:= -pg
  endif
    CXXFLAGS:= $(CXXFLAGS) -O0 -g -c
    BIN_DIR:=$(BIN_DIR)/Debug
    OBJ_DIR:=$(OBJ_DIR)/Debug
else
    CXXFLAGS:= $(CXXFLAGS) -O3 -c
    BIN_DIR:=$(BIN_DIR)/Release
    OBJ_DIR:=$(OBJ_DIR)/Release
endif

#sources directory
SRC_DIR:=source

SIMMY_CPP_FILES := \
	$(SRC_DIR)/simmy.cpp \
	$(SRC_DIR)/executor.cpp \
	$(SRC_DIR)/decoder.cpp \
	$(SRC_DIR)/register.cpp \
	$(SRC_DIR)/isa.cpp \
	$(SRC_DIR)/main.cpp
    
#simmy objs file to archive in $(LIBPLIMDP)
SIMMY_OBJS_FILES:=${SIMMY_CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o}

#common rule for build
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR) $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

#building binaries
$(BIN_DIR)/simmy: $(SIMMY_OBJS_FILES)
	$(CXX) $^ -o $@

all: $(BIN_DIR)/simmy

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

.PHONY: clean
