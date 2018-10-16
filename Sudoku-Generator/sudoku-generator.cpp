#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;

class Random{
	
	int randomCount;

	public:Random(){
		randomCount=0;
	}
	
	public:int generate(){
		time_t now = time(0);
		tm *curtime = localtime(&now);

		int number1=(curtime->tm_sec)*(curtime->tm_sec/10);
		int number2=(curtime->tm_min)/(curtime->tm_sec/10);
		
		randomCount+=7;		

		return ((number1*number2)+randomCount);
	}

	public:int chooseBetween(int lower, int upper){
		int difference=(upper+1)-lower;
		int random=generate()%difference;
		return (lower+random);
	}

};

class SudokuFrame{
	
	int sudokuFrame[9][9];

	public:SudokuFrame(){
		fillFrameWithZeroes();
		menu();
	}

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

	private:void fillFrameWithZeroes(){
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){
			for(colIter=0; colIter<9; colIter++){
				sudokuFrame[rowIter][colIter]=0;
			}
		}
	}

	public:void setCellValue(int row, int col, int value){
		sudokuFrame[row][col]=value;
	}

	public:bool cellValueValid(int row, int col, int value){
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++)
			if(sudokuFrame[rowIter][col]==value) return false;

		for(colIter=0; colIter<9; colIter++) 
			if(sudokuFrame[row][colIter]==value) return false;

		if(ThreeByThreeGridValid(row,col,value)==false) return false;

		return true;

	}

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

class SudokuGenerator{
	
	SudokuFrame frame;
	Random random;

	public:SudokuGenerator(){
		generateValues();
		frame.displayFrame();
		frame.printFrame();
	}

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
