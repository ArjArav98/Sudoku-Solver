//======================
//    Sudoku Solver
//======================
//
//Started On - October 2nd, 2018
//Author - Arjun Aravind
//Objective - This is an application written in C++ which takes in Sudoku puzzles and outputs the solution.

#include<iostream>
#include<fstream>
using namespace std;

#define TRUE 1
#define FALSE 0

typedef int boolean;

/**	
 *	This class provides a data structure which can hold and manipulate the values in a sudoku puzzle.
 *	In this file, we shall call this data structure the 'Sudoku Frame'.
*/
class SudokuFrame{
	
	int sudokuFrame[9][9]; //This pointer will hold all the values in the matrix.
	int editableFrame[9][9]; //This pointer will tell us all the values which are editable.
	int rowIter, colIter; //iterator variables
	

	/**	
	  *	@desc This constructor calls functions which get the values for the Sudoku Frame.
	  *	@param none
	  *	@return none
	*/
	public:SudokuFrame(){
		menu();
	}
	
	void menu(){
		
		cout<<"\n======================\n";
		cout<<"    Sudoku Solver\n";
		cout<<"======================\n\n";

		cout<<"Welcome to Sudoku Solver!\n";
		cout<<"Before we start, you will have to input the puzzle into this program.\n\n";
		cout<<"You can either:-\n";
		cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
		cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
		cout<<"\t   The file must not have a name > 20 characters.\n";
		cout<<"\t   The file must be in the same directory as this C++ file.\n";
		cout<<"\t   The file must have all 81 values seperated with spaces.\n";
		cout<<"\t   Blank cells must be filled in as 0 (eg; 1 0 0 2 0 0 ...).\n\n";
		cout<<"\t   --> ";

		int option;
		cin>>option;

		if(option==1) readFrameValues();
		else if(option==2) readFrameValuesFile();
		else{
			while(true){
				cout<<"\nYou seem to have entered an invalid option. Try again.\n";
				cout<<"\t  --> ";
				cin>>option;

				if(option==1) readFrameValues();
				else if(option==2) readFrameValuesFile();
				else continue;

				break;
			}
		}

	}

	/**
	  *	@desc Reads the values for the Sudoku Frame cell-by-cell.
	  *	@param none
	  *	@return none
	*/
	void readFrameValues(){
		cout<<"Enter the values for the Sudoku puzzle here!\n";
		cout<<"Enter the particular value when prompted. Enter 0 if cell is empty.\n\n";

		for(rowIter=0; rowIter<9; rowIter++){
			for(colIter=0; colIter<9; colIter++){
				cout<<"Enter value for cell["<<rowIter+1<<"]["<<colIter+1<<"] --> ";
				cin>>sudokuFrame[rowIter][colIter];

				if(sudokuFrame[rowIter][colIter]==0) editableFrame[rowIter][colIter]=0;
				else editableFrame[rowIter][colIter]=1;
			}
			cout<<"-------\n";
		}
	}

	void readFrameValuesFile(){

		char filename[20];

		cout<<"\nEnter the name of the file that contains the Sudoku Puzzle.\n";
		cout<<"\t  --> ";
		cin>>filename;

		ifstream sudokuFile;
		sudokuFile.open(filename,ios::in);

		for(rowIter=0; rowIter<9; rowIter++){
			for(colIter=0; colIter<9; colIter++){
				int readValue;
		
				sudokuFile>>readValue;
				sudokuFrame[rowIter][colIter]=readValue;

				if(sudokuFrame[rowIter][colIter]==0) editableFrame[rowIter][colIter]=0;
				else editableFrame[rowIter][colIter]=1;

				if(sudokuFile.eof()) break;
			}
		}
		
		//Gotta have a line which lets us check the frame for any errors

		sudokuFile.close();
	}
	
	/**
	  *	@desc Assigns the passed-in number to the specified row and col.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return none
	*/
	public:void setCellValue(int row, int col, int num){
		if(editableFrame[row][col]==0) sudokuFrame[row][col]=num;
	}
	
	/**	
	  *	@desc Returns the value of the cell at the specified row and col.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return (int) cellValue value at the specified cell
	*/
	public:int getCellValue(int row, int col){
		int cellValue=sudokuFrame[row][col];
		return cellValue;
	}
	
	/**
	  *	@desc Returns TRUE/FALSE depending on editableFrame values.
	  *	@param row (int) row of the required cell
 	  *	@param col (int) col of the required cell
	  *	@return (int) 1 if editable; 0 if not
	*/
	public:int isEditable(int row, int col){
		return (editableFrame[row][col]-1)*(-1);
	}

	/**
	  *	@desc clears frame of all values, other than the question values, from
	  *	the specified cell to the last cell.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	*/
	public:void clearFrameFrom(int row, int col){
		int jcount=0;

		for(rowIter=row; rowIter<9; rowIter++){
			
			if(jcount==0) colIter=col;
			else colIter=0;

			for(; colIter<9; colIter++){
				if(editableFrame[rowIter][colIter]==0) sudokuFrame[rowIter][colIter]=0;
			}

			jcount++;

		}
	}

	/**
	  *	@desc Displays the values stored in the frame with designs.
	  *	@param none
	  *	@return none
	*/
	public:void displayFrame(){
		cout<<"\n";
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


/**	
  *	This class provides the programmer a very simple way to iterate through
  *	the possibilities of a specified cell. This object utilises linked lists.
*/
class Possibilities{
	
	struct node{
		int value;
		struct node* next;
	}; //The struct for the node
	
	typedef struct node* Node;

	Node head; //The head node
	Node pos; //A node iterator variable
	

	/**	
	  *	@desc this constructor initialises the head (or sentinel) node
	  *	@param none
	*/
	public:Possibilities(){
		head=new struct node;
		head->next=NULL;
	}
	
	/**	
	  *	@desc this destructor destroys the linked list once the object
 	  *	has finished its lifespan. Calls the destroy() function.
	*/
	public:~Possibilities(){
		destroy();
	}
	
	/**	
	  *	@desc this functions takes in a number and adds it as a node in
	  *	the linked list.
	  *	@param number (int) the number which we want to append
	  *	@return none
	*/
	public:void append(int number){
		Node temp=new struct node;

		temp->value=number;
		temp->next=NULL;

		pos=head;
		while(pos!=NULL){
			if(pos->next==NULL){
				pos->next=temp;
				break;
			}
			pos=pos->next;
		}
	}
	
	/**	
		operator[]
	  *	@desc an operator overload function which overloads the [] operator.
	  *	@param index (int) the index of the required node in the linked list.
	  *	@return (int) the value contained in the specified node.
	*/
	public:int operator[](int index){
		int count=0;
		pos=head->next;
		
		while(pos!=NULL){
			if(count==index)
				return pos->value;
			pos=pos->next;
			count++;
		}

		return -1;
	}

	/**	print()

	  *	@desc prints the values inside all the nodes of the linked list.
	  *	@param none
	  *	@return none
	*/
	public:void print(){
		pos=head->next;
		while(pos!=NULL){
			cout<<pos->value<<",";
			pos=pos->next;
		}
		cout<<"\b";
	}

	/**
	  *	@desc returns the length of the linked list.
	  *	@param none
	  *	@return (int) the length of the linked list.
	*/
	int length(){
		pos=head->next;
		int count=0;

		while(pos!=NULL){
			count++;
			pos=pos->next;
		}
		
		return count;
	}
	
	/**
	  *	@desc this function takes in a possibilities object and copies
	  *	the contents into THIS object.
	  *	@param possibilities (Possibilities) the object which is to be copied
	  *	@return none
	*/
	void copy(Possibilities possibilities){ //Need to make this clear the old list if exists
		int oldLength=possibilities.length();
		int iter=0;
		
		pos=head;
		for(iter=0; iter<oldLength; iter++){
			Node temp=new struct node;

			temp->next=NULL;
			temp->value=possibilities[iter];

			pos->next=temp;
			pos=pos->next;
		}
	}
	
	/**
	  *	@desc frees all the nodes in the linked list
	  *	@param none
	  *	@return none
	*/
	void destroy(){
		Node temp;
		pos=head;
		while(pos!=NULL){
			temp=pos;
			pos=pos->next;
			delete temp;
		}
	}

};


/**
  *	Takes in the SudokuFrame object and solves the Sudoku Puzzle.
*/
class SudokuSolver{
	
	int rowIter, colIter; //Iter variables
	int recursiveCount; //Stats variable
	SudokuFrame frame; //The frame object
	
	/**
	  *	@desc The constructor initialises the recursiveCount variable.
	  *	@param none
	*/
	public:SudokuSolver(){
		recursiveCount=0;
	}
	
	/**
	  *	@desc Checks if the value in the specified cell is valid or not.
	  *	@param row (int) row of the required value
	  *	@param col (int) col of the required value
	  *	@param currentValue (int) the required value
	  *	@return (boolean) whether the value is valid or not in the sudoku frame
	*/
	public:boolean cellValueValid(int row, int col, int currentValue){

		//Checking if value exists in same column
		for(rowIter=0; rowIter<9; rowIter++){
			if(rowIter!=row){
				int comparingValue=frame.getCellValue(rowIter,col);
				if(comparingValue==currentValue) return FALSE;
			}
		}

		//Checking if value exists in same row
		for(colIter=0; colIter<9; colIter++){
			if(colIter!=col){
				int comparingValue=frame.getCellValue(row,colIter);
				if(comparingValue==currentValue) return FALSE;
			}
		}

		//Checking if value exists in the same 3x3 square block
		if(ThreeByThreeGridValid(row,col,currentValue)==FALSE) return FALSE;

		return TRUE;
	}
	
	/**
	  *	@desc Checks if the same value is also present in the same 3x3 grid block.
	  *	@param row (int) row of the required cell
	  *	@param col (int) col of the required cell
	  *	@param currentValue (int) required value
	  *	@return (boolean) whether the value is present or not
	*/
	boolean ThreeByThreeGridValid(int row, int col, int currentValue){
		int rowStart=(row/3)*3;
		int rowEnd=(rowStart+2);

		int colStart=(col/3)*3;
		int colEnd=(colStart+2);

		for(rowIter=rowStart; rowIter<=rowEnd; rowIter++){
			for(colIter=colStart; colIter<=colEnd; colIter++){
				if(frame.getCellValue(rowIter,colIter)==currentValue) return FALSE;
			}
		}

		return TRUE;	
	}
	
	/**
	  *	@desc gets the possible values and assigns them to the possibilities list.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return (Possibilities) Possibilities object containing all the possible values.
	*/
	public:Possibilities getCellPossibilities(int row, int col){
		int iter=0;

		Possibilities possibilities;

		for(iter=1; iter<=9; iter++){
			if(cellValueValid(row,col,iter))
				possibilities.append(iter);
		}

		return possibilities;
	}
	
	/**	
	  *	@desc the recursive function which does all the work, this iterates over the
	  *	possible values for the specified cell one-by-one. Once a value has been filled, it
	  *	goes to the next cell. Here, the same thing happens. If none of the possible values
	  *	work out, then the function backtracks to the previous cell.
  	  *
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return (int) whether the value put in the cell made it a SUCCESS or NOT
	*/
	int singleCellSolve(int row, int col){
		
		statsIncrement(); //This is used to see how many times the func is called.

		if(frame.isEditable(row,col)){

			Possibilities possibilities;
			possibilities.copy(getCellPossibilities(row,col));

			int posLength=possibilities.length();
			int posIter=0, newRow=row, newCol=col;

			for(posIter=0; posIter<posLength; posIter++){ //We iter over the possible values
				int possibility=possibilities[posIter];
				frame.setCellValue(row,col,possibility);
				
				//We now increment the col/row values for the next recursion
				if(col<8) newCol=col+1; 
				else if(col==8){
					if(row==8) return 1; //this means success
					newRow=row+1;
					newCol=0;
				}

				{

					if(singleCellSolve(newRow,newCol)==0){ //If wrong, clear frame and start over
						frame.clearFrameFrom(newRow,newCol);
					}
					else return 1;

				} //Recursion block ends here

			} //Loop ends here

			return 0;
			
		} //The isEditable() if block ends here.
		else{

			int newRow=row, newCol=col;
			
			//Same incrementing of the col/row values
			if(col<8) newCol=col+1;
			else if(col==8){
				if(row==8) return 1;
				newRow=row+1;
				newCol=0;
			}

			return singleCellSolve(newRow,newCol);

		} //The else block ends here

	}

	/**
	  *	@desc calls the singleCellSolve() func and prints a success/fail mesg.
	  *	@param none
	  *	@return none
	*/
	public:void solve(){
		int success=singleCellSolve(0,0);
		
		if(success==1) cout<<"\nYour Sudoku puzzle has been solved! QED.\n";
		else cout<<"This didn't work!\n";
	}
	
	/**
	  *	@desc displays the sudoku frame by calling the displayFrame() func of the
	  *	SudokuFrame object.
	  *	@param none
	  *	@return none
	*/
	public:void displayFrame(){
		frame.displayFrame();
	}
	
	/**
	  *	@desc this increments the count variable to keep track of the recursions done.
	  *	@param none
	  *	@return none
	*/
	void statsIncrement(){
		recursiveCount++;
	}

	/**
	  *	@desc this displays the number of times recursion has happened.
	  *	@param none
	  *	@return none
	*/
	public:void statsPrint(){
		cout<<"\nThe singleCellSolve() function was recursively called "<<recursiveCount<<" times.\n";
	}
	
};