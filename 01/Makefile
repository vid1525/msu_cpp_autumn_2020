CXX_FLAGS=-Wall -Werror -O2
CXX_VERSION=-std=c++1z
CXX_COMPILER=g++

all: alloc

Allocator.o: Allocator.cpp
	$(CXX_COMPILER) -c $(CXX_FLAGS) $(CXX_VERSION) -lm Allocator.cpp -o Allocator.o
main.o: main.cpp
	$(CXX_COMPILER) -c $(CXX_FLAGS) $(CXX_VERSION) -lm main.cpp -o main.o
alloc: main.o Allocator.o
	$(CXX_COMPILER) $(CXX_FLAGS) $(CXX_VERSION) -lm main.o Allocator.o -o alloc
clean:
	rm -f *.o alloc
