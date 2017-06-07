/* "Include guard" - prevents this file from getting included more
   than once. */
#ifndef RACE_H
#define	RACE_H

// Maximum number of steps in race
const int MaxPos = 48;
// Minimum number of steps in race
const int MinPos = 0;

/*
	The function that simulates the race. The clock is modeled as a loop 
	and in each iteration, we add one units to the clock. The loop breaks 
	until we have a winner and the race ends.
	
	Parameters: none
	Return: none
*/
void schedule(); 

/*
	Return the new position of Tortoise on the basis of rule given in 
	assignment document for Tortoise. 
	
	Parameters: 
	currentPosition = current position of Tortoise
	Return: new position of Tortoise
*/
int returnTortoisePosition( int currentPosition );


/*
	Return the new position of Hare on the basis of rule given in 
	assignment document for Hare. 
	
	Parameters: 
	currentPosition = current position of Hare
	
	Return: new position of Hare
*/
int returnHarePosition( int currentPosition );

/*
	Identify and print winner by comparing position of Tortoise and Hare 
	with maximum position
	
	Parameters:
	tortoisePos = current position of Tortoise
	harePos = current position of Hare
*/

void announceWinner(int tortoisePos, int harePos);

/*
	Print single line to display the current position of Trotise and Hare.
	Use letter 'T' for Trotoise and 'H' for Hare.
	Letter 'F' represents finish line.
	
	Here i represents current clock value of simulation. 
	A distance is represeny by a space or H/T.
	
	Time: i T     H                       F	
	
	Parameters:
	currentTick:	Current clock value of simulation
	tortoisePos:	Current position of Torotise
	harePos:		Current position of Hare
	
*/
void displayCurrentPositions(int currentTick, int tortoisePos, int harePos);

/*
	To return a unfiorm random number ranges between 0 and 1
*/
inline double returnUniformRandomNumber();

/*
	Add delay in execution in order to have slow-motion race. 
	
	Parameters: none
	Return: none
*/
inline void delay();

#endif	
