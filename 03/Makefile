CXX_FLAGS=-Wall -Werror -O2
CXX_VERSION=-std=c++1z
CCXX=g++

all: 

Matirx.o: Matrix.cpp
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) Matrix.cpp -o Matrix.o

test: main
	./main

clean:
	rm -f *.o test_output/tmp
help:
	cat README.md
