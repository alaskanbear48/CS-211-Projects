//The purpose of this program was to create an adjacency list using classes. Structs were not used 
//in order to keep the program class focused. The program has 5 classes. However MyStringNode and MyStringList
//are both used for reading text files and preventing infinite loops. Thus they work similar to MyNode and MyList.
//First the Island class creates an adjacency list for a specific island. It uses both the MyList and MyNode class.
//MyList manipulates the adjacency list using the MyNode class. Since structs are not used the MyNode class is used instead
//to connect nodes and set elements. All together the program creates adjacency lists for every island an a sole link list 
//that stores text file names.

//CS 211 Program 6 UIC <Manuel M Martinez> <mmart233>

#include <cstdio>
#include <cstring>
#include <cstdlib>


//Node Class to create Nodes in a list 
class MyNode
{
	private:
		int Value;
		MyNode* Next;

	public:

	//Constructor with initial value (Node connects to nothing) 
	MyNode(int value);
	
	//Constructor with initial value (Node connects to another node)
	MyNode(int value, MyNode* cur);

	//Assign New value to the current Node
	void setElem(int value);
	
	//Get the element of the current Node
	int getElem();
	
	//Connect the Link
	void setNext(MyNode* cur);

	//Go to the next node in the link list (Change current node)
	MyNode* getNext();

};

//Node Class to create Nodes in a char List 
class MyStringNode
{
	private:
		char Value[50];
		MyStringNode* Next;

	public:


	//Constructor with initial value (Node connects to nothing) 
	MyStringNode(char* value);
	
	//Constructor with initial value (Node connects to another node)
	MyStringNode(char* value, MyStringNode* cur);

	//Assign New value to the current Node
	void setElem(char* value);
	
	//Get the element of the current Node
	char* getElem();
	
	//Connect the Link
	void setNext(MyStringNode* cur);

	//Go to the next node in the link list (Change current node)
	MyStringNode* getNext();

};

//Class for creating a link list 
class MyList
{
	private:
		MyNode* Head;
	
	public:

//Initializes Head Node as NULL
MyList();

//Shows all the values stored in each node 
void show();

//Insert New Node into List
void insert(int value);

//Removes a node from the link list 
void Remove(int value);

//Check if Link list is empty
bool isEmpty();

//Removes all the nodes in the Link List 
void RemoveAll();
	
//Searches for a value at a positon on the list 	
int Search(int value);

//Searches for a value on the list 
int SearchVal(int value);

//Returns the lenght of the list 
int getLength();

//Insert a New Node to the front of the list 
void insertFront(int value);

//Insert a New Node to the back of the list 
void insertBack(int value);
	
//Pop Node at front of the list 
int popFront();

};

//Class for creating a char link list 
class MyStringList
{
	private:
		MyStringNode* Head;
	
	public:

//Initializes Head Node as NULL
MyStringList();

//Shows all the values stored in each node 
void show();

//Insert New Node into List
void insert(char* value);

//Removes a node from the link list 
void Remove(char* value);

//Check if Link list is empty
bool isEmpty();

//Removes all the nodes in the Link List 
void RemoveAll();

//Searches for a value
bool Search(char* value);

//Returns the lenght of the list 
int getLength();

};

//Class to create a link list stack. Parent Class is MyList 
//Inheritence is used to build stack 
class MyStack:public MyList 
{

	public:
	
		//Default Constructor
		MyStack();
		
		//Destructor
		~MyStack();
	
		//Insert Node at the Front of the List 
		void insertSK(int value);
	
		//Pop Node at the Front of the List 
		int popSK();

		//Check if Stack is empty
		bool emptySK();
		
		//Display all the contents of the Stack 
		void showSK();

};

//Class to create a link list queue. Parent Class is MyList 
//Inheritence is used to build queue 
class MyQueue:public MyList
{

	public:
	
		 //Default constructor
		 MyQueue();
		
		//Destructor 
		~MyQueue();
	
		//Inserts Node at the end of the list 
		void insertQ(int value);
	
		//Pop Node at the front of the Link list 
		int popQ();

	    //Check if the Queue is empty 
		bool emptyQ();

};

//Class to create a link list of edges to a specific island
class Island
{
	private:
		
		//Create link list 
		MyList Neighbors;
		bool Visited;
		int PreV;

	public: 
	
	//Default constructor
	Island();
	
	//Insert edge into link list
	void insertAdjacent(int value);
	
	//Show all edges in link list
	void showAdjacents();
	
	//Remove an edge from link list
	void removeAdjacent(int value);
	
	//Remove every edge from link list
	void removeAllAdj();
	
	//Check if link list is empty
	bool isAdjEmpty();
	
	//Set if island has been visited
	void setVisited(bool v);
	
	//Check if island has been visited 
	bool isVisited();
	
	//Find value at a position in the link list
	int findIsland(int value);
	
	//Find a value in the link list 
	int findAdjacent(int value);
	
	//Find the lenght of the link list
	int findLength();
	
	//Set the Previous Island 
	void setPreV(int value);
	
	//Get the previous Island 
	int getPreV();	
};


