/*
 *======================
 *   Sudoku Generator
 *======================
 *
 * Started On: October 15th
 * Author: Arjun Aravind
 * Objective: Generation of Sudoku puzzles.
*/
#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;

/**
  *	@desc this class contains member functions which generates random values.
  *	These values are not actually random, but are random as can be. There are
  *	two functions in this class:- generate() and chooseBetween().
*/
class Random{
	
	int randomCount; //a count variable
	
	/**
	  *	@desc this constructor initialises the randomCount variable to 0.
	  *	@param none
	*/
	public:Random(){
		randomCount=0;
	}
	
	/**
	  *	@desc using the current time, function generates a random number.
	  *	@param none
	  *	@return (int) the randomly generated number
	*/
	public:int generate(){
		time_t now = time(0);
		tm *curtime = localtime(&now);

		int number1=(curtime->tm_sec)*(curtime->tm_sec/10);
		int number2=(curtime->tm_min)/(curtime->tm_sec/10);
		
		randomCount+=7;		

		return ((number1*number2)+randomCount);
	}
	
	/**
	  *	@desc when given an upper value and a lower value, this function
	  *	randomly chooses values between and including the two numbers.
	  *	@param lower (int) the lower limit
	  *	@param upper (int) the upper limit
	  *	@return (int) a random value between or equal to one of the 2 nums.
	*/
	public:int chooseBetween(int lower, int upper){
		int difference=(upper+1)-lower;
		int random=generate()%difference;
		return (lower+random);
	}

};

/**
  *	@desc this class provides a data structure/object which contains the Sudoku
  *	puzzle along with other actions that might be needed to be performed on it.
*/
class SudokuFrame{
	
	int sudokuFrame[9][9]; //The 9x9 matrix that contains the values of the puzzle

	/**
	  *	@desc this constructor calls the functions menu() and fillFrameWithZeroes().
	*/
	public:SudokuFrame(){
		fillFrameWithZeroes();
		menu();
	}
	
	/**
	  *	@desc provides a menu for the user which it makes more convenient and better
	  *	appearance-wise.
	  *	@param none
	  *	@return none
	*/
	public:void menu(){
		cout<<"\n=====================\n";
		cout<<"  Sudoku Generator\n";
		cout<<"=====================\n\n";

		cout<<"Welcome to Sudoku Generator!\n";
		cout<<"This generator not only displays the puzzle onscreen, it ";
		cout<<"also outputs the puzzle to a file.\n";
		cout<<"(This can even then be used in the Sudoku-Solver program)\n";
		cout<<"Okay, here goes!\n\n";
	}

	/**
	  *	@desc fills all the values of the matrix with zeroes. This is so that, later
	  *	on, we do not need to fill all the blank values with zero.
	  *	@param none
	  *	@return none
	*/
	private:void fillFrameWithZeroes(){
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){
			for(colIter=0; colIter<9; colIter++){
				sudokuFrame[rowIter][colIter]=0;
			}
		}
	}
	
	/**
	  *	@desc this sets the required cell value with the specified value.
	  *	@param row (int) row of the required cell
	  *	@param col (int) col of the required cell
	  *	@param value (int) the specified value
	  *	@return none
	*/
	public:void setCellValue(int row, int col, int value){
		sudokuFrame[row][col]=value;
	}
	
	/**
	  *	@desc tells us whether the value in the specified cell is valid
	  *	or not.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@param value (int) the specified value
	  *	@return (bool) whether the value in the cell is valid or not.
	*/
	public:bool cellValueValid(int row, int col, int value){
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++)
			if(sudokuFrame[rowIter][col]==value) return false;

		for(colIter=0; colIter<9; colIter++) 
			if(sudokuFrame[row][colIter]==value) return false;

		if(ThreeByThreeGridValid(row,col,value)==false) return false;

		return true;

	}
	
	/**
	  *	@desc tells us whether the value in a cell is valid for its 3x3 grid.
	  *	@param row (int) row of the required cell
	  *	@param col (int) col of the required cell
	  *	@param value (int) the specified value
	  *	@return (bool) whether the value in the cell is valid or not.
	*/
	public:bool ThreeByThreeGridValid(int row, int col, int value){
		int rowStart=(row/3)*3;
		int rowEnd=(rowStart+2);

		int colStart=(col/3)*3;
		int colEnd=(colStart+2);

		int rowIter, colIter;

		for(rowIter=rowStart; rowIter<=rowEnd; rowIter++){
			for(colIter=colStart; colIter<=colEnd; colIter++){
				if(sudokuFrame[rowIter][colIter]==value) return false;
			}
		}
		
		return true;

	}
	
	/**
	  *	@desc displays the frame in an aesthetically pleasing way.
	  *	@param none
	  *	@return none
	*/
	public:void displayFrame(){
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){
			cout<<"+---+---+---+---+---+---+---+---+---+\n";
			for(colIter=0; colIter<9; colIter++){
				cout<<"| ";
				if(sudokuFrame[rowIter][colIter]==0) cout<<"  ";
				else cout<<sudokuFrame[rowIter][colIter]<<" ";
			}
			cout<<"|\n";
		}

		cout<<"+---+---+---+---+---+---+---+---+---+\n\n";

	}
	
	/**
	  *	@desc outputs the contents of the sudoku puzzle into a
	  *	specified file.
	  *	@param none
	  *	@return none
	*/
	public:void printFrame(){
		
		int rowIter, colIter;
		char filename[30];

		cout<<"Enter a filename to which the puzzle will be printed to --> ";
		cin>>filename;

		ofstream file;
		file.open(filename,ios::out);

		for(rowIter=0; rowIter<9; rowIter++){
			for(colIter=0; colIter<9; colIter++){
				file<<sudokuFrame[rowIter][colIter]<<" ";
			}
			file<<"\n";
		}
		cout<<"\n";		
	
		cout<<"Here's your puzzle! You can see it right here on the screen";
		cout<<"or you can view it\nin the generated file "<<filename<<".\n\n";
		file.close();

	}

};

/**
  *	@desc this class uses the objects of classes defined before and also contains
  *	member functions which randomly generate values and put them into random cols.
*/
class SudokuGenerator{
	
	SudokuFrame frame;
	Random random;

	/**
	  *	@desc this constructor calls functions which randomly generate values,
	  *	displays the finished puzzle and outputs it into a file.
	*/
	public:SudokuGenerator(){
		generateValues();
		frame.displayFrame();
		frame.printFrame();
	}
	
	/**
	  *	@desc for every row in the puzzle, this function randomly decides how many
	  *	values (between 2 and 4) to fill in the row, randomly decided which cols
	  *	to fill them in and randomly decided what these values should be.
	  *
	  *	@param none
	  *	@return none
	*/
	public:void generateValues(){
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){
			
			int numOfFilledValues=random.chooseBetween(1,4);
			int valIter;

			for(valIter=0; valIter<numOfFilledValues; valIter++){
				int randomCol=random.chooseBetween(0,8);
				int randomVal=random.chooseBetween(1,9);

				if(frame.cellValueValid(rowIter,randomCol,randomVal))
					frame.setCellValue(rowIter,randomCol,randomVal);
				else{
					while(true){
						randomVal=random.chooseBetween(1,9);
						if(frame.cellValueValid(rowIter,randomCol,randomVal))
							break;
					}

					frame.setCellValue(rowIter,randomCol,randomVal);
				
				}

			} //The valIter loop ends here

		} //The rowIter loop ends here
	}

};

int main(){
	SudokuGenerator gen;
	return 0;
}
