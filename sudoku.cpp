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


/* Wrapper to begin recursive backtracking search
 * Returns true if board can be solved (with board updated to solved illustrates
 * and false otherwise (with the board in it's original state)
 * count_recursion is an optional parameter to toggle on and off counting recurision
*/
bool solve_board(char board[9][9], bool count_recursion = false)
{
  // Set up for recursion count;
  int num_recursive_calls;
  if(count_recursion)
    num_recursive_calls = 1;
  else
    num_recursive_calls = 0;

  // Call to solve board starting at position A1
  char initial_position[] = "A1";
  bool result = solve_board_helper(board, initial_position, num_recursive_calls);

  // Print out for recursion count
  if(count_recursion)
  {
    cout << "It took " << num_recursive_calls
        << " recursions to solve this board" << endl;
  }
  return result;
}


/// Helper functions/////////

/* Returns true if position is within bounds of the board returns false
 * otherwise
 */
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


/* Return true if digit already present in row or col and false otherwise
 * Algorthm inspired by:
 * https://spin.atomicobject.com/2012/06/18/solving-sudoku-in-c-with-recursive-backtracking/
 */
bool digit_in_row_or_col(const int position[], const char digit, char board[9][9])
{
  for(int index = 0; index < 9; index++)
  {
    if(board[position[0]][index] == digit) return true;
    if(board[index][position[1]] == digit) return true;
  }
  return false;
}


/* Return true if digit already present in the 4 subsquare cells not in
 * the position's row or column and false otherwise
 * Algorthm inspired by:
 * https://spin.atomicobject.com/2012/06/18/solving-sudoku-in-c-with-recursive-backtracking/
 */
bool digit_in_subsquare(const int position[], const char digit, char board[9][9])
{
  // Calc the lowest indexed cell in the position's square (int div rounds down)
  int subsquare_min_row = position[0] - (position[0] % 3);
  int subsquare_min_col = position[1] - (position[1] % 3);
  // Calc the indices of the 4 unchecked subsquare cells
  int row1 = (position[0]+2)%3;
  int row2 = (position[0]+4)%3;
  int col1 = (position[1]+2)%3;
  int col2 = (position[1]+4)%3;

  // Check each of the 4 cells
  if(board[row1+subsquare_min_row][col1+subsquare_min_col] == digit)
    return true;
  if(board[row2+subsquare_min_row][col1+subsquare_min_col] == digit)
    return true;
  if(board[row1+subsquare_min_row][col2+subsquare_min_col] == digit)
    return true;
  if(board[row2+subsquare_min_row][col2+subsquare_min_col] == digit)
    return true;

  // If not matches found return false
  return false;
}

/* Takes a char position and updates an int array with it's conversion
 * e.g. 'A1' -> {0,0}
 */
void charPositionToArrayIndex(const char char_position[], int index_position[])
{
  // 'A' and '1' are equivalent to 0,0 in the board array
  index_position[0] = static_cast<int>(char_position[0])-static_cast<int>('A');
  index_position[1] = static_cast<int>(char_position[1]) - static_cast<int>('1');
}

/* Updates board with a digit at a specified position*/
void updateBoard(const char char_position[2], char digit, char board[9][9])
{
  int index_position[2];
  charPositionToArrayIndex(char_position, index_position);
  board[index_position[0]][index_position[1]] = digit;
}

/* Gets value of board for at a cell specified by row, col */
char getBoardValue(const char char_position[2] , char board[9][9])
{
  int index_position[2];
  charPositionToArrayIndex(char_position, index_position);
  return board[index_position[0]][index_position[1]];
}

/* Recursive backtracking algorithm that retruns true if the current board
 * state can be solved and false otherwises. If it can be solved the board
 * state is updated to the solution
 * Algorithm inspired by following web page:
 * https://spin.atomicobject.com/2012/06/18/solving-sudoku-in-c-with-recursive-backtracking/
*/
bool solve_board_helper(char board[9][9], char position[], int& recursion_count)
{
  // Optional count of number of recusions
  if(recursion_count)
  {
    recursion_count++;
  }

  // Base case- The whole board has been iterated over and valid digit found
  // for each cell so return true
  if(position[0] == 'J')
    return true;

  // If value already present it was given by input file so recurse onto next
  // cell straight away
  if(!(getBoardValue(position, board) == '.'))
    return can_solve_next_cell(board, position[0], position[1], recursion_count);

  // Recursive step- Attempt to place digit 1 to 9 in the cell. If the move can
  // be made and the next cell can be solved recursively then it is a solution.
  for(char test_digit = '1'; test_digit <= '9'; test_digit ++)
    if(make_move(position, test_digit, board))
      if(can_solve_next_cell(board, position[0], position[1], recursion_count))
        return true;

  // If a digit cannot be placed in the cell with this board state backtracking
  // is required so reset cell value to '.' and return false.
  // Base case if board has no solution- number of recursions not printed.
  updateBoard(position, '.', board);
  return false;
}

/* Returns true if next cell can be solved from current board state.
 * False otherwise
 */
bool can_solve_next_cell(char board[9][9], char row, char col, int& recursion_count)
{
  // Select next cell
  // If in col 9 next cell is the start of next row
  if(col == '9')
  {
    row ++;
    col = '1';
  }
  // Otherwise just the next col in row
  else
  {
    col++;
  }

  // Attempt to solve board with updated position
  char updatedPosition[3] = {row, col, '\0'};
  return solve_board_helper(board, updatedPosition, recursion_count);
}
