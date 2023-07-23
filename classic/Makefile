PROJECT := "Othello"
APP := OthelloApp
STATIC_LIB_DIR :=./
STATIC_LIB := $(STATIC_LIB_DIR)/
DYNLIB_DIR := "\"./libDyn\""
DEFINES := -DDYNLIB_DIR=$(DYNLIB_DIR)
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

CXX := clang++
CXXFLAGS := -Wall -std=c++11 -Iinclude -I$(STATIC_LIB_DIR) $(DEFINES)
LD := clang++
LDFLAGS := -L$(STATIC_LIB_DIR)
LDLIBS := -lncurses

all : clean $(BIN_DIR)/$(APP)

clean :
	rm -rf $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/$(APP): $(OBJ_FILES)
	@echo "Project : $(value PROJECT)"
	@echo "Application : $(value APP)"
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(LDLIBS) $(OBJ_FILES) -o $(BIN_DIR)/$(APP)

run :
	$(BIN_DIR)/$(APP)

.PHONY: all run
