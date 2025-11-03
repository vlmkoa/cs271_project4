all: clean test usecase

test: test_bst.o
	g++ -o test test_bst.o
	./test

test_bst.o: test_bst.cpp bst.h bst.cpp
	g++ -c test_bst.cpp

usecase: main.o
	g++ -o main main.o
	./main

main.o: main.cpp bst.h bst.cpp
	g++ -std=c++17 -c main.cpp

clean:
	rm -f test main *.o