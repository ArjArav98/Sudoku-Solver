/*
 *========================
 *    Sudoku Validator
 *========================
 *
 * Started On: October 18th, 2018
 * Author: Arjun Aravind
 * Objective: To verify whether a completed Sudoku puzzle is valid or not.
*/

#include<iostream>
#include<fstream>
using namespace std;

class SudokuFrame{

	int sudokuFrame[9][9];

	public:SudokuFrame(){
		menu();
	}
	
	/**
	  *	@desc This function generates a menu for the user at the starting of the
	  *	program execution. This lets the user select the input method for entering
	  *	the values for the Sudoku Puzzle into the SudokuFrame object.
	  *
	  *	@param none
	  *	@return none
	*/
	private:void menu(){

                cout<<"\n======================\n";
                cout<<"   Sudoku Validator\n";
                cout<<"======================\n\n";

                cout<<"Welcome to Sudoku Validator!\n";
                cout<<"Before we start, you will have to input the puzzle into this program.\n\n";
                cout<<"You can either:-\n";
                cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
                cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
                cout<<"\t   The file must not have a name > 30 characters.\n";
                cout<<"\t   The file must be in the same directory as this C++ file.\n";
                cout<<"\t   The file must have all 81 values seperated with spaces.\n";
                cout<<"\t   Blank cells must be filled in as 0 (eg; 1 2 9 8 1 9 ...).\n";
                cout<<"\t   --> ";

                int option;
                cin>>option;

                if(option==1) readFrameValues();
                else if(option==2) readFrameValuesFile();
                else{
                        while(true){
                                cout<<"\nYou seem to have entered an invalid option. Try again.\n";
                                cout<<"\t   --> ";
                                cin>>option;

                                if(option==1) readFrameValues();
                                else if(option==2) readFrameValuesFile();
                                else continue;

                                break;
                        }
                }

        }

	/**
          *     @desc Reads the values for the Sudoku Frame cell-by-cell.
          *     @param none
          *     @return none
        */
        private:void readFrameValues(){
                cout<<"\nEnter the specified value when prompted.\n";
                cout<<"Enter 0 if cell is empty.\n\n";

		int rowIter, colIter;

                for(rowIter=0; rowIter<9; rowIter++){ //Iterating over cells to read vals.
                        for(colIter=0; colIter<9; colIter++){
                                int enteredValue;

                                cout<<"Enter value for cell["<<rowIter+1<<"]["<<colIter+1<<"] --> ";
                                cin>>enteredValue;

                                if(!(enteredValue>=1 && enteredValue<=9)){ //Checking for bounds in input.
                                        while(true){ //We loop until valid input is read from user.
                                                cout<<"Oops! You seem to have entered a wrong value! Try again.\n";
                                                cout<<"Enter value for cell ["<<rowIter+1<<"]["<<colIter+1<<"] --> ";
                                                cin>>enteredValue;

                                                if(enteredValue>=1 && enteredValue<=9) break;
                                        }
                                }

                                sudokuFrame[rowIter][colIter]=enteredValue;
                        }
                        cout<<"-------\n"; //Display a break after every row for convenience.
                }
        }
	
	/**
	  *	@desc This function reads values from a specified file.
	  *	@param none
	  *	@return none
	 */
	private:void readFrameValuesFile(){
		
		int rowIter, colIter;
		char filename[30];
		ifstream file;
		
		cout<<"\nEnter the name of the file which contains the puzzle --> ";
		cin>>filename;

		file.open(filename,ios::in);

		for(rowIter=0; rowIter<9; rowIter++){
			for(colIter=0; colIter<9; colIter++){

				int readValue;
				file>>readValue;

				sudokuFrame[rowIter][colIter]=readValue;

				if(file.eof()) break;

			}
		}
		
		//If there aren't 81 values in the file, then it is invalid.	
		if((colIter*rowIter)!=81){
			cout<<"Oops! The file doesn't have the required amount of values.\n";
			cout<<"Try again!\n";
			exit(EXIT_FAILURE);
		}

		file.close();

	}

	/**
	  *	@desc Returns the value of a cell of a specified col and row.
	  *	@param row (int) The specified row.
	  *	@param col (int) The specified column.
	  *	@return The value in the specified cell.
	 */
	public:int getCellValue(int row, int col){
		return sudokuFrame[row][col];
	}

};


class SudokuValidator{

	SudokuFrame frame;
	
	/**
	  *	@desc Calls the function which validates the values in the Sudoku frame.
	  *	@param none
	 */
	public:SudokuValidator(){
		validateFrame();		
	}

	/**
	  *	@desc Calls functions which validates the rows, columns and 3x3 grids.
	  *	@param none
	  *	@return none
	*/
	private:void validateFrame(){
		if(valuesAreValid()){
			if(rowsAreValid()){
				if(columnsAreValid()){
					if(ThreeByThreeSquaresAreValid()){
						cout<<"\nYour puzzle is valid!\n\n";
					}
					else cout<<"Your puzzle in invalid!\n";
				}
				else cout<<"Your puzzle is invalid!\n";
			}
			else cout<<"Your puzzle is invalid!\n";
		}
		else cout<<"Your puzzle is invalid!\n";
	}
	

	/**
	  *	@desc Checks if all values in the frame are between the ranges of 1-9.
	  *	@param none
	  *	@return (bool) Whether all the values are valid or not.
	*/
	private:bool valuesAreValid(){		
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){
			for(colIter=0; colIter<9; colIter++){
				int cellValue=frame.getCellValue(rowIter,colIter);
				if(!(cellValue>=0 && cellValue<=9)) return false;
			}
		}

		return true;
	}

	/**
	  *	@desc Checks if the rows are valid in the frame.
	  *	@param none	
	  *	@return (bool) Whether the rows are valid or not.
	*/
	private:bool rowsAreValid(){
		
		int rowIter, colIter, valIter;

		for(rowIter=0; rowIter<9; rowIter++){ //Iterating over rows

			for(valIter=1; valIter<=9; valIter++){ //Iter over 1-9

				if(rowContains(rowIter,valIter)==false)
					return false;

			} //Value iteration loop ends here

		} //Row iteration loop ends here

		return true;
	}

	/**
	  *	@desc Checks if the columns in the frame are valid.
	  *	@param none
	  *	@return (bool) Whether the columns are valid or not.
	*/
	private:bool columnsAreValid(){
		
		int rowIter, colIter, valIter;
		
		for(colIter=0; colIter<9; colIter++){ //Iterating over cols
		
			for(valIter=1; valIter<=9; valIter++){ //Iter over 1-9
				
				if(columnContains(colIter,valIter)==false)
					return false;

			} //Value iteration loops ends

		} //Col iteration loop ends here
		
		return true;
	}
	
	/**
	  *	@desc Checks if the 3x3 grids in the frame are valid.
	  *	@param none
	  *	@return (bool) Whether the 3x3 grids are valid or not.
	*/
	private:bool ThreeByThreeSquaresAreValid(){
		
		int squareIter, valIter;

		for(squareIter=0; squareIter<9; squareIter++){ //Iter over squares
			
			for(valIter=1; valIter<=9; valIter++){ //Iter over 1-9

				if(squareContains(squareIter,valIter)==false)
					return false;

			} //Value iteration loop ends here

		} //Square iteration loop ends here
		
		return true;
	}

	/**
	  *	@desc Checks whether a given value is present in a specified row.
	  *	@param row (int) The specified row.
	  *	@param value (int) The value to be checked for.
	  *	@return (bool) Whether the value is present in the row or not.
	*/
	private:bool rowContains(int row, int value){
		int colIter;
		for(colIter=0; colIter<9; colIter++){
			if(frame.getCellValue(row,colIter)==value)
				return true;
		}
		return false;
	}

	/**
	  *	@desc Checks whether a given value is present in the specified column.
	  *	@param col (int) The specified column.
	  *	@param value (int) The value to be checked for.
	  *	@return (bool) Whether the value is present in the col or not.
	*/
	private:bool columnContains(int col, int value){
		int rowIter=0;
		for(rowIter=0; rowIter<9; rowIter++){
			if(frame.getCellValue(rowIter,col)==value)
				return true;
		}
		return false;
	}

	/**
	  *	@desc Checks whether a given value is present in the specified 3x3 grid.
	  *	@param squareNumber (int) The 3x3 grid specified. The available grids are 0-8.
	  *	@param value (int) The value to be checked for.
	  *	@return (bool) Whether the value is present or not.
	*/
	private:bool squareContains(int squareNumber, int value){
		int rowStart=(squareNumber/3)*3;
		int rowEnd=rowStart+2;
		
		int colStart=(squareNumber%3)*3;
		int colEnd=colStart+2;

		int rowIter, colIter;
		for(rowIter=rowStart; rowIter<=rowEnd; rowIter++){
			for(colIter=colStart; colIter<=colEnd; colIter++){
				if(frame.getCellValue(rowIter,colIter)==value)
					return true;
			}
		}

		return false;
	}

};


int main(){
	SudokuValidator s;
	return 0;
}
