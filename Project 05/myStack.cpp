#include "myStack.h"

//Push Value into Array 
void myStack::Push(int value)
{
	//Check if the array is full
	if(top == Size)
	{
		//Grow the dynamic array
		_Grow(mArray);
	}
	
	//Update top value 
	top++;
		
	//Store value into array 
	mArray[top] = value;
	
}
		
//Pop Top value of stack 
int myStack::Pop()
{
	if(isEmpty())
	{
		//Stack is empty return -999 
		return -999;
	}
		
	 //Store value that will be poped into a variable 
	 int dValue = mArray[top];
		 
	//Update top value 
	top--;
		 
	//Return value that was poped 
	return dValue;
		
}
		
//Check if the Stack is empty 
bool myStack::isEmpty()
{
	//Returns true if Stack is empty
	return top == -1; 
		
}

//Return value at top of the stack 
int myStack::Top()
{
	//Return top value 
	return mArray[top];
	
}
		
//Reset Stack and return it to default values
void myStack::Reset()
{
	//Holds poped values 
	int clear;
			
	//Loop while -999 is not returned in the pop function 
	while(clear != -999)
	{
	   clear = Pop();
	}
		
}

