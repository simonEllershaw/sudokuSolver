#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

void test_board_is_complete(const char inputFname[])
{
  char board[9][9];
  load_board(inputFname, board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";
}

/* Test placing functionality */
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


/* Test saving functionality */
void test_save(const char inputFname[], const char outputFname[])
{
  char board[9][9];
  load_board(inputFname, board);
  if (save_board(outputFname, board))
    cout << "Save board to " << outputFname << " successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';
}


/* Test solving functionality */
void test_solve(const char inputFname[], bool count_recursion = false)
{
  char board[9][9];
  load_board(inputFname, board);
  display_board(board);
  if (solve_board(board, count_recursion)) {
    cout << inputFname << " has a solution:" << '\n';
    display_board(board);
  }
  else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';
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

  test_board_is_complete("easy.dat");
  test_board_is_complete("easy-solution.dat");

  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  cout << "Test " << testNumber++ << ": Pass" << endl;
  test_placement("I8", '1', board);
  /* Additional testing */

  cout << "Test " << testNumber++ << ": Can overwrite a digit" << endl;
  test_placement("I8", '3', board);
  cout << "Test " << testNumber++ << ": Repeated placement fails" << endl;
  test_placement("I8", '3', board);
  cout << "Test " << testNumber++ << ": Row clash fails" << endl;
  test_placement("A2", '1', board);
  cout << "Test " << testNumber++ << ": Col clash fails" << endl;
  test_placement("A8", '6', board);
  cout << "Test " << testNumber++ << ": Row out of bounds fails" << endl;
  test_placement("Q8", '1', board);
  cout << "Test " << testNumber++ << ": Col out of bounds fails" << endl;
  test_placement("A0", '1', board);
  cout << "Test " << testNumber++ << ": Double digit position fails" << endl;
  test_placement("A10", '9', board);


  cout << "=================== Question 3 ===================" << "\n\n";

  test_save("easy.dat" , "easy-copy.dat");

  cout << "=================== Question 4 ===================" << "\n\n";

  test_solve("easy.dat");
  test_solve("medium.dat");

  cout << "=================== Question 5 ===================" << "\n\n";

  bool count_recursion = true;
  test_solve("mystery1.dat", count_recursion);
  test_solve("mystery2.dat", count_recursion);
  test_solve("mystery3.dat", count_recursion);


  return 0;
}
