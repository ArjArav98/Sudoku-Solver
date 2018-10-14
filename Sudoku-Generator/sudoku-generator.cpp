#include<iostream>
#include<ctime>
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

		return ((number1*number2)+randomCount)%9;
	}

	public:int chooseBetween(int lower, int upper){
		int difference=(upper+1)-lower;
		int random=generate()%difference;
		return (lower+random);
	}

};

class SudokuFrame{
	
	int sudokuFrame[9][9];
	Random random;

	public:SudokuFrame(){
		fillFrameWithZeroes();
		generateFrame();
		displayFrame();
	}

	void fillFrameWithZeroes(){
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){
			for(colIter=0; colIter<9; colIter++){
				sudokuFrame[rowIter][colIter]=0;
			}
		}
	}
	
	/*void generateFrame(){
		
		int rowIter;

		for(rowIter=0; rowIter<9; rowIter++){
			int numOfFilledValues=random.chooseBetween(3,4);
			int valueIter;

			for(valueIter=0; valueIter<numOfFilledValues; valueIter++){
				sudokuFrame[rowIter][random.generate()]=random.generate();		
			}
		}

	}*/

	private:void displayFrame(){
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

		cout<<"+---+---+---+---+---+---+---+---+---+\n";

	}
};

int main(){
	SudokuFrame frame;
	return 0;
}
