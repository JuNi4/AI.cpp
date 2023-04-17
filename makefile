CXX 	:= g++

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= include/nn/*.cpp include/CMath/*.cpp include/*.hpp

EXECUTABLE	:= main

all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)

c: clean all

$(BIN)/$(EXECUTABLE): $(SRC)/main.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

train: $(SRC)/evoloution_training.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $(BIN)/$(EXECUTABLE) $(LIBRARIES)
	./$(BIN)/$(EXECUTABLE)