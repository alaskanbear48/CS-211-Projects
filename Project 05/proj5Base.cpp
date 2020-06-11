/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

#include <cstdio>
#include <cstring>
#include <cctype>

#include "myStack.h"

int DebugMode;

// Enumarated Type specifying all of the Tokens
enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}



// Class to hold the Token information
class Token
{
  private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

  public:

  // Default to initialize to the ERROR TokenType
  Token()
  {
    type = ERROR;
    op = '$';
    val = -999;
  }

  // Initialize to a specific TokenType
  Token (TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a specific TokenType
  void setToType(TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a OPERATOR TokenType with specific operator value
  void setToOperator(char c)
  {
    type = OPERATOR;
    op = c;
    val = -999;
  }

  // Set to a VALUE TokenType with a specific numeric value
  void setToValue(int v)
  {
    type = VALUE;
    op = '$';
    val = v;
  }

  // return true if the Current Token is of the given TokenType
  bool equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool equalsOperator(char c)
  {
    if (type == OPERATOR && op == c)
      return true;
    else
      return false;
  }

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char getOperator ()
  {
    if (type == OPERATOR)
      return op;
    else
      return '$';   // using $ to indicate an error value
  }

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int getValue()
  {
    if (type == VALUE)
      return val;
    else
      return -999;  // using -999 to indicate an error value
  }
};


class TokenReader
{
  private:
     char inputline[300];  // this assumes that all input lines are 300 characters or less in length
     bool needline;
     int pos;


  public:

  // initialize the TokenReader class to read from Standard Input
  TokenReader()
  {
    // set to read from Standard Input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
  }

  // Force the next getNextToken to read in a line of input
  void clearToEoln()
  {
    needline = true;
  }

  // Return the next Token from the input line
  Token getNextToken()
  {
    char* endCheck;

    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

    // get a new line of input from user
    if (needline)
    {
      endCheck = fgets ( inputline, 300, stdin);

      if (endCheck == NULL )
      {
        printf ("Error in reading");
        Token t(EOFILE);
        return t;
      }

      for (int i = 0 ; i < strlen(inputline) ; i++)
          if ('\n' == inputline[i])
              inputline[i] = ' ';
      strcat (inputline , " ");    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }

    // skip over any white space characters in the beginning of the input
    while ( pos < strlen(inputline) && isspace(inputline[pos]) )
    {
      pos++;
    }

    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
      needline = true;
      Token t(EOLN);
      return t;
    }

    // Get the next character from the input line
    char ch = inputline[pos]; pos++;

    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return Token (QUIT);
    }

    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return Token (HELP);
    }

    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
    {
      Token t;
      t.setToOperator( ch );
      return t;
    }

    // check for a number  ==> VALUE Token
    if (isdigit(ch))
    {
      int number = int (ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
      ch = inputline[pos]; pos++;
      while (isdigit(ch))
      {
        number = number * 10 + int (ch) - int('0');
        ch = inputline[pos]; pos++;
      }
      pos--; // since number calcuation check one character after the last digit
      Token t;
      t.setToValue( number );
      return t;
    }

    // Input in not valid if code get to this part ==> ERROR Token
    return Token (ERROR);
  }

};




    /**************************************************************/
    /*                                                            */
    /*  The Code above this point should NOT need to be modified  */
    /*  for this program.   If you feel you must modify the code  */
    /*  below this point, you are probably trying to solve a      */
    /*  more difficult problem that you are being asked to solve  */
    /*                                                            */
    /**************************************************************/

//The Purpose of this function is to compute the inFix Expression
int Eval(int val1, int val2, int op)
{
	//Store the result of Expression
	int v3 = 0;
	
	//Switch statement
	//Checks the ascii value of the operator and performs the expression based on operator
	switch(op)
	{
		//Multiplication Operator
		case 42:
				v3 = val1 * val2;
				break;
		//Addition Operator
		case 43:
				v3 = val1 + val2;
				break;
		//Subtraction Operator
		case 45:
				v3 = val1 - val2;
				break;
		//Division Operator
		case 47:
				v3 = val1 / val2;
				break;
		//If the operator is invalid then return -999
		default:
				cout << "Error Not a recognizable Operator..." << endl;
				return -999;
			
				break;
	}

	//Return Expression answer
	return v3;
	
}

//Function that pops the operator and value stacks to 
//Form an expression to be evaluated 
void popAndEval(myStack& aOperator, myStack& aValues)
{
	//Initialize Values
	int op = 0;
	
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;

	//Pop Operator and pop two values to be used in the expression
	op = aOperator.Pop();
	val2 = aValues.Pop();
	val1= aValues.Pop();
	
	//The answer for the expression will be calculated by Eval() 
	val3 = Eval(val1, val2, op);
	
	//Push the answer for the expression into the values stack for further use 
	aValues.Push(val3);
	
}

//Functions purpose is to split user infix expression into tokens
void processExpression (Token inputToken, TokenReader *tr);

int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */

	DebugMode = false;
    int i;

	for ( i = 0 ; i < argc ; i++ )
	{
		if( strcmp (argv[i], "-d") == 0 )
			{
			
			DebugMode = true;
		    } 
	}	
	
    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}

//Function processes the Infix Expression and stores the appropriate values and operators
//Into a stack. Then tries to resolve the expression. 
void processExpression (Token inputToken, TokenReader *tr)
{
 /**********************************************/
 /* Declare both stack head pointers here      */

	//Stack for operator
	myStack aOperator;
	
	//Stack for Values
	myStack aValues;
	
	//Store char operator in ascii value 
	int mOp;
	
 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
		
		if(DebugMode == true){
       /* make this a debugMode statement */
       printf ("Val: %d, ", inputToken.getValue() );
		}
		
	   //Stores the value into the values stack  
       aValues.Push(inputToken.getValue());

      }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      {
		if(DebugMode == true){
       /* make this a debugMode statement */
       printf ("OP: %c, ", inputToken.getOperator() );
		}
		
		//Check for an open parentheses in the expression
		if(inputToken.getOperator() == '(')
		{
			//Cast operator into an int ascii value
			//Then stores into operator stack 
			mOp = int(inputToken.getOperator());
			aOperator.Push(mOp);
			
		}
		//Checks for input operators of + or - in expression
		else if(inputToken.getOperator() == '+' || inputToken.getOperator() == '-')
		{
			//Checks operator stack for operators +, -, *, and /
			while((!aOperator.isEmpty()) && (aOperator.Top() == 43 || aOperator.Top() == 45 || aOperator.Top() == 42 || aOperator.Top() == 47)) 
			{
				//If true Evaluate the stacks and solve for the expression
				popAndEval(aOperator, aValues);
				
			}
			    //Push current operator into operator stack 
				mOp = int(inputToken.getOperator());
			    aOperator.Push(mOp);
		}
		//Checks for input operators of * or / in expression
		else if(inputToken.getOperator() == '*' || inputToken.getOperator() == '/')
		{
			//Checks operator stack for operators * and /
			while((!aOperator.isEmpty()) && (aOperator.Top() == 42 || aOperator.Top() == 47))
			{
				//If true Evaluate the stacks and solve for the expression
				popAndEval(aOperator, aValues);
				
			}
			    //Push current operator into the operator stack 
				mOp = int(inputToken.getOperator());
			    aOperator.Push(mOp);
		}
		//Checks if the current operator is a closing parentheses
		else if(inputToken.getOperator() == ')') 
		{
			//Loops through popAndEval until the operator stack is empty and the current top 
			//is not an opening parentheses
			while(!aOperator.isEmpty() && aOperator.Top() != 40)
			{
				popAndEval(aOperator, aValues);
			}
			
			//Checks if the operator stack is empty which should not be since we do not pop the opening parentheses
			if(aOperator.isEmpty())
			{
				cout << "ERROR: Operator Stack is Empty..." << endl;
			}
			//Pop Openning parentheses
			else
			{
				//Pop Open Parentheses 
				int openParentheses = aOperator.Pop();
			}
		}
		
      }
	 
    /* get next token from input */
    inputToken = tr->getNextToken ();
   }

 /* The expression has reached its end */

 
//If Operator Stack is not empty then keep evaluating expressions
while(!aOperator.isEmpty())
{
	popAndEval(aOperator, aValues);
}
	//Pop the answer to the final expression from value stack 
	int answer = aValues.Pop();
	
	//Show expression answer
	cout << "Answer is: " << answer << endl;
	
	//Check if value stack is still not empty
	if(!aValues.isEmpty())
	{
		cout << "ERROR: Values stack is not empty..." << endl;
	}
	
 printf ("\n");
}

