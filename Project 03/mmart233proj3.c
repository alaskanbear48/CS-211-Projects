//The purpose of this Program is to use a stack link list data structure that will allow us to determine if a Maze of certain dimensions has a traversable path. The program uses a 
//Depth First Search algorithm that utilizes the aforementioned data structure and traverses each possible path in the given maze. If the algorithm cannot find a path then it will 
//display that No path was found. If a path is do found it will display the cordinates that make up the path that was able to reach to the end of the maze.  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int DebugMode;

//Creates our Node Struct to be used for a Link List 
struct NODE{
	
	int X;
	int Y;
	
	struct NODE* Next; 
};

//Initializes an empty stack to be used
void createStack(struct NODE* Head)
{
	Head = NULL;
}

//Function pushes two cordinate values into the Node
struct NODE* push(struct NODE* Head, int x, int y){
	
	//Allocates memory for a new Node
	struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
	
	//Stores values into new node
	newNode->X = x;
	newNode->Y = y; 
	newNode->Next = Head;
	
	//Sets the top of the stack to the new node being pushed
	Head = newNode;
	
	if(DebugMode == TRUE){
		printf("The coordinates being pushed are: (%d, %d)\n", Head->X, Head->Y);	
	}
	
	return Head;
}

//Function is used to pop the top of the stack 
struct NODE* pop(struct NODE *Head){

	if(DebugMode == TRUE){
	   printf("The coordinates being poped are: (%d, %d)\n", Head->X, Head->Y);	
	}

	//Temporary pointer points at the top of the stack 
	struct NODE* tmp = Head;

	//Head Moves down the stack
	Head = Head->Next;
	
	//Top of the stack is removed and its memory freed
	free(tmp);
	
	return Head;
}

//Function is used to determine if the stack is empty 
int empty(struct NODE* Head){
	
	//Returns 1 if the stack is empty 
	return Head == NULL;	
}

//This function is used to clear the stack and free all the 
//memory used in each stack node
void clear(struct NODE* Head){

	//Creates a new Pointer 
	struct NODE* temp;
	
	//Loop while the stack is not empty 
	while(!empty(Head)){

	   temp = Head;
	   Head = Head->Next;//Move down the stack
	   free(temp);//Free memory used by top Node
		
	}
	
}

//The function is used for returning the cordinate values that are stored at the top of the stack
//Untilizes pass by reference
void top(struct NODE* Head, int *x, int *y){

	*x = Head->X;
	*y = Head->Y;
}

//The purpose of this function is to display the cordinate values that form the path 
//Towards the end of the maze 
void display(struct NODE* head){

    //New Pointer that points at the top of the stack     	
    struct NODE *current;
    current = head;

    //Checks if the current stack is not empty      
    if(current!= NULL){

        printf("Path: ");
        do{
            printf("(%d, %d)", current->X, current->Y);
	    printf("\n");
            current = current->Next;
        }
        while (current!= NULL);//Loops until the stack has reached its end 
        printf("\n");
    }
    else{
        printf("The Stack is empty\n");
    }
 
}
	
//The purpose of this function is to free the memory that is allocated when a 2D array is created 
void destroyTwoDimenArrayOnHeapUsingFree(char ** ptr, int row, int col){
	int i;

	for( i = 0; i < row; i++){
		free(ptr[i]);//Free memory 
	}
	free(ptr);//Free pointer to array 
	
}

//Struct used to initialize maze
typedef struct mazeStruct
{
 char **arr;//Used to create a dynamic 2D array 
 char **tmp;//Used to grow the maze 
	
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

int main (int argc, char **argv)
{
	
    //Used for Debug Mode	
    DebugMode = FALSE;
    int l;
	for ( l = 0 ; l < argc ; l++ ){
		if( strcmp (argv[l], "-d") == 0 ){
			DebugMode = TRUE;
		    } 
	}
	
  //Create a maze struct 	
  maze m1;

  //Initializes the starting size of the array 	
  int row = 32;
  int colum = 32;
  int h;
   
  //Creates a dynamic 2D array using pointers 	
  m1.arr = (char**)malloc(row*sizeof(char*));
  for(h = 0; h < row; h++){

	  m1.arr[h] = (char*)malloc(colum*sizeof(char*));
  }

  //Used to store values in 2D array 
  int xpos, ypos;
  int i,j;

  FILE *src;

  /* verify the proper number of command line arguments were given */
  if(argc != 2) {
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
  }
   
  /* Try to open the input file. */
  if ( ( src = fopen( argv[1], "r" )) == NULL)
  {
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }
 

  /* read in the size, starting and ending positions in the maze */
  fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
  
  //If either of the x & y dimensions are less than 1 then its an error and the program exits
  if(m1.xsize < 1 || m1.ysize < 1)
  {
	  printf("STANDARD ERROR\n");
	  destroyTwoDimenArrayOnHeapUsingFree(m1.arr, row, colum);
	  fclose(src);
	  exit(0);
  }

  //If either the x & y starting postion is greater than the dimensions or less than 1 then its an error  
  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
  if(m1.xstart > m1.xsize || m1.xstart < 1)
  {
	  printf("STANDARD ERROR\n");
	  destroyTwoDimenArrayOnHeapUsingFree(m1.arr, row, colum);
	  fclose(src);
	  exit(0);
  }
  if(m1.ystart > m1.ysize || m1.ystart < 1)
  {
	  printf("STANDARD ERROR\n");
	  destroyTwoDimenArrayOnHeapUsingFree(m1.arr, row, colum);
	  fclose(src);
	  exit(0);
  }
  
  //If either the x & y end postion is greater than the dimensions or less than 1 then its an error
  fscanf (src, "%d %d", &m1.xend, &m1.yend);
  if(m1.xend > m1.xsize || m1.xend < 1)
  {
	  printf("STANDARD ERROR\n");
	  destroyTwoDimenArrayOnHeapUsingFree(m1.arr, row, colum);
	  fclose(src);
	  exit(0);
  }
  if(m1.yend > m1.ysize || m1.yend < 1)
  {
	  printf("STANDARD ERROR\n");
	  destroyTwoDimenArrayOnHeapUsingFree(m1.arr, row, colum);
	  fclose(src);
	  exit(0);
  }

  /* print them out to verify the input */
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n", m1.xend, m1.yend);

  //If the size is greater than the maximum dimensions that the maze can create then more memory is allocated and 
  //a new 2D array is dynamically created 
  if(m1.xsize > 30 || m1.ysize > 30)
  {
      m1.tmp = m1.arr;
	  
      //Allocates new memory for the bigger array (2 times bigger)
      m1.arr = malloc((row*2) * sizeof(char*));
      for(h = 0; h < (row*2); h++)
      {
		m1.arr[h] = malloc((colum*2) * sizeof(char*));
      }
	  
	  //Frees the allocated memory of the old array 
	  destroyTwoDimenArrayOnHeapUsingFree(m1.tmp, row, colum);
	  
	  //Updates the dimensions
	  row = row * 2;
	  colum = colum * 2;
	  
  }
	
  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
     for (j = 0; j < m1.ysize+2; j++)
       m1.arr[i][j] = '.';

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++)
    {
     m1.arr[i][0] = '*';
     m1.arr[i][m1.ysize+1] = '*';
    }
  for (i=0; i < m1.ysize+2; i++)
    {
     m1.arr[0][i] = '*';
     m1.arr[m1.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';
		  
  /* mark the blocked positions in the maze with *'s */
  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
	 //If one of the block cordinates blocks the starting or ending position
	 //Then it is an error and the program will exit 
	 if(xpos == m1.xstart && ypos == m1.ystart)
	 {
	  printf("STANDARD ERROR\n");
	  destroyTwoDimenArrayOnHeapUsingFree(m1.arr, row, colum);
	  fclose(src);
	  exit(0);
	 }
	 else if(xpos == m1.xend && ypos == m1.yend)
	 {
	  printf("STANDARD ERROR\n");
	  destroyTwoDimenArrayOnHeapUsingFree(m1.arr, row, colum);
	  fclose(src);
	  exit(0);
	 }
	 else{
	     m1.arr[xpos][ypos] = '*';
	 }
    }
		
  /* print out the initial maze */
  for (i = 0; i < m1.xsize+2; i++)
    {
     for (j = 0; j < m1.ysize+2; j++)
       printf ("%c", m1.arr[i][j]);
     printf("\n");
    }

	
	//Depth First Algorithm 
	
	//Token is used to determine if a path was found or not	
	int token = 0;
	
	int x = m1.xstart;
	int y = m1.ystart;
	
	//Create a new Stack
    	struct NODE* Head = NULL;
	createStack(Head);
	
	//Push the starting postion into the stack 
	Head = push(Head, x, y);
	
	//Infinite loop until a path is found or not found
	//Checks Right, Down, Left, and Up starting from the starting position. 
	//If a position is visited it is marked with a 'v' and pushed into the stack
	while(1)
	{
		//Checks if the path has reached the end point 
		if(x == m1.xend && y == m1.yend)
		{
			token = 1;
			break;
		}

		//Can only visit a position if its not blocked, has not been visited, and is not the starting position		
		//Turn Right
		else if(m1.arr[x][y+1] != '*' && m1.arr[x][y+1] != 'v' && m1.arr[x][y+1] != 's')
		{
			y = y + 1;
			m1.arr[x][y] = 'v';
			Head = push(Head, x, y);
			
		}
		//Turn Down
		else if(m1.arr[x+1][y] != '*' && m1.arr[x+1][y] != 'v' && m1.arr[x+1][y] != 's')
		{
			x = x + 1;
			m1.arr[x][y] = 'v';
			Head = push(Head, x, y);
			
		}
		//Turn Left 
		else if(m1.arr[x][y-1] != '*' && m1.arr[x][y-1] != 'v' && m1.arr[x][y-1] != 's')
		{
			y = y - 1;
			m1.arr[x][y] = 'v';
			Head = push(Head, x, y);
		}
		//Go Up 
		else if(m1.arr[x-1][y] != '*' && m1.arr[x-1][y] != 'v' && m1.arr[x-1][y] != 's')
		{
			x = x - 1;
			m1.arr[x][y] = 'v';
			Head = push(Head, x, y);
		}
		//If the current position cannot move in any direction then it is popped from the stack and the previous positon is now
		//In the top of the stack
		else{
			Head = pop(Head);
			if(empty(Head) == 1){
				break;
			}
			
			else{
			top(Head, &x, &y);
			}
		}
			
	}
	
	
	//If a path has been found then the path is displayed in cordinate points
	if(token == 1)
	{
		printf("Right Path was found!\n");
		display(Head);
		
	}
	//If the path is not found then it is displayed as a message
	else if(token == 0)
	{
		printf("No Path was found.\n");
	}
	
	//Clears the stack and frees memory in order to prevent any memory leaks and to be used again
	clear(Head);
	
	//Frees the allocated memory of the created 2D array
        destroyTwoDimenArrayOnHeapUsingFree(m1.arr, row, colum);
	
	//Closes the file that was opened 	
	fclose(src);


}

