//UIC CS 211 Program 5 Manuel M Martinez
//
//The purpose of this program is to be able to input a infix expression and solve it. This program utilizes a stack class 
//called 'myStack' that contains a dynamically allocated array that is able to grow when the size reaches its limit. In addition 
//it utilizes class functions such as a destructor to free allocated memory at the end of the program.
//projBase.cpp contains the algorithm for Infix to Postfix Conversation and Postfix Evaluation, and myStack.cpp contains the public 
//functions of the 'myStack' class.
//


#include <iostream>
#include <string>

using namespace std;

//Stack Class 
class myStack
{

//Private Stack Values 
private:
	
	//Int Array 
	int* mArray;
		
	int Size;
	int top;
		
	//Private Function that dynamically grows the array 
	void _Grow(int* mArray)
	{
		int* tmp = mArray;
			
		//Allocate new memory for a bigger array 
		mArray = new int[(Size + 2)];
		
		//Store old array values into new array 
		for(int i = 0; i < Size; i++)
		{
			mArray[i] = tmp[i];
		}
		
		//Free memory of old Array 
		delete[] tmp;
		
		//Update size 
		Size = Size + 2;
		
	}
		
public:
		
	//Initial constructor 
	myStack()
	{
	    //Set initial size and top values 
		Size = 2;		
		top = -1;
	
	    //Create new dynamic array
		mArray = new int[Size];
		
	}

	//Destructor
	virtual ~myStack()
	{
		delete[] mArray;
	}
	
	//Push Value into Array 
	void Push(int value);
		
	//Pop Top value of stack 
	int Pop();
		
	//Check if the Stack is empty 
	bool isEmpty();
	
	//Return value at top of the stack 
	int Top();
	
	//Reset Stack and return it to default values
	void Reset();
	
};


