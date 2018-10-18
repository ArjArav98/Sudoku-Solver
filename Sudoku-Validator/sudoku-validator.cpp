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
	
	void readFrameValuesFile(){
		
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
			cout<<"Oops! Something seems to be missing!";
		}

		file.close();

	}

};

int main(){
	SudokuFrame frame;
	return 0;
}
