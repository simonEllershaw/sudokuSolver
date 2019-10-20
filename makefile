main: main.o sudoku.o #helper.o
	g++ main.o sudoku.o -o main #helper.o -o main

main.o: main.cpp sudoku.h
	g++ -Wall -g -c main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -Wall -g -c sudoku.cpp

# helper.o: helper.cpp helper.h sudoku.h
# 	g++ -Wall -g -c helper.cpp

clean:
	rm -f *.o main
