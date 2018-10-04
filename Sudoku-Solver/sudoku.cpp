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
	int** editableFrame; //This pointer will tell us all the values which are editable
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
		editableFrame=new int*[ROWS];
		
		for(i=0; i<ROWS; i++){
			sudokuFrame[i]=new int[ROWS];
			editableFrame[i]=new int[ROWS];
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

				if(sudokuFrame[i][j]==0) editableFrame[i][j]=0;
				else editableFrame[i][j]=1;
			}
		}
	}
	
	/**	setCellValue()
		Takes in the row and col number and then assigns the passed 'num' value
		to that particular cell.
		@param row (int) row of the specified cell
		@param col (int) col of the specified cell
		@return none
	*/
	public:void setCellValue(int row, int col, int num){
		if(editableFrame[row][col]==1)	sudokuFrame[row][col]=num;
	}
	
	/**	getCellValue()
		Returns the value of the cell at the specified row and col.
		@param row (int) row of the specified cell
		@param col (int) col of the specified cell
		@return (int) cellValue value at the specified cell
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
			delete[] editableFrame[i];
		}
	}

};


/**	SudokuSolver (class)
	Takes in the SudokuFrame object and solves the Sudoku Puzzle.
*/
class SudokuSolver{
	
	int i, j; //Iterator variables
	SudokuFrame frame;
	
	/**	checkCellValidity
		Checks if the value is valid or not.
		@param row (int) row of the required value
		@param col (int) col of the required value
		@param currentValue (int) the required value
		@return (boolean) whether the value is valid or not in the sudoku frame
	*/
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

		//Checking if value exists in the same 3x3 square block
		if(check3x3SquareValidity(row,col,currentValue)==FALSE) return FALSE;

		return TRUE;
	}
	
	/**	check3x3SquareValidity()
		Checks if the same value is also present in the same 3x3 grid block.
		@param row (int) row of the required cell
		@param col (int) col of the required cell
		@param currentValue (int) required value
		@return (boolean) whether the value is present or not
	*/
	boolean check3x3SquareValidity(int row, int col, int currentValue){
		int rowStart=(row/3)*3;
		int rowEnd=(rowStart+2);

		int colStart=(col/3)*3;
		int colEnd=(colStart+2);

		for(i=rowStart; i<=rowEnd; i++){
			for(j=colStart; j<=colEnd; j++){
				if(frame.getCellValue(i,j)==currentValue) return FALSE;
			}
		}

		return TRUE;
		
	}
	
	/**	displayFrame()
		Displays the sudoku frame by calling the displayFrame() func of the
		SudokuFrame object.
		@param none
		@return none
	*/
	void displayFrame(){
		frame.displayFrame();
	}
	
};


int main(){
	SudokuSolver s;	
	
	s.displayFrame();

	return 0;
}
