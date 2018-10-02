//======================
//    Sudoku Solver
//======================
//
//Started On - October 2nd, 2018
//Author - Arjun Aravind
//Objective - This is an application written in C++ which takes in Sudoku puzzles and outputs the solution.

#include<iostream>
using namespace std;

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
		sudokuFrame=new int*[9];
		
		for(i=0; i<9; i++){
			sudokuFrame[i]=new int[9];
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

		for(i=0; i<9; i++){
			for(j=0; j<9; j++){
				cout<<"Enter value for cell["<<i+1<<"]["<<j+1<<"] --> ";
				cin>>sudokuFrame[i][j];
			}
		}
	}
	
	/**	displayFrame()
		Displays the values stored in the SudokuFrame object.
		@param none
		@return none
	*/
	public:void displayFrame(){
		for(i=0; i<9; i++){
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
		for(i=0; i<9; i++){
			delete[] sudokuFrame[i];
		}
	}

};

int main(){
	SudokuFrame s;	
	s.displayFrame();

	return 0;
}
