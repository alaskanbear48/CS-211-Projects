//The purpose of this program is to allow a user to input as many integer values as they want with a terminal value of -999 following their input.
//Their input will later be sorted in ascending order. Then the program will ask the user to input desired target values that they wish to find from
//the list of integers they had previously input. The program will then try to find two values that if added together will equal a target value. If the target 
//is found then the user is informed if the target is or is not found. The program features the use of calloc wich allowed the creation of Dynamic array allocation.
//This allowed for the array of the program to be dynamic and expand in size beyond its original size if needed.
//CS 211 Program 1 UIC <Manuel M Martinez> 

#include <stdio.h>
#include <stdlib.h>

//The function makes the pointers traverse the array from opposite sides in order to find 
//a sum of two values that is equal to the target value the user wants 
int TwoSumFunction(int array2[], int size2, int target, int *index1, int *index2)
{
	//Make the sum start equal to zero 
	int sum = 0;
	
	//Token2 is equal to zero to begin
	//Token2 will be return and will let the user know if their target value was found 
	int token2 = 0;
	
	//Loop will continue to loop until token2 is given a value that is not equal to zero 
	//This would mean that either the target was found or not found 
	do{
		//The sum of two values at a given index are calculated 
		sum = array2[*index1] + array2[*index2];
		
		//If index1 and index2 are equal and point at the same index value then the target value cannot be found (returns -1)
		if(*index1 == *index2){
			token2 = -1;
		}
		//If the sum is not equal to the target value and both index 1 & 2 are equal then the 
		//target value cannot be found (returns -1)
		else if((sum != target) && (*index1 == *index2))
		{
			token2 = -1;
		}
		//If the sum of two values equals the target value then return 1 (target found)
		else if(sum == target){
			token2 = 1;
		}
		//If the sum is greater than the target value then index2 will shift to the left index by one  
		else if(sum > target){
			*index2 = *index2 - 1; 
		}
		//If the sum is less than the target value then index1 will shift to the right index by one  
		else if(sum < target){
			*index1 = *index1 + 1;
		}
		
	 //Loop will continue to work until the target value is found or not found 	
	}while(token2 == 0);
	
	//Ruturn the value of token2 (1 or -1)
	return token2;
	
}

//Function serves to sort the values in the new array into order of least to greatest
//The purpose of this is to make it easier to find the target value later on in the program 
void myFavoriteSort (int array2[], int size)
{
	//Loop counters
	int i, j;
	
	//'hold' is used for switching two values in the array 
	int hold; 
	
	//Array is sorted by bubble sort 
    for (i = 0; i < size-1; i++){
	   
      for (j = 0; j < size-i-1; j++){
		
		//If true then the value of array2[j] is switched 
		//with the value of array2[j+1] using variable hold 
        if (array2[j] > array2[j+1]){
			
                hold = array2[j];
				array2[j] = array2[j+1];
				array2[j+1] = hold;
		}
	  }
    }	 



}

//Makes a copy of the original array and stores all of the user input values into a new array
void makeArrayCopy (int array1[], int array2[], int size2)
{
	   //Used for loop 
       int x;
    
	   //Loop traverses the original array up to index 'size2 - 1' in order to prevent unnecessary  
	   //0s from being stored in the new array  
       for(x = 0; x < size2; x++){
           
           array2[x] = array1[x];
       }
       
    
}

//Main section of code that prints out all the information regarding the specific input the
//user provided 
int main (int argc, char** argv)
{

	//Variable Used for Loops 	
	int i;    
	
	//Variable assigned to user input	
	int value; 
	
	//Determines the overall list size of numbers that was input by the user
	int counter = 0; 
    
	//Creates a dynamic allocated array 
	int* array1;
	int size = 10; //Sets the first initial size of the array

	//Allocates memory space for the created first array 	
	array1 = (int *) malloc (sizeof(int) * size); 
 
	//Pointer that will point at the old array when it is expanded 
	int* temp;
	
	//User input information 
	printf ("Enter in a list of numbers ito be stored in a dynamic array.\n");
	printf ("End the list with the terminal value of -999\n");
    
	//User input is stored in variable 'value'	
	scanf ("%d", &value); 

	//Loop checks each indivdidual value that is input by the user and checks for terminal value 	
	while(value != -999){
	
		//Checks if the array has not exceded its capacity 
		if(counter < size){
	
			//Value is stored in the first array 	
			array1[counter] = value;
        }
	    
		//Checks if the array has exceded its capacity
	    //If it has, then it will increase the size of the array 
		else if(counter >= size){
		
		   //Pointer 'temp' points at array1(old memory allocation)
		   temp = array1;
       
		   //New memory is allocated for the new array with a greater size 
		   array1 = (int *) malloc ( size * 2 * sizeof(int));
       
	       //Old values are stored in the new array 
	       for(i = 0; i < size; i++){
		   
           array1[i] = temp[i];
           
            }
        
		//Memory from the old array is freed 
		free(temp);
		
		//Size is updated to the new size 
        size = size * 2;
        
		//Starts the loop from the beggining to prevent going to the next value 
        continue;
        } 
	
	//After each value is checked the counter is increased by one in order to keep track 
	//of how many variables are being stored in the array (checks for size limit reach)
    counter++;
	
	//Stores the next user input into value for it to be checked by the loop 
    scanf("%d", &value);
   }
    
	//A new array is created. This array will be sorted.
	//The new size will be equal to counter in order to prevent 0s from being sorted 
	//These 0s coming from unused memory in the first array when it is expanded in size.
    int size2 = counter;
    int array2[size2];
    
	//Copies the values from the first array to the second array
    makeArrayCopy(array1, array2, size2);
	
	//Sorts the second array is ascending order using a bubble sort 
	myFavoriteSort (array2, size2);
	
	//index 1 and 2 are used to traverse the array in order to find two numbers that 
	//are the sum of the target user value
	int index1;
	int index2;
	
	//Token is used to determine if the target user value is found or not found 
	int token = 0;
	
	//Target value user is trying to find by adding two numbers together in the array 
	int val;
	
 //User information	
 printf ("Enter in a list of numbers to use for searching.  \n");
 printf ("End the list with a terminal value of -999\n");
 scanf ("%d", &val);
 
 //Main loop to find target value 
 while (val != -999)
   {
     //Index 1 is equal to the first value of the array at the left
     //Index 2 is equal to the last value of the array at the right  
	 index1 = 0;
	 index2 = size2 - 1;
	 
	 //Calls function to perform target sum operation
	 //The return value is assigned to variable 'token' 
	 token = TwoSumFunction(array2, size2, val, &index1, &index2);
	
	 //Stores the target value of the user into variable 'val'
	 printf("Target: ");
	 printf("%d ", val);
	 
	 //If the token returns as 1 then the target value is found
	 if(token == 1){
		 
		 printf("YES! ");
		 
		 printf("Index: ");
		 
		 printf("%d ", index1);
	 
	     printf("%d ", index2);
		 
		 printf("\n");
	 }
	 //If the token returns as -1 then the target value was not found 
	 else if(token == -1){
		 
		 printf("NO! \n");
	 }
      

    //Get next user target value 
    scanf("%d", &val);
   }

   //Informs user the program has ended 
   printf ("Good bye\n");
    


return 0;
}
