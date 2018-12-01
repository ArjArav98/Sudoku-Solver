/*
 *======================
 *   Sudoku Generator
 *======================
 *
 * Started On - November 28th, 2018
 * Author - Arjun Aravind
 * Objective - Outputs a Sudoku puzzle.
*/

#include<iostream>
#include<fstream>
using namespace std;

/**	
  *	This class provides a data structure which can hold and manipulate the values in a sudoku puzzle.
  *	In this file, we shall call this data structure the 'Sudoku Frame'.
*/
class SudokuFrame{
	
	int sudokuFrame[9][9]; //This pointer will hold all the values in the matrix.

	/**	
	  *	@desc This constructor calls the menu() func to provide the menu. It also
	  *	calls the setZeros() func to set all cells to the default 0 value.
	  *
	  *	@param none
	  *	@return none
	*/
	public:SudokuFrame(){
		menu();
		setZeros();
	}
	
	/**
	  *	@desc Displays a menu to the user when the SudokuFrame objects is instantiated
	  *	(which is basically at the start of the program).
	  *
	  *	@param none
	  *	@return none
	*/
	private:void menu(){
		
		cout<<"\n=======================\n";
		cout<<"    Sudoku Generator\n";
		cout<<"=======================\n\n";

		cout<<"Welcome to Sudoku Generator!\n";
		cout<<"We shall begin generating your puzzle now.\n\n";

	}

	/**
	  *	@desc Fills all the values of the board with 0, the value representing
	  *	an empty cell in this program.
	  *	
	  *	@param none
	  *	@return none
	*/
	private:void setZeros(){
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){
			for(colIter=0; colIter<9; colIter++){
				sudokuFrame[rowIter][colIter]=0;
			}
		}
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
	  *	@desc Clears frame of all values, other than the question values, from
	  *	the specified cell to the last cell.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	*/
	public:void clearFrameFrom(int row, int col){
		int jcount=0;
		int rowIter, colIter;

		for(rowIter=row; rowIter<9; rowIter++){
			
			if(jcount==0) colIter=col;
			else colIter=0;

			for(; colIter<9; colIter++){
				if(editableFrame[rowIter][colIter]==0) sudokuFrame[rowIter][colIter]=0;
			}

			jcount++;

		}
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
	  *	@desc This constructor initialises the head (or sentinel) node
	  *	@param none
	*/
	public:Possibilities(){
		head=new struct node;
		head->next=NULL;
	}
	
	/**	
	  *	@desc This destructor destroys the linked list once the object
 	  *	has finished its lifespan. Calls the destroy() function.
	*/
	public:~Possibilities(){
		destroy();
	}
	
	/**	
	  *	@desc This function takes in a number and adds it as a node in
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
	  *	@desc An operator overload function which overloads the [] operator.
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

	/**
	  *	@desc Prints the values inside all the nodes of the linked list.
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
	  *	@desc Returns the length of the linked list.
	  *	@param none
	  *	@return (int) the length of the linked list.
	*/
	public:int length(){
		pos=head->next;
		int count=0;

		while(pos!=NULL){
			count++;
			pos=pos->next;
		}
		
		return count;
	}
	
	/**
	  *	@desc This function takes in a possibilities object and copies
	  *	the contents into THIS object.
	  *	@param possibilities (Possibilities) the object which is to be copied
	  *	@return none
	*/
	public:void copy(Possibilities possibilities){ //Need to make this clear the old list if exists
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
	  *	@desc Frees all the nodes in the linked list.
	  *	@param none
	  *	@return none
	*/
	private:void destroy(){
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
	
	int recursiveCount; //Stats variable
	SudokuFrame frame; //The frame object
	
	/**
	  *	@desc The constructor initialises the recursiveCount variable and also calls
	  *	the solve() function which solves the puzzle. It also displays the frames
	  *	before and after the solving.
	  *	@param none
	*/
	public:SudokuSolver(){
		recursiveCount=0;

		cout<<"\nCalculating possibilities...\n";
		cout<<"Backtracking across puzzle....\n";
		cout<<"Validating cells and values...\n\n";
		
		solve();
		cout<<"QED. Your puzzle has been solved!\n\n";
		displayFrame();

		cout<<"\n\n";
	}
	
	/**
	  *	@desc Checks if the value in the specified cell is valid or not.
	  *	@param row (int) row of the required value
	  *	@param col (int) col of the required value
	  *	@param currentValue (int) the required value
	  *	@return (bool) whether the value is valid or not in the sudoku frame
	*/
	private:bool cellValueValid(int row, int col, int currentValue){
		int rowIter, colIter;

		//Checking if value exists in same column
		for(rowIter=0; rowIter<9; rowIter++){
			if(rowIter!=row){
				int comparingValue=frame.getCellValue(rowIter,col);
				if(comparingValue==currentValue) return false;
			}
		}

		//Checking if value exists in same row
		for(colIter=0; colIter<9; colIter++){
			if(colIter!=col){
				int comparingValue=frame.getCellValue(row,colIter);
				if(comparingValue==currentValue) return false;
			}
		}

		//Checking if value exists in the same 3x3 square block
		if(ThreeByThreeGridValid(row,col,currentValue)==false) return false;

		return true;
	}
	
	/**
	  *	@desc Checks if the same value is also present in the same 3x3 grid block.
	  *	@param row (int) row of the required cell
	  *	@param col (int) col of the required cell
	  *	@param currentValue (int) required value
	  *	@return (bool) whether the value is present or not
	*/
	private:bool ThreeByThreeGridValid(int row, int col, int currentValue){
		int rowStart=(row/3)*3;
		int rowEnd=(rowStart+2);

		int colStart=(col/3)*3;
		int colEnd=(colStart+2);
		
		int rowIter, colIter;

		for(rowIter=rowStart; rowIter<=rowEnd; rowIter++){
			for(colIter=colStart; colIter<=colEnd; colIter++){
				if(frame.getCellValue(rowIter,colIter)==currentValue) return false;
			}
		}

		return true;	
	}
	
	/**
	  *	@desc Gets the possible values and assigns them to the possibilities list.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return (Possibilities) Possibilities object containing all the possible values.
	*/
	private:Possibilities getCellPossibilities(int row, int col){
		int iter=0;

		Possibilities possibilities;

		for(iter=1; iter<=9; iter++){
			if(cellValueValid(row,col,iter)==true)
				possibilities.append(iter);
		}

		return possibilities;
	}
	
	/**	
	  *	@desc The recursive function which does all the work, this iterates over the
	  *	possible values for the specified cell one-by-one. Once a value has been filled, it
	  *	goes to the next cell. Here, the same thing happens. If none of the possible values
	  *	work out, then the function backtracks to the previous cell.
  	  *
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return (int) whether the value put in the cell made it a SUCCESS or NOT
	*/
	private:int singleCellSolve(int row, int col){
		
		statsIncrement(); //This is used to see how many times the func is called.

		if(frame.isEditable(row,col)==true){

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
	  *	@desc Calls the singleCellSolve() func and prints a success/fail mesg.
	  *	@param none
	  *	@return none
	*/
	private:void solve(){
		int success=singleCellSolve(0,0);
	}
	
	/**
	  *	@desc Displays the sudoku frame by calling the displayFrame() func of the
	  *	SudokuFrame object.
	  *	@param none
	  *	@return none
	*/
	private:void displayFrame(){
		frame.displayFrame();
	}
	
	/**
	  *	@desc This function increments the count variable to keep track of the recursions done.
	  *	@param none
	  *	@return none
	*/
	private:void statsIncrement(){
		recursiveCount++;
	}

	/**
	  *	@desc This displays the number of times recursion has happened.
	  *	@param none
	  *	@return none
	*/
	public:void statsPrint(){
		cout<<"\nThe singleCellSolve() function was recursively called "<<recursiveCount<<" times.\n";
	}
	
};

int main(){
	SudokuSolver ss;
	return 0;
}
