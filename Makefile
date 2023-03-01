CXX=g++
CXXFLAGS=-Wall -Wextra -g -std=c++17
# CXXFLAGS += -Werror

INCLUDES=-Iinc

EXE=main
OBJ_DIR=obj/
SRC_DIR = src/


SRC = $(shell find $(SRC_DIR) -name '*.cpp' -printf "%f ")
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all

all: client server

client: client.cpp $(OBJ)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $^ -o $@

server: server.cpp $(OBJ)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $^ -o $@

# $(EXE): main.cpp $(OBJ)
# 	$(CXX) $(INCLUDES) $(CXXFLAGS) $^ -o $@

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(info Building objects...)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -o $@ -c $<



clean:
	rm -rf *.o
	rm -rf obj/*.o
	rm -rf $(EXE)
	rm -rf client
	rm -rf server