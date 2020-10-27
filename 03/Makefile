CXX_FLAGS=-Wall -Werror -O2
CXX_VERSION=-std=c++1z
CCXX=g++

all: main

Matirx.o: Matrix.cpp Matrix.h
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) Matrix.cpp -o Matrix.o

main.o: main.cpp
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) main.cpp -o main.o

main: main.o Matrix.o
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) main.o Matrix.o -o main

test: main
	./main

clean:
	rm -f *.o test_output/tmp
help:
	cat README.md

scratch.o: scratch.cpp
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) scratch.cpp -o scratch.o

scratch: Matrix.o scratch.o
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) Matrix.o scratch.o -o scratch
