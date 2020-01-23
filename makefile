# VPATH=./src
#vpath %.h ./include
#vpath %.o ./obj
#vpath %.cpp ./src

CC=mpicxx
CFLAGS=-std=c++11 -lm -llapack
LDFLAGS=-I./include 

EXE=FE.x

#SRC= src/main.cpp $(filter-out %main.cpp, $(wildcard src/*.cpp))
#OBJ=$(filter-out %main.o, $(patsubst src/%.cpp,obj/%.o,$(SRC)))

SRC= $(wildcard src/*.cpp)
OBJ=$(patsubst src/%.cpp,obj/%.o,$(SRC))


all: $(OBJ)
	$(CC) $^ -o $(EXE) $(CFLAGS) $(LDFLAGS)

obj/%.o: src/%.cpp 
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)


clean:
	rm -fd obj/* $(EXE)

show:
	@echo OBJ = $(OBJ)
	@echo SRC = $(SRC)
