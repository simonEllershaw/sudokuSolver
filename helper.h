#ifndef HELPER_H
#define HELPER_H

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
