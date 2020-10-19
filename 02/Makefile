CXX_FLAGS=-Wall -Werror -O2
CXX_VERSION=-std=c++1z
CCXX=g++

all: test

Parser.o: Parser.cpp Parser.h
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) Parser.cpp -o Parser.o

main.o: main.cpp
	$(CCXX) -c $(CXX_FLAGS) $(CXX_VERSION) main.cpp -o main.o

test: main.o Parser.o
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) main.o Parser.o -o test
	./test
clean:
	rm -f *.o test_output/tmp
help:
	cat README.md
