#ifndef SUDOKU_H
#define SUDOKU_H

/////////////////// Given functions /////////////////////////////////

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

//////////////////Implemented functions//////////////////////////////

/* Takes a board and returns true if all positions are occupied by digits
and false otherwise. Does not check if logically valid */
bool is_complete(const char board[9][9]);

/* Function to place a digit at a specific position on the board. This occurs
as long as the position and digit inputs are valid and don't break sudoku rules.
Returns true with a successful placement and false otherwise */
bool make_move(const char input_position[], const char digit, char board[9][9]);

/* Saves a board state to a given filename. Returns true if successful and false
otherwise */
bool save_board(const char filename[], const char board[9][9]);

/*Returns true if board can be solved (with board updated to solved illustrates
  and false otherwise (with the board in it's original state)
  count_recursion is an optional parameter to toggle on and off counting recurision
  */
bool solve_board(char board[9][9], bool count_recursion);

// Helper functions

/* Returns true if position is within bounds of the board returns false
otherwise */
bool position_is_valid(const char position[]);

/* Return true if digit already present in row or col and false otherwise*/
bool digit_in_row_or_col(const int position[], const char digit, char board[9][9]);

/* Return true if digit already present in the 4 subsquare cells not in
  the position's row or column and false otherwise*/
bool digit_in_subsquare(const int position[], const char digit, char board[9][9]);

/* Takes a char position and updates an int array with it's conversion
  e.g. 'A1' -> {0,0}*/
void charPositionToArrayIndex(const char char_position[], int index_position[]);

/* Updates board with a digit at a specified position*/
void updateBoard(const char char_position[2], char digit, char board[9][9]);

/* Gets value of board for at a cell specified by row, col */
char getBoardValue(const char char_position[2] , char board[9][9]);

/* Recursive backtracking algorithm that retruns true if the current board
  state can be solved and false otherwises. If it can be solved the board
  state is updated to the solution
*/
bool solve_board_helper(char board[9][9], char position[], int& recursion_count);

/* Returns true if next cell can be solved from current board state.
    False otherwise */
bool can_solve_next_cell(char board[9][9], char row, char col, int& recursion_count);

#endif
