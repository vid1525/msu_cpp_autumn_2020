CXX_FLAGS=-Wall -Werror -O2
CXX_VERSION=-std=c++1z
CCXX=g++

all: test

Allocator.o: Allocator.cpp Allocator.h
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) -lm Allocator.cpp -o Allocator.o
test.o: test.cpp
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) -lm test.cpp -o test.o
test: test.o Allocator.o
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) -lm test.o Allocator.o -o test
clean:
	rm -f *.o test
help:
	cat README.md
