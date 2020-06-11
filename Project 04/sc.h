//The purpose of this Program was to Use a Linked List type queue to store orders for a fast food restuarant. We are able to know the 
//Waiting time of each order. What type of order (In-Restuarant or Call Ahead), and we are able to change it as well. In addition the 
//program will be able to remove orders once they are picked up. The order that has been waiting the longest will be picked up first. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

int DebugMode;

//Creates our Node Struct to be used for a Link List 
struct NODE{
	
	char *Name; 
	int Burgers;
	int Salads;
	
	boolean Status;//Use Yes or No
	//Yes for in restuarant
	//No for not being in restuarant 
	
	struct NODE* Next; 
};

//Source 1 
int getNextNWSChar();
int getPosInt()	;
char *getName();
void clearToEoln();
void printCommands();
int main (int argc, char **argv);

//Source 2
struct NODE* doAdd(struct NODE* Head);
struct NODE* doCallAhead(struct NODE* Head);
struct NODE* doWaiting(struct NODE* Head);
struct NODE* doRetrieve (struct NODE* Head);
void doList (struct NODE* Head);
void doDisplay (struct NODE* Head);
void doEstimateTime(struct NODE* Head);


//Source 3
void createQueue(struct NODE* Head);
struct NODE* addToList(struct NODE* Head, char *orderName, int numBurgers, int numSalads, boolean orderStatus);
boolean doesNameExist(struct NODE* Front, char *givenName);
boolean updateStatus(struct NODE* Front, char *givenName);
struct NODE* retriveAndRemove(struct NODE* Front, int numSalads, int numBurgers);
int countOrdersAhead(struct NODE* Front, char *givenName);
int displayWaitingTime(struct NODE* Front, char *givenName);
void displayOrdersAhead(struct NODE* Front, char *givenName);
void displayListInformation(struct NODE* Front);
boolean empty(struct NODE* Head);
struct NODE* clear(struct NODE* Head);

boolean checkForValidNumbers(struct NODE* Front, int numSalads, int numBurgers);
char *retriveName(struct NODE* Front, int numSalads, int numBurgers);
struct NODE* changeStatus(struct NODE* Head, char *givenName);





