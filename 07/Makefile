CXX_FLAGS=-O2 -Wall
CXX_VERSION=-std=c++1z
CCXX=g++

all: main

main: main.cpp Vector.h
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) main.cpp -o main

test: main
	./main

clean:
	rm -f *.o

help:
	cat README.md
