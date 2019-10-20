#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"
#include "helper.h"

using namespace std;


/* You are pre-supplied with the functions below. Add your own
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++)
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */


/* Takes a board and returns true if all positions are occupied by digits
and false otherwise. Does not check if logically valid */
bool is_complete(const char board[9][9])
{
  // Iterate across all positions
  for(int row = 0; row < 9; row ++)
    for(int col=0; col < 9; col ++)
        // If not a digit return false
        if(!(isdigit(board[row][col])))
          return false;
  // Else return true
  return true;
}


/* Function to place a digit at a specific position on the board. This occurs
as long as the position and digit inputs are valid and don't break sudoku rules.
Returns true with a successful placement and false otherwise */
bool make_move(const char char_position[], const char digit, char board[9][9])
{
  // Check input is valid
  if(!(position_is_valid(char_position) && isdigit(digit) && digit > '0'))
    return false;

  // Convert from char position to int indices
  int index_position[2];
  charPositionToArrayIndex(char_position, index_position);

  // Check for clashes with current board
  if(digit_in_row_or_col(index_position, digit, board))
    return false;
  if(digit_in_subsquare(index_position, digit, board))
    return false;

  // Place digit on the board
  updateBoard(char_position, digit, board);
  return true;
}


/* Saves a board state to a given filename. Returns true if successful and false
otherwise */
bool save_board(const char filename[], const char board[9][9])
{
  // Open stream and check stream is functioning
  ofstream out_stream;
  out_stream.open(filename);
  if(out_stream.fail())
    return false;

  // Iterate through each cell saving it's character to file
  for(int row = 0; row < 9; row ++)
  {
    for(int col = 0; col < 9; col++)
      out_stream.put(board[row][col]);
    // Start new row
    out_stream.put('\n');
  }

  out_stream.close();
  return true;
}


/*Returns true if board can be solved (with board updated to solved illustrates
  and false otherwise (with the board in it's original state) */
bool solve_board(char board[9][9])
{
  // Wrapper to begin recursive backtracking search
  char initial_position[] = "A1";
  return solve_board_helper(board, initial_position);
}
