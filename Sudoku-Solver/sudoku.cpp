//======================
//    Sudoku Solver
//======================
//
//Started On - October 2nd, 2018
//Author - Arjun Aravind
//Objective - This is an application written in C++ which takes in Sudoku puzzles and outputs the solution.

#include<iostream>
using namespace std;

#define ROWS 9
#define COLS 9

#define TRUE 1
#define FALSE 0

typedef int boolean;

/**	Sudoku-Frame (class)
	Contains functions and data members necessary fo holding the values in the sudoku-puzzle.
*/
class SudokuFrame{
	int** sudokuFrame; //This pointer will hold all the values in the matrix.
	int i, j; //iterator variables
	
	/**	Sudoku-Frame() (Constructor)
		This constructor calls the initFrame() and getFrameValues() functions.
		@param none
		@return none
	*/
	public:SudokuFrame(){
		initFrame();
		getFrameValues();
	}
	
	/**	Sudoku-Frame (destructor)
		Calls the deleteFrame() function.
		@param none
		@return none
	*/
	public:~SudokuFrame(){
		deleteFrame();
	}
	
	/**	initFrame()
		Initialises the Sudoku-Frame by dynamically allocating 9 columns and 9 rows.
		@param none
		@return none
	*/
	void initFrame(){
		sudokuFrame=new int*[ROWS];
		
		for(i=0; i<ROWS; i++){
			sudokuFrame[i]=new int[ROWS];
		}
	}

	/**	getFrameValues()
		Gets the values to be inputted into the Sudoku-Frame.
		@param none
		@return none
	*/
	void getFrameValues(){
		cout<<"Enter the values for the Sudoku puzzle here!\n";
		cout<<"Enter the particular value when prompted. Enter 0 if cell is empty.\n\n";

		for(i=0; i<ROWS; i++){
			for(j=0; j<COLS; j++){
				cout<<"Enter value for cell["<<i+1<<"]["<<j+1<<"] --> ";
				cin>>sudokuFrame[i][j];
			}
		}
	}
	
	/**	setCellValue()
		Takes in the row and col number and then assigns the passed 'num' value
		to that particular cell.
		@param row int row of the specified cell
		@param col int col of the specified cell
		@return none
	*/
	public:void setCellValue(int row, int col, int num){
		sudokuFrame[row][col]=num;
	}
	
	/**	getCellValue()
		Returns the value of the cell at the specified row and col.
		@param row int row of the specified cell
		@param col int col of the specified cell
		@return int cellValue value at the specified cell
	*/
	public:int getCellValue(int row, int col){
		int cellValue=sudokuFrame[row][col];
		return cellValue;
	}

	/**	displayFrame()
		Displays the values stored in the SudokuFrame object.
		@param none
		@return none
	*/
	public:void displayFrame(){
		for(i=0; i<ROWS; i++){
			cout<<"+---+---+---+---+---+---+---+---+---+\n";
			for(j=0; j<9; j++){
				cout<<"| ";
				if(sudokuFrame[i][j]==0) cout<<"  ";
				else cout<<sudokuFrame[i][j]<<" ";
			}
			cout<<"|\n";
		}
		cout<<"+---+---+---+---+---+---+---+---+---+\n";
	}
	
	/**	deleteFrame()
		Deletes the dynamically-allocated values in the frame.
		@param none
		@return none
	*/
	void deleteFrame(){
		for(i=0; i<ROWS; i++){
			delete[] sudokuFrame[i];
		}
	}

};


/**	SudokuSolver (class)
	Takes in the SudokuFrame object and solves the Sudoku Puzzle.
*/
class SudokuSolver{
	
	int i, j; //Iterator variables
	SudokuFrame frame;

	boolean checkCellValidity(int row, int col, int currentValue){

		//Checking if value exists in same column
		for(i=0; i<ROWS; i++){
			if(i!=row){
				int comparingValue=frame.getCellValue(i,col);
				if(comparingValue==currentValue) return FALSE;
			}
		}

		//Checking if value exists in same row
		for(j=0; j<COLS; j++){
			if(j!=col){
				int comparingValue=frame.getCellValue(row,j);
				if(comparingValue==currentValue) return FALSE;
			}
		}

		return TRUE;
	}

};


int main(){
	SudokuSolver s;	

	return 0;
}
