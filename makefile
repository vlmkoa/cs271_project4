all: test usecase

test: test_bst.o
	g++ -o test test_bst.o
	./test

test_bst.o: test_bst.cpp bst.h bst.cpp
	g++ -c test_bst.cpp

usecase: main.o bst.o
	g++ -o main main.o bst.o
	./main

usecase.o: main.cpp bst.h
	g++ -std=c++17 -c main.cpp

bst.o: bst.cpp bst.h
	g++ -c bst.cpp

clean:
	rm -f test main *.o