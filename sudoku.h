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
  and false otherwise (with the board in it's original state) */
bool solve_board(char board[9][9]);


#endif
