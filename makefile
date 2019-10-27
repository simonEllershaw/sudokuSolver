sudoku: sudoku.o helper.o test.o
	g++ sudoku.o helper.o test.o -o sudoku

%.o: %.cpp
	g++ -Wall -g -c $<

test.o: sudoku.h test.h

sudoku.o: sudoku.h helper.h test.h

helper.o: helper.h sudoku.h

clean:
	rm -f *.o main

.PHONY: clean
