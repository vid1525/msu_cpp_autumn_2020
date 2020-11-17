CXX_FLAGS=-O2
CXX_VERSION=-std=c++1z
CCXX=g++

all: main

main: main.cpp Format.h
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) main.cpp -o main

test: main
	./main 2> test_error.log

clean:
	rm -f *.o
	rm -f test_error.log

help:
	cat README.md
