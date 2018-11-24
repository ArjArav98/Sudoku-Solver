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
		//menu();
		readFrameValuesFile();
	}
	
	private:void readFrameValuesFile(){
		
		int rowIter, colIter;
		char filename[30];
		ifstream file;
		
		cout<<"Enter the name of the file which contains the puzzle --> ";
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
		
		
		if((colIter*rowIter)!=81){
			cout<<"Oops! The file doesn't have the required amount of values.\n";
			cout<<"Try again!\n";
			exit(EXIT_FAILURE);
		}

		file.close();

	}

	public:int getCellValue(int row, int col){
		return sudokuFrame[row][col];
	}

};


class SudokuValidator{

	SudokuFrame frame;

	public:SudokuValidator(){
		validateFrame();		
	}

	private:void validateFrame(){
		if(valuesAreValid()){
			if(rowsAreValid()){
				if(columnsAreValid()){
					if(ThreeByThreeSquaresAreValid()){
						cout<<"Your puzzle is valid!\n";
					}
					else cout<<"Your puzzle in invalid!\n";
				}
				else cout<<"Your puzzle is invalid!\n";
			}
			else cout<<"Your puzzle is invalid!\n";
		}
		else cout<<"Your puzzle is invalid!\n";
	}

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

	private:bool rowContains(int row, int value){
		int colIter;
		for(colIter=0; colIter<9; colIter++){
			if(frame.getCellValue(row,colIter)==value)
				return true;
		}
		return false;
	}

	private:bool columnContains(int col, int value){
		int rowIter=0;
		for(rowIter=0; rowIter<9; rowIter++){
			if(frame.getCellValue(rowIter,col)==value)
				return true;
		}
		return false;
	}

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
