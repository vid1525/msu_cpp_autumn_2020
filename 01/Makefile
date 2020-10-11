CXX_FLAGS=-Wall -Werror -O2
CXX_VERSION=-std=c++1z
CCXX=g++

all: alloc

Allocator.o: Allocator.cpp Allocator.h
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) -lm Allocator.cpp -o Allocator.o
main.o: main.cpp
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) -lm main.cpp -o main.o
alloc: main.o Allocator.o
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) -lm main.o Allocator.o -o alloc
clean:
	rm -f *.o alloc
