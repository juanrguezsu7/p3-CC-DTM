CC = g++
CXXFLAGS = -std=c++17 -o 
OBJ0 = main
OBJ1 = input/DTMInput
OBJ2 = structure/DTM
OBJ3 = structure/state
OBJ4 = structure/symbol
OBJ5 = structure/transitionSet
OBJ6 = structure/tape

all: clean ${OBJ0}

${OBJ0}:
	${CC} ${CXXFLAGS} $@ src/$@.cpp src/${OBJ1}.cpp src/${OBJ2}.cpp src/${OBJ3}.cpp src/${OBJ4}.cpp src/${OBJ5}.cpp src/${OBJ6}.cpp

clean:
	del /f ${OBJ0}.exe
