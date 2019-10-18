#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

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


/* Internal helper func- returns true if position is within bounds of the board
  returns false otherwise */
bool position_is_valid(const char position[])
{
  // Check row is valid
  if(position[0] < 'A' || position[0] > 'I')
    return false;
  // Check column is valid
  if(!isdigit(position[1]))
    return false;
  // Check position is 2 char long i.e. not A10
  if(strlen(position) != 2)
    return false;
  return true;
}


/* Internal helper func- return true if digit already present in row
    and false otherwise*/
bool digit_in_row(const int row_index, const char digit, char board[9][9])
{
  for(int col = 0; col < 9; col++)
    if(board[row_index][col] == digit){
      return true;
    }
  return false;
}


/* Internal helper func- return ture if digit already present in col
    and false otherwise*/
bool digit_in_col(const int col_index, const char digit, char board[9][9])
{
  for(int row = 0; row < 9; row++)
    if(board[row][col_index] == digit){
      return true;
    }
  return false;
}

/* Internal helper func- return true if digit already present in subsquare
    and false otherwise*/
bool digit_in_subsquare(const int position[], const char digit, char board[9][9])
{
  int min_row, min_col;
  // Calc the lowest indexed cell in the position's square (int div rounds down)
  min_row = position[0] - (position[0] % 3);
  min_col = position[1] - (position[1] % 3);

  // Iterate over all cells in square checking non have value equal to digit
  for(int row_count=0; row_count < 3; row_count++)
    for(int col_count=0; col_count < 3; col_count++)
      if(board[min_row + row_count][min_col + col_count] == digit)
        return true;

  // If not matches found return false
  return false;
}

/* Internal helper func- updates board with a digit at a specified position*/
void updateBoard(const int position[2], char digit, char board[9][9])
{
  board[position[0]][position[1]] = digit;
}


/* Function to place a digit at a specific position on the board. This occurs
as long as the position and digit inputs are valid and don't break sudoku rules.
Returns true with a successful placement and false otherwise */
bool make_move(const char input_position[], const char digit, char board[9][9])
{
  // Check input is valid
  if(!(position_is_valid(input_position) && isdigit(digit) && digit > '0'))
  {
    cout << "iterate: " << input_position << " " << digit << endl;
    cout << position_is_valid(input_position) << endl;
    cout << isdigit(digit) << endl;
    cout << (digit > '0') << endl;
    return false;
  }

  // Map position from char to int array equal to board indices
  // Note mapping A->0 and 1->0
  const int position[2] = {static_cast<int>(input_position[0])-static_cast<int>('A'),
                  static_cast<int>(input_position[1]) - static_cast<int>('1')};

  // Check for clashes with current board
  if(digit_in_row(position[0], digit, board))
    return false;
  if(digit_in_col(position[1], digit, board))
    return false;
  if(digit_in_subsquare(position, digit, board))
    return false;

  // Place digit on the board
  updateBoard(position, digit, board);
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


// https://spin.atomicobject.com/2012/06/18/solving-sudoku-in-c-with-recursive-backtracking/

char getBoardValue(char board[9][9], char row, char col)
{
  int row_converted = static_cast<int>(row)-static_cast<int>('A');
  int col_converted = static_cast<int>(col) - static_cast<int>('1');
  return board[row_converted][col_converted];
}

bool can_solve_next_cell(char board[9][9], char row, char col)
{
  if(col == '9')
  {
    if(solve_board(board, ++row, '1'))
      return true;
  }
  else
  {
    if(solve_board(board, row, ++col))
    {
      cout << row << " " << col;
      return true;
    }
  }
  return false;
}

bool solve_board(char board[9][9], char row, char col)
{
  // Base case
  display_board(board);
  char position[3] = {row, col, '\0'};

  if(row == 'J')
    return true;

  if(!(getBoardValue(board, row, col) == '.'))
    return can_solve_next_cell(board, row, col);

  cout << position << endl;
  for(char test_digit = '1'; test_digit <= '9'; test_digit ++)
    if(make_move(position, test_digit, board)){
      cout << test_digit << endl;
      if(can_solve_next_cell(board, row, col))
        return true;
    }

  return false;
}
