#include "Island.h"


//Class Island

//Default Constructor
Island::Island()
{
	Visited = false;
}

//Insert edge into link list 
void Island::insertAdjacent(int value)
{
	Visited = true;
	Neighbors.insert(value);
        
}
	
//Show all edges in link list 
void Island::showAdjacents()
{
	Neighbors.show();
}
	
//Remove an edge from link list 
void Island::removeAdjacent(int value)
{
	Neighbors.Remove(value);
}
	
//Remove every edge from link list 
void Island::removeAllAdj()
{
	Neighbors.RemoveAll();
}
	
//Check if link list is empty
bool Island::isAdjEmpty()
{
	return Neighbors.isEmpty();
}

//Set if island has been visited 
void Island::setVisited(bool v)
{
	Visited = v;		
}

//Check if island has been visited 
bool Island::isVisited()
{
	return Visited;
}

//Find value at a postion in the link list 
int Island::findIsland(int value)
{
	return Neighbors.Search(value);
}

//Find a value in the link list 
int Island::findAdjacent(int value)
{
	return Neighbors.SearchVal(value);
}
		
//Find the lenght of the link list 
int Island::findLength()
{
	return Neighbors.getLength();
}


//Class My List 

//Initializes Head Node as NULL
MyList::MyList()
{
  Head = NULL;
}

//Shows all the values stored in each node 
void MyList::show()
{
	MyNode* curr = Head;
	
	while(curr != NULL)
	{
	   printf("|%d|", curr->getElem());
	   
	   curr = curr->getNext();
	}

	printf("\n");
}

//Insert New Node into List
void MyList::insert(int value)
{
  MyNode* newNode = new MyNode(value);
  MyNode* tmp;
  MyNode* prev;

  //There are no Nodes in list 
  if(Head == NULL)
  {
    newNode->setNext(Head);
    Head = newNode;
  }
  //The New Node is less than or equall the head of the list
  else if(newNode->getElem() < Head->getElem())
  {
      newNode->setNext(Head);
      Head = newNode;
  }
  //This means the New Node is either greater than the head or equall to some node greater than head 
  else
  {
      tmp = Head;
      prev = tmp;
      
      while(tmp != NULL)
      {
	    //Insert New Node into list 
        if(newNode->getElem() < tmp->getElem())
        {
            prev->setNext(newNode);
            newNode->setNext(tmp);
            break;
        }
		//Insert New Node into the end of the link list 
        else if(tmp->getNext() == NULL)
        {
            prev = NULL;
            tmp->setNext(newNode);
            newNode->setNext(prev);
            break;
        }
        else
        {
            prev = tmp;
            tmp = tmp->getNext();
        }
            
      }
      
  }


}

//Removes a node from the link list 
void MyList::Remove(int value)
{
   MyNode* tmp = Head;
   MyNode* prev = Head;
   MyNode* tmp2;
	
   
   while(tmp != NULL)
   {
	  //If true the head of the list is removed
	  if(tmp->getElem() == value && tmp->getElem() == Head->getElem())
	  {
		  //Set Head to next value of the list
		  Head = Head->getNext();
		  delete tmp;
		  
		  return;
		  
	  }
	  //If true and the last Node of the list must be removed
	  else if(tmp->getElem() == value && tmp->getNext() == NULL)
	  {
		  //Delete the last node 
		  delete tmp;
		  
		  //Set the pointer to NULL
		  tmp = NULL;

		  //Set the previous node to the last node and set its next to null 
		  prev->setNext(tmp);
		  
		  return;
		  
	  }
	  //If true the node must be deleted
	  else if(tmp->getElem() == value)
	  {
		  tmp2 = tmp->getNext();
		  prev->setNext(tmp2);
		  
		  delete tmp;
		  
		  return;
	  
	  }
	  else
	  {
	    prev = tmp;
		tmp = tmp->getNext();
	  }
	  
	   
   }
	
	//If it reaches here then the edge could not be found
	printf("Edge could not be found to be deleted.\n");
   
}
	
//Check if Link list is empty
bool MyList::isEmpty()
{
	MyNode* tmp = Head;
	
	if(tmp == NULL)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
	
//Removes all the nodes in the Link List 
void MyList::RemoveAll()
{
	MyNode* tmp = Head;
	MyNode* prev;
	
	Head = NULL;
	
	while(tmp != NULL)
	{
		prev = tmp;
		tmp = tmp->getNext();
		
		delete prev;
		
	}
}

//Searches for a value at a postion in the list 
int MyList::Search(int value)
{
	int counter = 0;
	
	MyNode* cur = Head;
	
	//While it is not the end of the list and the postion(value) has not been met 
	while(cur != NULL && counter != value)
	{
		    counter++;
			cur = cur->getNext();
	}
	
	//Positon has been reached 
	//Check if a value exists and return
	if(counter == value)
	{
		return cur->getElem();
	}
	else
	{
		return -1;
	}
}

//Search for a value on the list 
int MyList::SearchVal(int value)
{
	MyNode* cur = Head;
	
	//While the list does not end 
	while(cur != NULL)
	{
		//If element is found return value 
		if(cur->getElem() == value)
		{
			return cur->getElem();
		}
		else
		{
			cur = cur->getNext();
		}
		
	}
	
	return -1;
	
}

//Get Length of list 
int MyList::getLength()
{
	int counter = 0;
	
	MyNode* cur = Head;
	
	while(cur != NULL)
	{
		counter++;
		cur = cur->getNext();
	}
	
	return counter;
	
}


    //My Node Class 

    //Constructor with initial value (Node connects to nothing) 
	MyNode::MyNode(int value)
	{
		Value = value;
		Next = NULL;
	}
	
	//Constructor with initial value (Node connects to another node)
	MyNode::MyNode(int value, MyNode* cur)
	{
		Value = value;
		Next = cur;
	}

	//Assign New value to the current Node
	void MyNode::setElem(int value)
	{
	  Value = value;
	}

	//Get the element of the current Node
	int MyNode::getElem()
	{
	  return Value;
	}

	//Connect the Link
	void MyNode::setNext(MyNode* cur)
	{
	  Next = cur;
	}

	//Go to the next node in the link list (Change current node)
	MyNode* MyNode::getNext()
	{
	  return Next;
	}


	//String Classes 

    //Constructor with initial value (Node connects to nothing) 
	MyStringNode::MyStringNode(char* value)
	{
		strncpy(Value, value, sizeof(Value));
		
		Next = NULL;
	}
	
	//Constructor with initial value (Node connects to another node)
	MyStringNode::MyStringNode(char* value, MyStringNode* cur)
	{
		
		strncpy(Value, value, sizeof(Value));
		Next = cur;
	
	}

	//Assign New value to the current Node
	void MyStringNode::setElem(char* value)
	{
	  strncpy(Value, value, sizeof(Value));
	}

	//Get the element of the current Node
	char* MyStringNode::getElem()
	{
	  return Value;
	}

	//Connect the Link
	void MyStringNode::setNext(MyStringNode* cur)
	{
	  Next = cur;
	}

	//Go to the next node in the link list (Change current node)
	MyStringNode* MyStringNode::getNext()
	{
	  return Next;
	}



//Initializes Head Node as NULL
MyStringList::MyStringList()
{
  Head = NULL;
}

//Shows all the values stored in each node 
void MyStringList::show()
{
	MyStringNode* curr = Head;
	
	while(curr != NULL)
	{
	   printf("Island: %s\n", curr->getElem());
	   
	   curr = curr->getNext();
	}

}

//Insert New Node into List
void MyStringList::insert(char* value)
{
  MyStringNode* newNode = new MyStringNode(value);
  MyStringNode* tmp;
  MyStringNode* prev;

  //There are no Nodes in list 
  if(Head == NULL)
  {
    newNode->setNext(Head);
    Head = newNode;
  }
  //The New Node is less than or equall the head of the list
  else if(newNode->getElem() < Head->getElem())
  {
      newNode->setNext(Head);
      Head = newNode;
  }
  //This means the New Node is either greater than the head or equall to some node greater than head 
  else
  {
      tmp = Head;
      prev = tmp;
      
      while(tmp != NULL)
      {
		//Inserts new node into list 
        if(newNode->getElem() < tmp->getElem())
        {
            prev->setNext(newNode);
            newNode->setNext(tmp);
            break;
        }
		//Inserts new node into the end of the list 
        else if(tmp->getNext() == NULL)
        {
            prev = NULL;
            tmp->setNext(newNode);
            newNode->setNext(prev);
            break;
        }
        else
        {
            prev = tmp;
            tmp = tmp->getNext();
        }
            
      }
      
  }


}

//Removes a node from the link list 
void MyStringList::Remove(char* value)
{
   MyStringNode* tmp = Head;
   MyStringNode* prev = Head;
   MyStringNode* tmp2;
	
   
   while(tmp != NULL)
   {
	  //If true the head of the list is removed
	  if(tmp->getElem() == value && tmp->getElem() == Head->getElem())
	  {
		  //Set Head to next value of the list
		  Head = Head->getNext();
		  delete tmp;
		  
		  return;
		  
	  }
	  //If true and the last Node of the list must be removed
	  else if(tmp->getElem() == value && tmp->getNext() == NULL)
	  {
		  //Delete the last node 
		  delete tmp;
		  
		  //Set the pointer to NULL
		  tmp = NULL;

		  //Set the previous node to the last node and set its next to null 
		  prev->setNext(tmp);
		  
		  return;
		  
	  }
	  //If true the node must be deleted
	  else if(tmp->getElem() == value)
	  {
		  tmp2 = tmp->getNext();
		  prev->setNext(tmp2);
		  
		  delete tmp;
		  
		  return;
	  
	  }
	  else
	  {
	    prev = tmp;
		tmp = tmp->getNext();
	  }
	  
	   
   }
	
	//If it reaches here then the edge could not be found
	printf("Node could not be found to be deleted.\n");
   
}
	
//Check if Link list is empty
bool MyStringList::isEmpty()
{
	MyStringNode* tmp = Head;
	
	if(tmp == NULL)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
	
//Removes all the nodes in the Link List 
void MyStringList::RemoveAll()
{
	MyStringNode* tmp = Head;
	MyStringNode* prev;
	
	Head = NULL;
	
	while(tmp != NULL)
	{
		prev = tmp;
		tmp = tmp->getNext();
		
		delete prev;
		
	}
	
}

//Search for value at a postion
bool MyStringList::Search(char* value)
{
	
	MyStringNode* cur = Head;
	int res;
	
	while(cur != NULL)
	{
		res = strcmp(cur->getElem(), value);
		
		if(res == 0)
		{
			return true;
		}
		else
		{
			cur = cur->getNext();
		}
	}
	 
		return false;
}

//Get length of list 
int MyStringList::getLength()
{
	int counter = 0;
	
	MyStringNode* cur = Head;
	
	while(cur != NULL)
	{
		counter++;
		cur = cur->getNext();
	}
	
	return counter;
	
}


