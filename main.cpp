#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

// Test function for make_move(......)
void test_placement(const char position[2], const char digit, char board[9][9])
{
  bool move_valid = make_move(position, digit, board);
  // Output if move valid
  cout << "Putting '"<< digit << "' into " << position <<" is ";
  if (!move_valid)
    cout << "NOT ";
  cout << "a valid move.";
  // If move has been made re-print board
  if(move_valid)
  {
    cout <<" The board is:" << '\n';
    display_board(board);
  }
  cout << endl;
}

int main() {
  int testNumber = 1;
  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";


  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  cout << "Test " << testNumber++ << ": Pass" << endl;
  test_placement("I8", '1', board);
  /* Additional testing */
  cout << "Test " << testNumber++ << ": Repeated placement fails" << endl;
  test_placement("I8", '1', board);
  cout << "Test " << testNumber++ << ": Row clash fails" << endl;
  test_placement("A2", '1', board);
  cout << "Test " << testNumber++ << ": Col clash fails" << endl;
  test_placement("A8", '6', board);
  cout << "Test " << testNumber++ << ": Row out of bounds fails" << endl;
  test_placement("Q8", '1', board);
  cout << "Test " << testNumber++ << ": Col out of bounds fails" << endl;
  test_placement("A0", '1', board);
  cout << "Test " << testNumber++ << ": Digit already in subsquare fails" << endl;
  test_placement("A2", '2', board);
  cout << "Test " << testNumber++ << ": Double digit position fails" << endl;
  test_placement("A10", '9', board);


  cout << "=================== Question 3 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  cout << "=================== Question 4 ===================" << "\n\n";

  load_board("easy.dat", board);
  display_board(board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // load_board("medium.dat", board);
  // if (solve_board(board)) {
  //   display_board(board);
  // } else
  //   cout << "A solution cannot be found." << '\n';
  // cout << '\n';

/*
	// write more tests

  cout << "=================== Question 5 ===================" << "\n\n";

	// write more tests
*/
  cout << "=================== Question 5 ===================" << "\n\n";


  return 0;
}
