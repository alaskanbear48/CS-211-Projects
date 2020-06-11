#include "Island7.h"

class ArchipelagoExpedition
{
 private:
   //Data Members for the Archipelago Network here
   Island* Darwin;	
   int N;
	
   //Making a String Link List to store text files  	
   MyStringList txtFiles;	
  
 public:
  
 //Use a constructor to initialize the Data Members for your expedition
 ArchipelagoExpedition()
 {
	 //Set a starting size of 10 islands
	 N = 11;
	 Darwin = new Island[N];
 }

 //Resize helper function 	
 void rezize(int n)
 {
	 //Set the new size
	 N = n + 1;
	 Darwin = new Island[N];
 }
  
  
 //The main loop for reading in input
 void processCommandLoop (FILE* inFile)
 {
  char  buffer[300];
  char* input;

  input = fgets ( buffer, 300, inFile );   // get a line of input
    
  // loop until all lines are read from the input
  while (input != NULL)
  {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok(input, " \n\t");

    printf ("*%s*\n", command);
    
    if ( command == NULL )
      printf ("Blank Line\n");
 
    else if ( strcmp (command, "q") == 0)//
	{
		
	   //Delete the Island Link List 	
	   for(int i = 0; i < N; i++)
	   {
		   if(!Darwin[i].isAdjEmpty())
		   {
			   Darwin[i].removeAllAdj();
		   }
	   
	   }
		
	  delete[] Darwin;
		
	  //Delete the text file link list 	
	  txtFiles.RemoveAll();
		
      exit(1);
	}
    else if ( strcmp (command, "?") == 0) 
      showCommands();
     
    else if ( strcmp (command, "t") == 0)
	{
      doTravel();
	  printf("\n");
	}
	else if ( strcmp (command, "s") == 0)
	{
	  doSP();
	  printf("\n");
	}
    else if ( strcmp (command, "r") == 0)
	{
      doResize();
	  printf("\n");
	}
    else if ( strcmp (command, "i") == 0)
	{
      doInsert();
	  printf("\n");
	}
    else if ( strcmp (command, "d") == 0)
	{
      doDelete();
	  printf("\n");
	}
    else if ( strcmp (command, "l") == 0)
	{
      doList();
	  printf("\n");	
	}
    else if ( strcmp (command, "f") == 0)
	{
      doFile();
	  printf("\n");
	}
    else if ( strcmp (command, "#") == 0)
      ;
     
    else
      printf ("Command is not known: %s\n", command);
     
	//Let the user know they can input another command   
	printf ("Input next command:\n");  
    input = fgets (buffer, 300, inFile);   // get the next line of input

  }
 }

 //DFS Helper function 	
 void depthFirstSearchHelper(int x, int y)
 {
	 //Mark all islands as unvisited
	 for(int i = 0; i < N; i++)
	 {
		 
		 Darwin[i].setVisited(false);
		 
	 }
	 
	 if(dfs(x, y) == true)
	 {
		 printf("You can get from Island %d to Island %d in one or more ferry rides.\n", x, y);
	 }
	 else
	 {
		 printf("You can NOT get from Island %d to Island %d in one or more ferry rides.\n", x, y);
	 }
	 
	 
 }

 //Depth First Search function
 bool dfs(int a, int b)
 {
	int c = 0;
	
	//For every island c that can be reached from a in one ferry ride 
	for(int i = 0; i < Darwin[a].findLength(); i++)
	{
		c = Darwin[a].findIsland(i);
		
		if(c == b)
		{
			return true;
		}
		
		//If Island C is unvisited
		if(!Darwin[c].isVisited())
		{
			//Mark Island C as visited
			Darwin[c].setVisited(true);
			
			if(dfs(c, b) == true)
			{
				return true;
			}
		}
			
	}
	return false;
}

//BFS Helper function
bool bfs(int b, MyQueue& islandQ)
{
	//Index variables 
	int a = 0;
	int c = 0;
	
	//Check if the Queue is empty 
	while(!islandQ.emptyQ())
	{
		//Check current Island 
		a = islandQ.popQ();
		
		//Check each adjcent island to a 
		for(int i = 0; i < Darwin[a].findLength(); i++)
		{
			//Check adjcent island 
			c = Darwin[a].findIsland(i);
			
			//If adjcent island c has previous = to -1
			if(Darwin[c].getPreV() == -1)
			{
				//Set island a to previous island of c 
				Darwin[c].setPreV(a);
				
				//If island c equalls b then return true 
				if(c == b)
				{
					return true;
				}
				
				//Insert Island to queue 
				islandQ.insertQ(c);
			}
			
		}
		
	}
	
	//Return false if island b is not found 
	return false;
}
		
//Breath First Search function	
MyStack breadthFirstSearch(int x, int y)
{
	//Index variable
	int c = -1;
	
	 //Mark all islands as unvisited (prev = -1)
	 for(int i = 0; i < N; i++)
	 {
		 Darwin[i].setVisited(false);
		 Darwin[i].setPreV(-1);
	 }
	
	//Create a new Queue and Stack 
	MyQueue islandQ;
	MyStack islandSK;
	
	//Insert starting island to queue 
	islandQ.insertQ(x);
	
	//If island y cannot be reached then print message 
	if(bfs(y, islandQ) == false)
	{
	   printf("You can NOT get from Island %d to Island %d in one or more ferry rides.\n", x, y);
	   //Make sure to destroy the queue 
	   return islandSK;
	}
	else 
	{
		//Else: Island y could be reached thus print the message 
		printf("You can get from Island %d to Island %d in one or more ferry rides.\n", x, y);
		
		//Assign c to y 
		c = y;
		
		//Inset c to stack 
		islandSK.insertSK(c);
		
		//Insert all islands in path x to y into stack 
		do{
			c = Darwin[c].getPreV();
			islandSK.insertSK(c);
			
		}while(c != x);
		
		//Return Stack with path 
		return islandSK;
	}
	
	
	
}
	
 //Find the shortest path between island x and y 	
 void doSP()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
 
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");

   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
	 //Error checking. If no errors then DFS is used  
	 if((val1 > N - 1 || val1 < 0) || (val2 > N - 1 || val2 < 0))
	 {
		 printf("One of the Islands does not exist.\n");
	 }
	 else if(Darwin[val1].isAdjEmpty())
	 {
		 printf("Island %d does not have any edges to any other island.\n", val1);
	 }
	 else
	 {
		printf("Performing the Shortest Path Command from %d to %d\n", val1, val2);
		 
		//Perform BFS and get stack with shortest path 
		MyStack List = breadthFirstSearch(val1, val2);
		
		 //If Stack is not returned empty then print shortest path 
		 if(!List.emptySK())
		 {
			List.showSK(); 
		 }	
	 }
 }
		
 //Display commands	
 void showCommands()
 {
   printf ("The commands for this project are:\n");
   printf ("  q \n");
   printf ("  ? \n");
   printf ("  # \n");
   printf ("  s <int1> <int2> \n");	 
   printf ("  t <int1> <int2> \n");
   printf ("  r <int> \n");
   printf ("  i <int1> <int2> \n");
   printf ("  d <int1> <int2> \n");
   printf ("  l \n");
   printf ("  f <filename> \n");
 }
 
 //Check if it is possible to travel from point a to point b 
 void doTravel()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
 
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");

   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
	 //Error checking. If no errors then DFS is used  
	 if((val1 > N - 1 || val1 < 0) || (val2 > N - 1 || val2 < 0))
	 {
		 printf("One of the Islands does not exist.\n");
	 }
	 else if(Darwin[val1].isAdjEmpty())
	 {
		 printf("Island %d does not have any edges to any other island.\n", val1);
	 }
	 else
	 {
		printf("Performing the Travel Command from %d to %d\n", val1, val2);
		depthFirstSearchHelper(val1, val2);
	 }
	  
 }
 
 //Resize Island array
 void doResize()
 {
   int val1 = 0;
   
   //Get an integer value from the input
   char* next = strtok(NULL, " \n\t");
   
   if (next == NULL)
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi(next);
   if (val1 == 0 && strcmp(next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }	 
	//Check if the resize value is greater than 0
	if(val1 == 0)
	{
		return;
	}
	 
   printf ("Performing the Resize Command with new size of %d\n", val1);

	 Island* tmp = Darwin;
	 
   //Delete all the values of the old Island Array 
   for(int i = 0; i < N; i++)
   {
	   if(!tmp[i].isAdjEmpty())
	   {
		   tmp[i].removeAllAdj();
	   }
	   
   }
	 delete[] tmp;
	 
	 //Create a new array with the new size 
	 rezize(val1);
	 
	  
 }
 
 //Insert edge to Island Array 
 void doInsert()
 {
	int val1 = 0;
    int val2 = 0;
	 
	 
   //Get an integer value from the input
   char* next = strtok(NULL, " \n\t");
   
   if (next == NULL)
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi(next);
   if (val1 == 0 && strcmp(next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
	 
   //Get another integer value from the input
   next = strtok(NULL, " \n\t");
	 
   if(next == NULL)
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi(next);
	 
   if(val2 == 0 && strcmp(next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
	 
	//Error checking. If it passes then the edge can be inserted 
	if((val1 > N - 1 || val1 < 0) || (val2 > N - 1 || val2 < 0))
	{
		printf ("One Island does not exist.\n");
	}
	else if(Darwin[val1].findAdjacent(val2) == val2)
	{
		printf("Adjacent has already been inserted.\n");
	}
	else
	{
		
	//Insert the edge into the link list for that specific Island
	printf ("Performing the Insert Command with %d and %d\n", val1, val2);
	Darwin[val1].insertAdjacent(val2);  
	 	
	}
 }
 
 //Delete an edge from the Island Array 	
 void doDelete()
 {
	int val1 = 0;
    int val2 = 0;
	 
	 
   //Get an integer value from the input
   char* next = strtok(NULL, " \n\t");
   
   if (next == NULL)
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi(next);
   if (val1 == 0 && strcmp(next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
	 
	 
   //Get another integer value from the input
   next = strtok(NULL, " \n\t");
  
   if(next == NULL)
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi(next);
   if(val2 == 0 && strcmp(next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
	 
	 //Error checking. If it passes then an Edge can be deleted 
	 if((val1 > N - 1 || val1 < 0) || (val2 > N - 1 || val2 < 0))
	 {
		 printf ("An Island does not exist an cannot be deleted.\n");
	 }
	 else if(Darwin[val1].isAdjEmpty() || Darwin[val2].isAdjEmpty())
	 {
		 printf ("An Island cannot be reached and has no edges.\n");
	 }
	 else
	 {
		//Delete the edge into the link list for that specific Island
		printf ("Performing the Delete Command with %d and %d\n", val1, val2);
		Darwin[val1].removeAdjacent(val2); 
	 }
 }
 
 //Show all the corresponding edges for every island in the array 
 void doList()
 {
	 //Loop through every possible island 
	 for(int i = 0; i < N; i++)
	 {
		 if(!Darwin[i].isAdjEmpty())
		 {
			 printf("Island %d has these edges:\n", i);
			 Darwin[i].showAdjacents();
		 }
		 else
		 {
			 printf("Island %d is empty and has no edges.\n", i);
		 }
		  
	 }
	 
 }
 
 //Read commands from a txt file and open txt file  
 void doFile()
 {
   // get a filename from the input
   char* fname = strtok (NULL, " \n\t");
   if ( fname == NULL )
   {
     printf ("Filename expected\n");
     return;
   }
   
   printf ("Performing the File command with file: %s\n", fname);
   
   
     //Verify the file name is not currently in use
     char a[50];  
	 strncpy(a, fname, sizeof(a));
	 
	  if(txtFiles.Search(a))
	   {
		   printf ("File Has already been used.\n");
		   return;
	   }
	   else
	   {
		   txtFiles.insert(a);
	   }
	 
         //Open the file using fopen creating a new instance of FILE*
		 FILE* inFile;
		 inFile = fopen(fname, "r");
	 
	 
         //Recursively call processCommandLoop() with this new instance of FILE* as the parameter
         if(inFile == NULL)
		 {
			 printf("File does not exist.\n");
			 return;
		 }
		 
		  processCommandLoop(inFile);
	 
         //Close the file when processCommandLoop() returns
         fclose(inFile);
		  
 }
	
};

int main (int argc, char** argv)
{
  // set up the variable inFile to read from standard input
  FILE* inFile = stdin;

  // set up the data needed for the island adjcency list
  ArchipelagoExpedition islandData;
   
  // call the method that reads and parses the input
  islandData.showCommands();
  printf ("\nEnter commands at blank line\n");
  printf ("    (No prompts are given because of f command)\n");
  islandData.processCommandLoop (inFile);
   
  printf ("Goodbye\n");
  return 1;
 }


