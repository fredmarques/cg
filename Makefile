CPP      = g++
CC       = gcc
OBJ      = main.o programwindow.o 
LINKOBJ  = main.o programwindow.o 
BIN      = program.out
# LDFLAGS  = -lglut -lGLU -lGL -lm -lGLEW -Wconversion
LDFLAGS  = -lglut -lGLU -lGL -lm -lGLEW
CXXFLAGS = -Wall $(LDFLAGS)
RM       = rm -f
SRC 	 = ./src/

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(CXXFLAGS)

main.o: $(SRC)main.cpp
	$(CPP) -c $(SRC)main.cpp -o main.o $(CXXFLAGS)

programwindow.o: $(SRC)programwindow.cpp
	$(CPP) -c $(SRC)programwindow.cpp -o programwindow.o $(CXXFLAGS)
