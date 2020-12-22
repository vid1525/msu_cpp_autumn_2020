CXX_FLAGS=-pthread
CXX_VERSION=-std=c++1z
CCXX=g++

all: main

main: main.cpp ThreadPool.h
	$(CCXX) $(CXX_FLAGS) $(CXX_VERSION) main.cpp -o main

test: main
	./main

clean:
	rm -f *.o

help:
	cat README.md
