CXX_FLAGS=-Wall -Werror -O2
CXX_VERSION=-std=c++1z
CCXX=g++

all: main

BigInt.o: BigInt.cpp BigInt.h
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) BigInt.cpp -o BigInt.o

main.o: main.cpp
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) main.cpp -o main.o

main: main.o BigInt.o
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) main.o BigInt.o -o main

test: main
	./main

clean:
	rm -f *.o test_output/tmp
help:
	cat README.md
