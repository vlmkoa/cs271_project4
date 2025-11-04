all: clean test usecase

test: test_bst.o
	g++ -o test test_bst.o

test_bst.o: test_bst.cpp bst.h bst.cpp
	g++ -std=c++17 -c test_bst.cpp

usecase: main.o
	g++ -o usecase main.o

main.o: main.cpp bst.h bst.cpp usecase.cpp
	g++ -std=c++17 -c main.cpp

clean:
	rm -f test usecase *.o