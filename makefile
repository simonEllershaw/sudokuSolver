sudoku: main.o sudoku.o helper.o
	g++ main.o sudoku.o helper.o -o sudoku

%.o: %.cpp
	g++ -Wall -g -c $<

main.o: sudoku.h

sudoku.o: sudoku.h helper.h

helper.o: helper.h sudoku.h

clean:
	rm -f *.o main
