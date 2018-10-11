#include"sudoku.h"

int main(){
	SudokuSolver s;

	s.displayFrame(); //We display the unsolved sudoku puzzle here
	s.solve();
	s.displayFrame(); //We display the solved sudoku puzzle here

	return 0;
}
