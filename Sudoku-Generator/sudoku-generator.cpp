#include<iostream>
#include <ctime>
using namespace std;

class SudokuGenerator{
	
	int randomCount;

	public:SudokuGenerator(){
		randomCount=17;
	}

	int randomSudoku(){
		time_t now = time(0);
	        tm *curtime = localtime(&now);
	
	        int num = (curtime->tm_year)/(curtime->tm_min) * (curtime->tm_sec + curtime->tm_min);
	        num = num+(curtime->tm_mday*curtime->tm_mon);
	        num = num-curtime->tm_hour;
	
	        int div1 = (curtime->tm_sec*13)/curtime->tm_min;
	        int div2 = (curtime->tm_sec*4)+(curtime->tm_sec*29);
	
		div1+=randomCount;
	        div1 = (div1+div2)%(curtime->tm_sec+div1);
	        div1 = (div1+curtime->tm_sec)*curtime->tm_sec;
	        div1 = (div1+num)+(num+div2);
	
	        if(curtime->tm_sec%10==1) div1=div2*9;
	        else if(curtime->tm_sec%10==2) div1=div2*(num%9);
	        else if(curtime->tm_sec%10==3) div1=(num*13)%(num+20)+div2;
	        else if(curtime->tm_sec%10==4) div1=div1*17;
	        else if(curtime->tm_sec%10==5) div1=div1+(div1*5);
	        else if(curtime->tm_sec%10==6) div1=div1+91;
	        else if(curtime->tm_sec%10==7) div1=(div2-19)+(num*12);
        	else if(curtime->tm_sec%10==8) div1=(div2+div1)+(div1+num);
	        else if(curtime->tm_sec%10==9) div1=(num+num)+23;

		div1=div1&num;
		div1=div1|num;

		randomCount++;

		return (div1%9);
	}

};

int main(){
	
	SudokuGenerator s;
	int i;

	for(i=0; i<10; i++){
		cout<<s.randomSudoku();
	}

	return 0;
}
