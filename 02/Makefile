CXX_FLAGS=-Wall -Werror -O2
CXX_VERSION=-std=c++1z
CCXX=g++

all: main

main: main.cpp Parser.h
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) main.cpp -o main

test: main
	./main

clean:
	rm -f *.o test_output/tmp
help:
	cat README.md
