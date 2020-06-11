#include "sc.h"

//Initializes an empty stack to be used
void createQueue(struct NODE* Head)
{
	Head = NULL;
}

//Creates order (Node) and adds it to the list (In-Restuarant)
struct NODE* addToList(struct NODE* Head, char *orderName, int numBurgers, int numSalads, boolean orderStatus)
{
	
	//Allocates memory for a new Node
	struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
	
	//Pointers used to help in adding nodes into list
	//Will make it easy to Keep the front pointer at the front without moving it 
	struct NODE* tmp = NULL;
	struct NODE* Hermes = Head;
	
	//Stores order details into new node
	newNode->Name = orderName;
	newNode->Burgers = numBurgers;
	newNode->Salads = numSalads;
	newNode->Status = orderStatus;

	//Only if the first order is being added to the list (List is empty)
	//Set the front of the list  
	if(Head == NULL)
	{
	newNode->Next = Head;
	Head = newNode;
	}
	//If List is not empty then add Node into List 
	else
	{
		//Set Next of newNode to NULL 
		newNode->Next = tmp;
		tmp = newNode;
		
		if(DebugMode == TRUE){
			printf("The values traversed on ADDTOLIST are: (%s, %d, %d, %d)\n", Hermes->Name, Hermes->Burgers, Hermes->Salads, Hermes->Status);	
	          }
	
		//Traverse the list to find the last node 
		while(Hermes->Next != NULL)
		{
			Hermes = Hermes->Next;
			
			if(DebugMode == TRUE){
			printf("The values traversed on ADDTOLIST are: (%s, %d, %d, %d)\n", Hermes->Name, Hermes->Burgers, Hermes->Salads, Hermes->Status);	
	          }
		
		}
			//Connect the last Node in the list to the newNode 
			//Making it the new Last Node 
		    Hermes->Next = tmp;
		
	}

	return Head;
}

//Function Checks if a given Name exists in the Order List 
boolean doesNameExist(struct NODE* Front, char *givenName)
{
	//Variable used to check if Group names match 
	int result;
	struct NODE* Head = Front;
	
	//Traverse List to find a matching Group Name 
	while(Head != NULL)
	{
		if(DebugMode == TRUE){
			printf("The values traversed on DOESNAMEEXIST are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	
		
		//Compare Given Name and Node Names
		result = strcmp(givenName, Head->Name);
		
		//If Names match then Name exists in Order List 
		if(result == 0)
		{
			//Name found
			return TRUE;
		
		}
		else
		{
			Head = Head->Next;
		}
		
	}
    
	
	//Name was not found 
	return FALSE;
	
}

//Function is used to check if an Order is In-Restuarant or a Call ahead Order 
boolean updateStatus(struct NODE* Front, char *givenName)
{
	//Variable Used to check if Names Match 
	int result;
	struct NODE* Head = Front;
	
	//Traverse List to find matching names 
	while(Head != NULL)
	{
		if(DebugMode == TRUE){
			printf("The values traversed on UPDATESTATUS are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	
		
		//Check if Order Name in List and Given Name match 
		result = strcmp(givenName, Head->Name);
		
		//If Both Names match Check if it's an In-Restuarant or Call Ahead Order 
		if(result == 0)
		{
			//Order is Call Ahead
			if(Head->Status == NO)
			{
				return TRUE;
			}
			//Order is In-Restuarant
			else if(Head->Status == YES)
			{
				return FALSE;
			}
		}
		else
		{
			Head = Head->Next;
		}
		
	}
	
	//If Name was Not found then Return False 
	return FALSE;
	
}

//Function is used to Update the order status of a group 
struct NODE* changeStatus(struct NODE* Front, char *givenName)
{
	//Variable used to check for matching Names 
	int result;
	struct NODE* Head = Front;
	
	//Traverse List Looking for matching Names 
	while(Head != NULL)
	{
		if(DebugMode == TRUE){
			printf("The values traversed on CHANGESTATUS are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	
		
		//Compare Names to check for a match 
		result = strcmp(givenName, Head->Name);
		
		//If Names Match then Change the order status to In-Restuarant
		if(result == 0)
		{
			Head->Status = YES;
			return Front;
		}
		else
		{
			Head = Head->Next;
		}
		
	}
	
}

//The purpose of this function is to check that order specifications can be found in order list to be retrived 
boolean checkForValidNumbers(struct NODE* Front, int numSalads, int numBurgers)
{
	struct NODE* Head = Front;
	
	//Traverse List to look for order specifications
	while(Head != NULL)
	{
		if(DebugMode == TRUE){
			printf("The values traversed on CHECKFORVALIDNUMBERS are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	
		//If the order specifications are found and it is In-Restuarant then return True 
		if(Head->Burgers <= numBurgers && Head->Salads <= numSalads && Head->Status == YES)
		{
			return TRUE;
		}
		else
		{
			Head = Head->Next;
		}
	}
	
	//If Specifications are not found then Return False 
	return FALSE;
}

//The purpose of this function is to retrive the name of an order that will be delivered (Deleted)
char *retriveName(struct NODE* Front, int numSalads, int numBurgers)
{
	struct NODE* Head = Front;
	
	//Traverse List looking for order specifications
	while(Head != NULL)
	{
		if(DebugMode == TRUE){
			printf("The values traversed on RETRIVENAME are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	
		
		//If specifications are found then Group name is returned 
		if(Head->Burgers <= numBurgers && Head->Salads <= numSalads && Head->Status == YES)
		{
			return Head->Name;
		}
		else
		{
			Head = Head->Next;
		}
	}
	
	
}

//The purpose of this Function is to Remove an order from the Order List (order delivered)
struct NODE* retriveAndRemove(struct NODE* Front, int numSalads, int numBurgers)
{
	//Pointers used to Delete Node and Keep the main pointer to point to the front of the list 
	struct NODE* Head = Front;
	struct NODE* prev;
	struct NODE* tmp;
	
	//Variable to store Malloc allocated memory
	char *name;
	
	//This is in the scenario that the Front is removed and makes the next order the new front 
	if(Front != NULL && Front->Burgers <= numBurgers && Front->Salads <= numSalads && Front->Status == YES)
	{
		//When there is only one Node, the List is now empty
		if(Front->Next == NULL)
		{
			name = Front->Name;
			Front = NULL;
			
			//Free Node and Malloc Allocated Memory
			free(name);
			free(Head);
			
			return Front;
		}
		//If There is more than one node in the list the next node is now the front of list 
		else{
			
		name = Front->Name;	
		Front = Front->Next;
		
		Head->Next = NULL;
			
		//Free Node and Malloc Allocated Memory
		free(name);	
		free(Head);
		
		return Front;
		}
	}
	//If the Front of List is not being removed then this will execute 
	else
	{
		//Traverse Node to look for Order to be removed
		while(Head != NULL)
		{
			if(DebugMode == TRUE){
				printf("The values traversed on RETRIVEANDREMOVE are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	
		 
			//If order specifications are found then Delete and rearange List 
			if(Head->Burgers <= numBurgers && Head->Salads <= numSalads && Head->Status == YES)
			{
				//This is for when the Back of the Queue is Poped and the previous order is the new back
				if(Head->Next == NULL)
				{
				  name = Head->Name;
				  prev->Next = NULL;
				
				  //Free Node and Malloc Allocated Memory
				  free(name);
				  free(Head);
					
				  return Front;
				
				}
				//If node is not the back or the front then Delete Node 
				else{
					tmp = Head;
					Head = Head->Next;
			
					name = tmp->Name;
					tmp->Next = NULL;
					prev->Next = Head;
			
					//Free Node and Malloc Allocated Memory
					free(name);
					free(tmp);
			
					return Front;
				}
			}
			//Move to Next Node 
			else
			{
				prev = Head;
				Head = Head->Next;
			}
	}
  }
}

//The purpose of this function is to calculate the amount of orders ahead of a specific order 
int countOrdersAhead(struct NODE* Front, char *givenName)
{
		int result;
		struct NODE* Head = Front;
			
		//Variable Stores # of orders ahead 
		int i = 0;
		
		//Traverse List looking for group Name 
		while(Head != NULL)
		{
			if(DebugMode == TRUE){
			printf("The values traversed on COUNTORDERSAHEAD are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	
			
			//Compares Given Name and List Group Name 
			result = strcmp(givenName, Head->Name);
			
			//If Group Name is found then Break out of loop 
			if(result == 0)
			{
				break;
			}
			//If group Name is not found then increase i by one
			//Each increase means there is an order ahead 
			else
			{
				Head = Head->Next;
				i++;
			}
		}
		
		//return the amount of orders ahead of a specific order 
		return i;

	}

//Function is used to calculate the waiting time for a specific order 
int displayWaitingTime(struct NODE* Front, char *givenName)
{
	    int result;
		struct NODE* Head = Front;
		
		//Store the waiting time for an order  
		int waitingTime = 0;
		
		//Traverse List to look for an order name 
		while(Head != NULL)
		{
			if(DebugMode == TRUE){
			printf("The values traversed on DISPLAYWAITINGTIME are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	
			
			//Compare given name and Node group name 
			result = strcmp(givenName, Head->Name);
			
			//If Group name matches then Node with order details was found thus break from loop 
			if(result == 0)
			{
				break;
			}
			else
			{
				Head = Head->Next;
			}
		}
	
		//Calculate waiting time 
		waitingTime = (Head->Burgers * 10) + (Head->Salads * 5);
		
		return waitingTime;
	
	}

//The Purpose of this function is to display every order ahead of a specific order 
void displayOrdersAhead(struct NODE* Front, char *givenName)
{
	
		int result;
		struct NODE* Head = Front;

		int i = 1;
		
		//Traverse List to display orders ahead 
		while(Head != NULL)
		{
			if(DebugMode == TRUE){
			printf("The values traversed on DISPLAYORDERSAHEAD are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	
			
			//Compare Given Name and Node Name 
			result = strcmp(givenName, Head->Name);
			
			//If Names match then Break from Loop 
			if(result == 0)
			{
				break;
			}
			//If The names dont match then output the Order details since it is ahead of the specific order 
			else
			{
				printf("Order %d: ",i);
				printf("%d Burgers, and ",Head->Burgers);
				printf("%d Salads.\n",Head->Salads);
				
				i++;
				Head = Head->Next;
				
			}
		}
		
	}

//The Purpose of this function is to display every order in the list 
void displayListInformation(struct NODE* Front)
{
		struct NODE* Head = Front;
		
	    //Traverse List 
		while(Head != NULL)
		{

			//Output order details
			printf("Order Name \"%s\": ", Head->Name);
			printf("%d Burgers, and ", Head->Burgers);
			printf("%d Salads. ", Head->Salads);
			
			//Output if the status is in or not in
			if(Head->Status == YES)
			{
				printf("Status is IN.\n");
			}
			else
			{
				printf("Status is NOT IN.\n");
			}

			//Move to the next order in list 
			Head = Head->Next;
				
		}
	
	}

//-------------------------------------------------------------------------------------------------------------------------------

//Function is used to determine if the stack is empty 
boolean empty(struct NODE* Head)
{
	
	if(Head == NULL)
	{
	    //Returns TRUE if the stack is empty 
	    return TRUE;
	}
	else
	{
		return FALSE;
	}
	
		
}

//This function is used to clear the List and free all the 
//memory used in each stack node
struct NODE* clear(struct NODE* Head)
{

	//Creates a new Pointer 
	struct NODE* temp;
	char *name;
	
	//Loop while the list is not empty 
	while(!empty(Head)){
		
		if(DebugMode == TRUE){
			printf("The values traversed on CLEAR are: (%s, %d, %d, %d)\n", Head->Name, Head->Burgers, Head->Salads, Head->Status);	
	          }	

	   temp = Head;
	   name = Head->Name;
	   Head = Head->Next;//Move down the List 
	   free(name); 
	   free(temp);//Free memory used by top Node
		
	}
	
	return Head;
	
}



