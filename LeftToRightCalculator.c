/*
Author: 		My Tran

StudentID:		001550700

Course:			ICSI 333 System Fundamentals

Semester:		Spring 2022

TA:				Sourav Dutta

Filename:		LeftToRightCalculator.c

Description:	Program gets an arithmetic expression from the user and
				evaluates the expression in a left to right fashion. Then
				the user is asked for a radix to determine the number base
				to convert the number to and outputs the answer to the
				expression in that number base.
				
Assumptions:	-The expression consists only of integers, operators, and whitespace
				-integers can be multi decimal digits
				-There may be no space or more than one space between characters
				-The expression begins with an integer number
				-The expression alternates between numbers and operators
				-Each expression is terminated by a new line
				-The expression is no more than 80 symbols
				-The result from the expression will be given as type signed int
				-Radix will be one of 2,3,4,..., 15, 16
				-Conversion of negative integers will be displayed as -"representation"
				-No error checks are needed
*/
#include<stdio.h>	//standard input/output 
#include<string.h>	//string library included for string related functions. Mainly strlen

//DEFINED CONSTANTS
#define MAX_EXPR 80		//MAX_EXPR gives the max length of an expression
#define MAX_DIGIT 32	//MAX_DIGIT gives the max amount of digits needed to represent an int in binary
#define BASE_10 10		//BASE_10 gives the base 10 as a value;


//PROTOTYPES



//TASK1:
//prototype for function Evaluate
int Evaluate();
//prototype for ReadExpression
void ReadExpression(char *);
//prototype for GetInt
int GetInt(char *);




//TASK2:
//prototype for ConvertToBase
void ConvertToBase(int);
//prototype for GetDigit
char GetDigit(int);
//prototype for ReadExpression
void ReverseString(char *);



int main()
{	//format output to screen and call functions of the program
	printf("%%\tproject1\n");
	
	//Task #1:
	//call to Evaluate and result is returned to answer
	int answer = Evaluate();
	
	
	//Pass control to Task #2
	//call to ConvertToBase given answer from expression
	ConvertToBase(answer);
	
	printf("%%\n");
	
	
	return 0;
}//end main



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//TASK1:


/*
Function:		Evaluate()

Purpose:		Function evaluates arithmetic expression given by user in a
				left to right fashion, outputs result, and returns result to caller.
				
Pre-condition:	None.

Post-condition:	Result of expression is displayed and returned to caller.
*/
int Evaluate()
{
	//declare char array to store expression string
	//temp pointer is used to  iterate through the string
	char expression[MAX_EXPR], *temp;
	
	//result stores the integer value of given by the evaluation of the
	//given arithmetic expression
	int result = 0;		//initiallized to 0
	
	//call ReadExpression to obtain expression as a string in expression
	ReadExpression(expression);
	
	
	//temp points to expression array
	temp = expression;
	
	//initiallize result with first number in the expression
	//call to GetInt function
	result = GetInt(temp);
	
	
	//continue until terminating value is encountered in string
	while(temp[0] != '\0')
	{
		//ignore digits and whitespace in expression
		//pointer is being moved to increment so current position is always at index 0
		if(temp[0] >= '0' && temp[0] <= '9' || temp[0] == ' ')
		{
			//move pointer to next position
			temp = &temp[1];
		}
		//if not digit or whitespace, then it must be an operator
		else
		{
			//determine which operator has been encountered
			switch(temp[0])
			{
				
				//increment pointer to next position, and perform the specified operation
				//on the left hand running total and next number (gotten by GetInt function)
				case '+':
					temp = &temp[1];
					result += GetInt(temp);	//increment result by next integer value
					break;
				case '-':
					temp = &temp[1];
					result -= GetInt(temp);	//decrement result by next integer value
					break;
				case '*':
					temp = &temp[1];
					result *= GetInt(temp);	//multiply result by next integer value
					break;
				case '/':
					temp = &temp[1];
					result /= GetInt(temp);	//divide result by next integer value
					break;
				default:
					break;
							
			}//end of switch
		
		}
	}//end of while
	
	//print answer
	printf("Value = %d\n", result);
	fflush(stdout);
	
	
	//return the output of the given expression to caller
	return result;
}//end Evaluate



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


/*
Function:		ReadExpression()

Purpose:		Function reads an expression from the user into a string.

Pre-condition:	A pointer to a string to contain the expression is passed to function.

Post-condition:	The expression is stored in the memory address given by the pointer parameter
*/
void ReadExpression(char *expression)
{
	//prompt user to enter an arithmetic expression
	printf("Enter expression: ");
	fflush(stdout);
	
	//counter variable to iterate through expression string
	int index = 0;
	
	//variable to temporarily hold characters from user
	char temp;
	
	//priming read for loop
	scanf("%c", &temp);
	
	//loop continues until user hits enter key/new line
	while(temp != '\n')
	{
		//temp is stored in current location
		expression[index] = temp;
		
		//read next value and increment counter variable
		scanf("%c", &temp);
		index++;
	}
	
	//set terminating zero character at the end of the string
	expression[index] = '\0';
	
}//end ReadExpression


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



/*
Function:		GetInt()

Purpose:		Function reads string character by character, converting the first occurring
				integer in the string to it's decimal equivalent.
				
Pre-condition:	Pointer to an array containing an integer at the start is passed in

Post-condition:	An int value representing the decimal equivalent of the first value in 
				the string is returned. 
*/
int GetInt(char *num)
{
	//result will store the an integer term from the string
	int result=0, index = 0;
	
	//loop continues until a space is encountered in string
	//to ignore whitespace up to character representing a digit in integer
	while(num[index] == ' ')
	{
		//increment to the next position
		index++;
	}
	
	//perform loop while characters represent integer digits
	//builds integer from characters by starting with the highest place value,
	//multiplying current sum by the base, adding the next value, and repeating
	while(num[index] >= '0' && num[index] <= '9')
	{
		
		//being read in left to right, multiply by number base and add digit to the right
		result *= BASE_10;
		result += (num[index] - '0');
		//move onto next character
		index++;
	}
	
	//returns the calculated value
	return result;
}//end GetInt



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//TASK2:



/*
Function:		ConvertToBase()

Purpose:		Function obtains desired radix from user, converts given integer to corresponding
				number base, and outputs result.
				
Pre-condition:	Value to be converted is taken as argument.

Post-condition:	Desired representation of value is output.
*/
void ConvertToBase(int value)
{
	//char array output is the converted value given as a string
	char output[MAX_DIGIT];
	
	//Radix stores the value given by user, and tempVal
	//is used to work with value without modifying value
	int radix, tempVal;
	
	//prompt for a radix from user
	printf("Enter radix: ");
	fflush(stdout);
	
	//read in radix
	scanf("%d", &radix);
	
	
	int count = 0;
	
	//assign value to tempVal
	tempVal = value;
	
	//if value is zero, output character '0'
	if(tempVal == 0)
	{
		output[0] = '0';
		count++;
	}
	else
	{	
		//if tempVal is negative, flip to positive for the correct
		//representation and add a negative sign to beginning of string
		if(tempVal < 0)
		{
			//negate tempVal
			tempVal *= -1;
			//first position gets '-' sign
			output[0] = '-';
			//increment to the next position in string
			count++;
		}
		//loop continues while tempVal has not been reduced to 0
		while(tempVal != 0)
		{
			//output gets corresponding digit from the modulus by radix
			output[count] = GetDigit(tempVal%radix);
			
			//tempVal divided by radix for the next pass
			tempVal /= radix;
			
			count++;
		}
	}
	
	//add terminating character to string
	output[count] = '\0';
	
	//Reverse the string to get right to left reading order on string
	//skip first value in reverse if negative to account for sign
	if(value < 0)
	{
		ReverseString(&output[1]);
	}
	else
	{
		ReverseString(output);
	}
	
	printf("Answer = %s\n", output);
	fflush(stdout);
}//end ConvertToBase





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




/*
Function:		GetDigit()

Purpose:		Converts given digit into char where if 0-9, char equivalents are returned.
				otherwise, alphabetical equivalents are found and returned.
				
Pre-condition	Number to be converted is passed in as argument.

Post-condition:	A char equivalent of num is returned to caller.
*/
char GetDigit(int num)
{
	//find character equivalent of digit between 0 and 9
	if(num >= 0 && num <= 9)
		//adds number to char value of '0' to get corresponding char
		// 0 returns '0', 1 returns '1',...
		return (char)(num + '0');
	
	//find character equivalent of integers beyond a single digit
	else
		//returns corresponding letter to number >=10
		//where A=10, B=11,...
		return (char)(num + 'A' -10);
	
}//end GetDigit





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





/*
Function:		ReverseString()

Purpose:		Reverse the order of values in a string

Pre-condition:	Pointer to a character array is passed in as argument

Post-condition:	Order of values in string is reversed in string
*/
void ReverseString(char *ptr)
{
	//starting at the first character stored at ptr's mem location,
	//swap characters in the beginning of the array, with the end of
	//the array, until they meet in the middle
	for(int index = 0; index < strlen(ptr)/2; index++)
	{
		//temp holds a value to aid in swap;
		char temp;
		
		//temp holds the value from the first half
		temp = ptr[index];
		
		//current position in the first half now stores the corresponding
		//value from the second half
		ptr[index] = ptr[strlen(ptr) - index -1];
		
		//position in the second half gets that of the first
		ptr[strlen(ptr) - index -1] = temp;
	}
	
}//end ReverseString