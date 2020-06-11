#include "sc.h"

//Function for command 'a'
struct NODE* doAdd(struct NODE* Head)//Source 2
{
 /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

     //Code to perform this operation here    
	
	 //Customers are in the Restuarant
	 boolean status = YES;
	
   //Check if Name already Exists in List
   if(!doesNameExist(Head, name)){
	
	printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);	
	//Insert Node to queue with order information 
	Head = addToList(Head, name, NumBurgers, NumSalads, status);
		
	}
	else{
		
		//Free malloc memory 
		free(name);
		printf("Error, Name Already Exists. \n");
	}
		
	return Head;		
}

//Function for command 'c'
struct NODE* doCallAhead(struct NODE* Head)//Source 2
{
 /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  


 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

     //Code to perform operation here
 
	 //Customers made a Call-ahead order (Not in Restuarant)
	 boolean status = NO;
	
	//If the name is not found then add to Queue
	if(!doesNameExist(Head, name)){
	
	printf ("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);	
	//Insert Node to queue with order Information 
	Head = addToList(Head, name, NumBurgers, NumSalads, status);
		
	}
	else{
		
		//Free memory allocated by Malloc
		free(name);
		printf("Error, Name Already Exists. \n");
	}
	
	return Head;
	
}

//Function for command 'w'
struct NODE* doWaiting(struct NODE* Head)//Source 2
{
	
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }

    //Code to perform this operation
            
	boolean status;
	
	//If Head is not NULL and Name is found in order list. Then we can check order status. 
	if(Head != NULL && doesNameExist(Head, name) == TRUE)
	{
		//Checks and stores order status 
		status = updateStatus(Head, name);
		
		//If False then Group is already in Restuarant
		if(status == FALSE)
		{
			printf("Error, Group Not Call Ahead. Already in Restuarant.\n");
		}
		
		//If True then Group made a Call-ahead but is now In the Restuarant
		//Change Status of Group order 
		if(status == TRUE)
		{
			printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);
			
			Head = changeStatus(Head, name);
			
			//Free Malloc Allocation
			free(name);
			return Head;
		}
	}
	else
	{
		printf("Error, Name Does Not Exist.\n");
	}
	
	//Free Malloc Allocation
	free(name);
	return Head;
	
}

//Function for command 'r'
struct NODE* doRetrieve (struct NODE* Head)//Source 2
{
	
 /* get info of prepared food ready on the counter from input */
 int PreparedBurgers = getPosInt();
 if (PreparedBurgers < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }

 int PreparedSalads = getPosInt();
 if (PreparedSalads < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }   

 clearToEoln();

    //Code to perform this operation
    
    //Order List is empty 
	if(Head == NULL)
	{
		printf("Error. There are no orders. Please make and order.\n");
		return Head;
	}
	
	//Checks if the order asked for is in restaurant or is found in order list 
	boolean vNumbers = checkForValidNumbers(Head, PreparedSalads, PreparedBurgers);
	
	//True if the order asked for is in restaurant and is found in order list
	if(vNumbers)
	{
		printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers ,PreparedSalads);
		
		//Retrives the Name of the group that will have their order delivered
		char *vName = retriveName(Head, PreparedSalads, PreparedBurgers);
		
        printf("\"%s\" order has been delivered.\n", vName);
		
		//Remove group order from List since they have picked up their order
		Head = retriveAndRemove(Head, PreparedSalads, PreparedBurgers);
		
	    return Head;
		
	}
	else
	{
		printf("There are no orders matching the amount of Burgers and Salads that are in the Restuarant.\n");
	
	}
	
	return Head;
	
}

//Function for command 'l'
void doList (struct NODE* Head)//Source 2
{
	
	
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }
	
	//Code to perform this operation

	//Check if Head is not NULL and if Name exists in order list 
	if(Head != NULL && doesNameExist(Head, name) == TRUE)
	{
	
	 //Check how many orders are ahead of given group
	 int behind = countOrdersAhead(Head, name);	

		 //If there are no orders ahead of the group (single node)
		 if(behind == 0)
		 {
		   printf("Order for \"%s\" is Not behind any order.\n", name);
		 }
		else
		{
			
		 //Displays the number or orders that are ahead of the given group
		 printf("Order for \"%s\" is %d orders behind the following\n", name, behind);
			
		 //Displays the spefic orders that are ahead of the given group
		 displayOrdersAhead(Head, name);
		}		
	}
	else
	{
		printf("Error, Name Does Not Exist. \n");
	}
	
	//Free Malloc Allocation
	free(name);
}
 
//Function for command 'd'
void doDisplay (struct NODE* Head)//Source 2
{
	
 clearToEoln();

 //Code to perform this operation
 
 //Check first if there is a list to display (not empty)
 if(Head != NULL)
 {
	printf ("Display information about all orders\n");
	 
	//Display contents of every order in list 
	displayListInformation(Head);
 }
 else
 {
    printf("Error. There are no orders. Please make and order.\n");
 }
	
}

//Function for command 't'
void doEstimateTime(struct NODE* Head)//Source 2
{
	
  /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: t <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }

     //Code to perform this operation  
  
	//Check if List is not empty and if group name exists in List 
	if(Head != NULL && doesNameExist(Head, name) == TRUE)
	{
	
	 //Calculate and Store the total time for order completion
	 int minutes = displayWaitingTime(Head, name);	
	 printf("Estimated wait time for for \"%s\" is %d minutes\n", name, minutes);
		
	}
	else
	{
		printf("Error, Name Does Not Exist. \n");
	}
	
	//Free Malloc Allocation
	free(name);
}






