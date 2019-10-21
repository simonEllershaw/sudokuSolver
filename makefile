sudoku: main.o sudoku.o helper.o
	g++ main.o sudoku.o helper.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -Wall -g -c main.cpp

sudoku.o: sudoku.cpp sudoku.h helper.h
	g++ -Wall -g -c sudoku.cpp

helper.o: helper.cpp helper.h sudoku.h
	g++ -Wall -g -c helper.cpp

clean:
	rm -f *.o main
