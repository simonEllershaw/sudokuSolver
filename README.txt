Sudoku solver

Takes a data file (examples given as .dat files) in the form of 9x9 grids.
E.g.
  ...1.83..
  24..5....
  ..8....61
  ..4..9..3
  .6.....2.
  3..8..1..
  17....9..
  ....1..52
  ..27.4...

And outputs solution (if there is one) to the command line. The solution is found
using recursive backtracking.

A test programme can also be run to show the functionality behind the solver

To solve a sudoku enter commands:
  make
  ./sudoku.exe filename

Or to run the test programme:
  ./sudoku.exe test
