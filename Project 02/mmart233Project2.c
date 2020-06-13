//The purpose of this program was to build a system where we are able to decode a message. This message is only able to be decoded if 
//a specific letter in L (a,b,c,d) mapped to a letter in L2 (m,n,o,p) respectively. When a word is valid it means that it was mapped 
//correctly and thus could be decoded. The program implements stacks and dynamically allocated arrays in other to determine if a letter
//is perfectly mapped. This program is user based wich means that a user must input a string of words that they wish to be decoded.
//The program will then decide if it is able to decode the message by checking if words in the message are meaningful.
//CS 211 Program 2 UIC <Manuel M Martinez> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int DebugMode; 

//A structure used to represent the stack 
struct Stack {
	int top;
	int capacity; 
	char* array;
};

//Function to create a stack of a given capacity 
struct Stack* createStack(int capacity){
	
	//Uses malloc to allocate memory for the stack
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	
	//Sets the initial capacity of the stack and initial top of stack
	stack->capacity = capacity;
	stack->top = -1;
	
	//Uses malloc to allocate memory for the stack array
	stack->array = (char*)malloc(stack->capacity * sizeof(char));
	
	return stack; 	
}

//Function to clear the stack of any values
void clear(struct Stack* stack){
	
	//Loop POPs any value in the stack 
	while(1){
	   pop(stack);
	   
	   //Loop stops when the stack is found to be empty 			
	   if(isEmpty(stack) == 1){
	  	break;
	   }
	}	
}

//Function checks if the stack has reached its maximum size capacity 
int isFull(struct Stack* stack){
	
	return stack->top == stack->capacity - 1;
	
}

//Function checks if the stack is empty 
int isEmpty(struct Stack* stack){
	
	//Test is a token that is initialized as false (-1)
	int test = -1;
	
	//If the stack is found to be empty then test is set to true (1)
	if(stack->top == -1)
	{
		test = 1;
	}
	
	return test;
}

//Function to dynamically grow stack array if the orginal has reached its maximum size
void grow(struct Stack* stack){
	
	//Char Pointer
	char* temp;
	
	int i;
	
	//Pointer is used to point at original array
	temp = stack->array;
	
	//Malloc is used to allocate more memory space for a bigger array (size increased by 4)
	stack->array = (char*)malloc((stack->capacity + 4) * sizeof(char));
	
	//The values from the orignal array are copied into the new array 
	for(i = 0; i < stack->capacity; i++){

		stack->array[i] = temp[i];
		
	}
	
	//Frees the memory space used by the orginal array 
	free(temp);
	
	//Used for Debug Mode
	if(DebugMode == TRUE){

		printf("The old size of the Stack Array was: %d\n", stack->capacity);
		printf("The number of values copied where: %d\n", i);
		printf("The new size of the Stack Array is: %d\n", stack->capacity + 4);
		
	}
	
	//The stack capacity is updated 
	stack->capacity = (stack->capacity + 4);
	
}

//Function to add an item to the stack, and increases top by 1 
void push(struct Stack* stack, char item){
	
	//Checks if the stack has reached its maximum limit.
	//If it has then its size is dynamically increased
	if(isFull(stack)){

	   grow(stack);
	}
	
	//The switch statement is used to check for items(char) that belong in alphabet L and are PUSHed into the stack.
	//In addition it checks for items(char) in alphabet L2 and checks if they are mapped to their corresponding value 
	//in alphabet L at the top of the stack. If its true then the top of the stack is POPed  
	switch(item){

		   case 'a': 
			    stack->array[++stack->top] = item;
				if(DebugMode == TRUE)
				{
					printf("Item PUSHED is: %c\n", item);
				}
				break;
		   case 'b': 
			    stack->array[++stack->top] = item;
				if(DebugMode == TRUE)
				{
					printf("Item PUSHED is: %c\n", item);
				}
				break;
		   case 'c': 
			    stack->array[++stack->top] = item;
				if(DebugMode == TRUE)
				{
					printf("Item PUSHED is: %c\n", item);
				}
				break;
		   case 'd': 
			    stack->array[++stack->top] = item;
				if(DebugMode == TRUE)
				{
					printf("Item PUSHED is: %c\n", item);
				}
				break;
		   case 'm': 
			    if('a' == stack->array[stack->top]){

			        if(DebugMode == TRUE){

				printf("Item POPED is: %c\n", stack->array[stack->top]);
				 	}

			       pop(stack);
		  	     	}
				break;
		   case 'n': 
				if('b' == stack->array[stack->top]){

				    if(DebugMode == TRUE){

				 	printf("Item POPED is: %c\n", stack->array[stack->top]);
				      }

			          pop(stack);
				   } 
				   break;
		   case 'o':
				if('c' == stack->array[stack->top]){

				    if(DebugMode == TRUE){

					printf("Item POPED is: %c\n", stack->array[stack->top]);
				      }

			       pop(stack);
				}
				break;
		   case 'p':
				 if('d' == stack->array[stack->top]){

				      if(DebugMode == TRUE){
 
					printf("Item POPED is: %c\n", stack->array[stack->top]);
				       }
			       pop(stack);
				}
				break;
		    default: 
				break;		
	}
	//NOTE: Debuging statements are used for the debuging tool and inform the user what items were poped or pushed 
}

//Function is used to remove the value at the top of the stack 
int pop(struct Stack* stack){
	
	//Checks if the stack is empty 
	if(isEmpty(stack) == 1){

		return -1;
	}
	//Removes value and sets new top value (one less)
	return stack->array[stack->top--];
	
}

//Function to return the top from the stack without removing it
int top(struct Stack* stack){

    //Checks if the stack is empty  
    if(isEmpty(stack) == 1)
	{
		return -1;
	}
    //If not empty then it returns the top of the stack
    return stack->array[stack->top]; 
} 

//Function used to remove and shift the extra letters in the a meaningful word 
void removeExtraLetter(char *validString)
{
	int y;
	int l = 0;
	
	char tmep;
	
	//Gets the length of the meaningful word
	int length2 = strlen(validString);
	
	//The loop cycles through each individual character in the meaningful word
	for(y = 0; y < length2; y++){
		
		//Stores the character in variable tmep	
		tmep = validString[y];
		 
		//The switch statement is used to check if any character in the meaningful word belongs to the L alphabet.
		//If it does then it is stored at an index defined by 'l'. The purpose of this is to get every meaningful 
		//character together and seperate them from non-meaningful characters
		switch(tmep){

		case 'a': 
			 validString[l] = 'a';
			 l++;
			 break;
		case 'b': 
			 validString[l] = 'b';
			 l++;
			 break;
		case 'c': 
			 validString[l] = 'c';
			 l++;
			 break;
		case 'd': 
			 validString[l] = 'd';
			 l++;
			 break;
		default:
			break;
		}
			
	 }
	
	char tmep2;
	
	//The loop cycles through each character of the modified meaningful word
	for(y = 0; y < length2; y++){
	
	//Character is stored into variable tmep2
	tmep2 = validString[y];
		
		//Checks for the first non-meaningful character and replaces it with a space
	        if((tmep2 != 'a')&&(tmep2 != 'b')&&(tmep2 != 'c')&&(tmep2 != 'd')){

		         validString[y] = ' ';
	                 break;
				
				
			}
		
		}
	
}

int main(int argc, char const *argv[])
{
	//Initializes the debug mode to be used by the user
	//This will allow them to see specific information 
	DebugMode = FALSE;
        int i;

	for ( i = 0 ; i < argc ; i++ ){

	    if( strcmp (argv[i], "-d") == 0 ){
			
		DebugMode = TRUE;
 		} 
	}
	
		
	char input[300];
	
/* set up an infinite loop */
 while (1)
 {
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';


   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
   {
     break;
   }
	 
   //printf ("%s\n", input);
   /*Start tokenizing the input into words separated by space
    We use strtok() function from string.h*/
   /*The tokenized words are added to an array of words*/
   
   char delim[] = " ";
   char *ptr = strtok(input, delim);
   int j = 0 ; 
   char *wordList[15];
  

	while (ptr != NULL)
	{	
		wordList[j++] = ptr;
		ptr = strtok(NULL, delim);

	}

	 //Creates a Stack with an initial size of 4 
	 struct Stack* stack1 = createStack(4);
	 
	 //Used for loops 
	 int m = 0;
	 int n = 0;
	 int o = 0;
	 
         int f = 0;
	 
	 //Char array that will hold the full decoded message 
	 char decoded[300];
	 
	 int length = 0;
	 int index = 0;
	 int length2 = 0;
	 
	 char c; 
	 char z; 
	 
	 //Used to store a meaningful word 
	 char* validString;
	 
	//The loop cycles through all the words in the message
	 for(m = 0; m < 15; m++){
	     
	     //Finds the length of the word
	     length = strlen(wordList[m]);
		 
		//Cycles through each individual character in the word
         	for(n = 0; n < length; n++){
		    
                    //Stores a character in variable c
               	    c = input[index]; 			 
		    
		    //Sends a character to be checked if they belong in alphabet L or L2 
		    //Could cause a push or pop
		    push(stack1, c);
		    
                    //The index is used to keep track of which index postion at array input it left off at.
                    index++;
		 
		 }
		 
		 //Checks if the stack is empty. If the stack is empty it means the word being checked is meaningful
		 if(isEmpty(stack1) == 1)
		 {	
		         //The meaningful word is stored into char variable validString
			 validString = wordList[m];
			 
			 //The meaningful word is sent through to be cleaned and modified from un-meaningful characters
			 removeExtraLetter(validString);
			 
			  //Cycles through each character of the meaninful word
			 for(o = 0; o < length; o++){
				 
				 //Stores the character in char variable z
				 z = validString[o];
				 
                                 //If any of the characters are found to be from alphabet L then they are stored
				 //in array 'decoded'
				 if((z == 'a')||(z == 'b')||(z == 'c')||(z == 'd')){

					 decoded[f] = z;
					 
					 f++;
				 }
			         //If a character is ' ' (space) then the loop terminates and the space is stored into the array 
				 else if(z == ' '){

					 decoded[f] = z;
					 
					 f++;
					 break;
				 }
			 }
			 
			 
		 }
		 else{
                        //If the stack is not found to be empty then the word was not meaningful and the stack is then cleared for the next word
			clear(stack1);
		 }
		 
		//Increases the index by one. This is so it can skip a space and start at the first character of 
		//of the next word.
		index++;
		
		//Checks for a NULL, if it is found it means that the message has reached its end and all words have been checked.
		if(input[index] == '\0'){

			 break;
		 } 
	 }	
	 
	 int g = 0;
	 
	 //Informs the user what the decoded message is
	 printf("The Decoded Message is: ");
	 
	//Loops and prints through all the characters of the array 'decoded'
	 for(g = 0; g < f; g++)
	 {
	    printf("%c", decoded[g]);
		 
	 }
	 
	 
 }

 printf ("\nGoodbye\n");

	return 0;
}

