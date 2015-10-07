/* ----------------------------------------------------------------------------- 
 * 1024 And More! 
 *
 * Class: CS 141, Spring 2014.  Wed 3pm lab.
 * System: Mac OS X 10.6.8 on TextWrangler
 * Author: Filip Radzikowski
 *
 * ToDo: All Done
 * -----------------------------------------------------------------------------
   This program creates a game where the player attempts to add up numbers to
   get a certain value. The numbers are randomly generated on the screen with 
   only a 2 or a 4 appearing on the board initially. With each move a new 
   number is randomly generated to the board. Below is a print out of the 
   initial screen that better explains the directions: 
   
   
   This Program is based off of Gabriele Cirulli's game online at
   bit.ly/great2048

   For each move enter a direction as a letter key, as follows:
      W
    A S D
   where A=left, W=up, D=right and S=down.

   After a move, when two identical valued tiles come together they
   join to become a new single tile with the value of the sum of the
   two originals. This value gets added to the score. On each move
   one new randomly choses value of 2 and 4 is placed in a random open
   square. User input of r restarts the game, and x exits the game.

   Game ends when you reach 2048.

   Score:  4
    . . . . .
    . . . . 4
    . . . . .
    . . 4 . .
    . . . . .

   1. Your move:  a
   
   Score:  4
    . . . . .
    4 . . . .
    . . . . .
    4 . . . .
    4 . . . .

   2. Your move:  

 */

//-- Header Files ---
#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;


//--- Function Declarations ---
void printHeaderInstructions();
void setBoardArray(int*, int);
void setBoardSize(int&, int&);
void printBoard(int*, int, int);

void userMove(int*, int, int, char, int&);
	void slideSumLeft(int*, int, int, int&);
	void slideSumRight(int*, int, int, int&);
	void slideSumUp(int*, int, int, int&);
	void slideSumDown(int*, int, int, int&);

void userInput(char&);
int checkUserInput(int*, int, char, int&);
	void manuallySetBoardArray(int*, int&);

void setRandomLocation(int*, int);
	int getRandomValue();

int checkPossibleMoves(int*, int, int);
	int checkForOpenIndex(int*, int);
	int validSurroundingIndex(int*,int, int);

int checkWinner(int*, int, int);
	int getScore(int*, int);
	int setWinningScore(int);




//----------------------------- Main Function ----------------------------------

int main()
{
	// Clear Screen before printing new board
	system("clear");
	printHeaderInstructions();
	
	int boardWidth = 0;
	int boardSize = 0;
	int winner = 0;
	char input = ' ';
	int checkMove = 1;
	
	// Gets user input size (4-12) and total elements in boards
	setBoardSize(boardWidth, boardSize);
	int board[boardSize];
	
	// Set array elements to 0 for length boardSize
	setBoardArray(board, boardSize);
	
	// Set initial random number on board
	setRandomLocation(board, boardSize);
	

	do{
		system("clear");
		printHeaderInstructions();
		
		// Checks for open tiles and equivalent surrounding tiles.
		//		neither are found then returns 0 , ending the game.	
		if(checkPossibleMoves(board, boardWidth, boardSize) == 1){
			
			// Checks if slide or summation was made. If so random value added.
			//		checkMove is modified within slideSum functions.
			if(checkMove == 1){
				// Find random open space on board and set random value(2 or 4)
				setRandomLocation(board, boardSize);
			}
			
			printBoard(board, boardWidth, boardSize);
			
			// Prompts user for direction of slide.
			userInput(input);
			// Checks if user wants to quit, restart, or add value to board.
			if(checkUserInput(board, boardSize, input, checkMove) == 0)break;
			
			// Receives userInput slide direction and implements them.	
			userMove(board, boardWidth, boardSize, input, checkMove);
			// If current score equals winning score then winner.
			winner = checkWinner(board, boardWidth, boardSize);	
		}
		else {
			printBoard(board, boardWidth, boardSize);
			cout<< "\nGame Over!! You ran out of moves!!\n";
			break;
		}
		
	}while(winner == 0); // loops until user reaches winning score
										

}// End main 

//------------------------ Sub-Function Definitions ----------------------------


/* --- userMove Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth 
 *              3. int boardSize
 *              4. int &checkMove
 *
 * Description: This function takes userInput to establish the direction
 *              the user wishes to slide in. Using switch case it then calls
 *              on the respective slide function.
 */
void userMove(int board[], int boardWidth, int boardSize, char move, int &checkMove)
{
	
	switch(move){
				case 'A': 
					slideSumLeft(board, boardWidth, boardSize, checkMove);
					return;
				
				case 'D':
					slideSumRight(board, boardWidth, boardSize, checkMove);
					return;
				
				case 'W':
					slideSumUp(board, boardWidth, boardSize, checkMove);
					return;
				
				case 'S':
					slideSumDown(board, boardWidth, boardSize, checkMove);
					return;			
	}
	return;
}// End userMove


/* --- slideSumDown Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth 
 *              3. int boardSize
 *              4. int &checkMove
 *
 * Description: This function loops through the board array and finds all 
 *              elements that are greater than 0 (which are printed out as
 *              the '.' character. Using a while loop with the conditions that
 *              element > 0, the element below the current element is 0, and 
 *              the current index does not fall beyond the end of the array,
 *					 each element > 0 slides to the bottom of the board. Next if 
 *              the current index value and value below the current index value
 *              are the same then they are added and stored in index value
 *              below the current index.  
 */
void slideSumDown(int board[], int boardWidth, int boardSize, int &checkMove)
{
 	checkMove = 0; // If no moves are made then remains 0.
 	
 	// Iterates through board index's from end of array to beginning.
 	for(int i=boardSize-1; i >= 0; i--){
		if(i % boardWidth < boardWidth){ // Keeps to single row on board
			
			int j = i;
			// Loop continues while value at index and below index are not 0.
			while(board[j]>0 && board[j+boardWidth] == 0 &&
					j <= ((j/boardWidth)*boardWidth + boardWidth-1)){ // Keeps loop 
																					  // within array
				board[j+boardWidth] = board[j];
				board[j] = 0;
				j+=boardWidth;
				checkMove = 1; // move has been made
			
			}//end while loop
			
			// Skip index's for last row when summing
			if(j/boardWidth == boardWidth-1) continue;
			
			// Sum equal values with down slide from bottom most row
			if(board[j] != 0 && board[j] == board[j+boardWidth]){
				board[j+boardWidth] = board[j]*2;
				board[j] = 0;
				checkMove = 1; // when summation has been made
			}
		}// end conditional
 	}// end for loop
 	
 	return;
 }// End slideSumDown 
 
 
/* --- slideSumUp Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth 
 *              3. int boardSize
 *              4. int &checkMove
 *
 * Description: This function loops through the board array and finds all 
 *              elements that are greater than 0 (which are printed out as
 *              the '.' character. Using a while loop with the conditions that
 *              element > 0, the element above the current element is 0, and 
 *              the current index does not fall beyond the top end of the array,
 *					 each element > 0 slides to the top of the board. Next if 
 *              the current index value and value above the current index value
 *              are the same then they are added and stored in index value
 *              above the current index.     
 */
void slideSumUp(int board[], int boardWidth, int boardSize, int &checkMove)
{
	
	checkMove = 0; // If no moves are made then remains 0.
	
	// Iterates through board index's from beginning of array to end.
	for(int i=0; i<boardSize; i++){
		if(i % boardWidth < boardWidth){ // Keeps to single row on board
		
			int j = i;
			// Loop continues while value at index and above index are not 0.
			while(board[j]>0 && board[j-boardWidth] == 0 &&
					j >= ((j/boardWidth)*boardWidth)){ // Keeps loop within array
				
				board[j-boardWidth] = board[j];
				board[j] = 0;
				j-=boardWidth;
				checkMove = 1; // move has been made
			
			}// end while loop
			
			// Skip indexs for first row when summing 
			if(j/boardWidth == 0)continue; 
			
			// Sum equal values with upward slide from top most row
			if(board[j] != 0 && board[j] == board[j-boardWidth]){
				board[j-boardWidth] = board[j]*2;
				board[j] = 0;
				checkMove = 1; // when summation is made
			}	
		} // end conditional
	}// end for loop 

	return;
}// End slideSumUp


/* --- slideSumRight Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth 
 *              3. int boardSize
 *              4. int &checkMove
 *
 * Description: This function loops through the board array and finds all 
 *              elements that are greater than 0 (which are printed out as
 *              the '.' character. Using a while loop with the conditions that
 *              element > 0, the element right of the current element is 0, and 
 *              the current index does not fall right beyond the end of the 
 *              array, each element > 0 slides to the right of the board.Next if 
 *              the current index value and value right the current index value
 *              are the same then they are added and stored in index value
 *              right the current index.   
 */
void slideSumRight(int board[], int boardWidth, int boardSize, int &checkMove)
{
	
	checkMove = 0; // If no moves are made then remains 0.
	
	// Iterates through board index's from end of array to beginning.
	for(int i=boardSize-1; i>=0; i--){
	 	if(i % boardWidth < boardWidth){ // Keeps from performing slide on right
	 												//  most column.
	 		int j = i; 
	 		// Loop continues while value at index and right of index are not 0.
	 		while(board[j]>0 && board[j+1] == 0 && 
	 				j < ((j/boardWidth)*boardWidth) + boardWidth-1){ // Keeps loop 	
																					 // within array
	 				board[j+1] = board[j];
	 				board[j] = 0;
	 				j++;
	 				checkMove = 1; // move has been made
	 		} // end while loop
	 		
	 		// Skip indexs for right column when summing
	 		if(j % boardWidth == 0) continue;
	 		
	 		// Sum equal values with right slide from right most column
	 		if(board[j] != 0 && board[j] == board[j+1]){
	 			board[j+1] = board[j]*2;
	 			board[j] = 0;
	 			checkMove = 1; // when summation is made
	 		}
	 	} // end conditional
	} // end for loop
	
	return;
}// End slideSumRight


/* --- slideSumLeft Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth 
 *              3. int boardSize
 *              4. int &checkMove
 *
 * Description: This function loops through the board array and finds all 
 *              elements that are greater than 0 (which are printed out as
 *              the '.' character. Using a while loop with the conditions that
 *              element > 0, the element left of the current element is 0, and 
 *              the current index does not fall left beyond the end of the 
 *              array, each element > 0 slides to the left of the board. Next if 
 *              the current index value and value left the current index value
 *              are the same then they are added and stored in index value
 *              left the current index.     
 */
void slideSumLeft(int board[], int boardWidth, int boardSize, int &checkMove)
{
	
	checkMove = 0; // If no moves are made then remains 0.
	
	// Iterates through board index's from beginning of array to end.
	for(int i=0; i<boardSize; i++){
	 	if(i % boardWidth > 0){ // Keeps from performing slide on left most
	 									//  column.
	 		int j = i; 
	 		// Loop continues while value at index and left of index are not 0.
	 		while(board[j]>0 && board[j-1] == 0 && 
	 				j > ((j/boardWidth)*boardWidth)){ // Keeps loop within array
				
	 				board[j-1] = board[j];
	 				board[j] = 0; 
	 				j--;
	 				checkMove = 1; // move has been made
	 		} // end while loop
	 		
	 		// Skip index's for left column when summing
	 		if(j % boardWidth == 0) continue;
	 		
	 		// Sum equal values with left slide from left most column
	 		if(board[j] != 0 && board[j] == board[j-1]){
	 			board[j-1] = board[j]*2;
	 			board[j] = 0;
	 			checkMove = 1; // when summation has been made
	 		}
	 	} // end conditional
	} // end for loop
	
	return;
}// End slideSumLeft


/* --- userInput Function ----
 * Parameters:  char &input 
 *
 * Description: This function prompts user for move direction. If input is 
 *              incorrect then the user is prompted again until the correct
 *              entry typed. If move letter is typed in lower case then for 
 *              consistency all correct input letters are made capital. The 
 *              function returns uppercase move letter. Possible moves include
 *              four direction slides, restart, exit, and manual value 
 *              placement.
 */
void userInput(char &input)
{
	static int moveCount = 1; // Keeps track of number of moves
	
	// When game is restarted number of moves goes back to 1
	if(input == 'R') moveCount = 1;
	
	cout<< moveCount << ". Your move:  ";
	cin>> input; 
	input = toupper(input); // changes lower case input to upper case
	
	// Loops until the correct input it typed
	while(1){
		if(input == 'A' || input == 'D' || input == 'W' || input == 'S'||
			input == 'R' || input == 'X' || input == 'P') break;
		
		else{ cout<<"Incorrect input..Please try again";
			cout<<"\n"<< moveCount << ". Your move:  ";
			cin>> input;
			input = toupper(input);
		}	
	}
	
	moveCount++;
	return;
}// End userInput 


/* --- checkUserInput Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *              3. char input
 *              4. int &checkMove
 *
 * Description: This function exits the game, restarts the game, or calls
 *              on function to manually set values on board depending on the 
 *              input value. 
 */
int checkUserInput(int board[], int boardSize, char input, int &checkMove)
{
	// If player wants to exit game
	if(input == 'X'){
		cout << "Exiting...\n";
		return 0; // this activates a break in main.
	}
	
	// Resets the board and move count
	if(input == 'R'){
		setBoardArray(board, boardSize);
		setRandomLocation(board, boardSize);
	}
	
	// Allows user to input location and value manually 
	if(input == 'P') manuallySetBoardArray(board, checkMove);
	
	return 1;
}// End checkUserInput


/* --- manuallySetBoardArray Function ----
 * Parameters:  1. int board []
 *              2. int &checkMove
 *
 * Description: This function takes user values for value and position and 
 *              puts them in the board array. Also makes sure that new random
 *              numbers aren't place on the board while manually setting. 
 */
void manuallySetBoardArray(int board[], int &checkMove)
{
 	checkMove = 0; // makes sure no moves are reflected 
 	
 	int position = 0;
 	int value = 0;
 	
 	cin >> position >> value; // gets values for postion and value
 	board[position] = value; // sets those values in array

 }// End manuallySetBoardArray


/* --- setRandomLocation Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *
 * Description: This function sets seed to clock time. A value is randomly 
 *              chosen 1 less the board size. Using value generated by 
 *              getRandomValue function this value is placed at a random 
 *              location on board.
 */
void setRandomLocation(int board [], int boardSize)
{
	//Set seed value to clock time.
	srand((int)time(NULL));
	int rIndex = rand() % (boardSize); // limit random number to size of array

	while(1){	   
	   // Search for open space (0) randomly and set random value
	   if(board[rIndex] == 0){
			board[rIndex] = getRandomValue();
			break;
		}
		// looks for new random location when previous was not empty
		else rIndex = rand() % (boardSize);  
	}// End find open location loop
	
	return;
}// End setRandomLocation


/* --- getRandomValue Function ----
 * Parameters:  *None* 
 *
 * Description: This function randomly flips between 2 and 4 and returns this 
 *              value to setRandomLocation.
 */
int getRandomValue()
{
	//Set random seed value to clock time.
	srand((int)time(NULL));
	int rVal = 0;
	
	do{
		rVal = (rand() % 3) + 2; // randomizes between 2 and 4
	}while( rVal == 3); // keeps looping until value 2 or 4

	return rVal;
}// End getRandomValue


/* --- checkPossibleMoves Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth
 *              3. int boardSize 
 *
 * Description: This function calls functions checkForOpenIndex and 
 *              validSurroundingIndex to check if there are any open spaces and 
 *              any possible moves left on the board. 
 */
int checkPossibleMoves(int board[], int boardWidth, int boardSize)
{
	
	// Checks for open spaces to place random number and surrounding pairs
	if(checkForOpenIndex(board, boardSize) == 0 &&
		validSurroundingIndex(board, boardWidth, boardSize) == 0) return 0;
	else return 1;

}// End checkPossibleMoves


/* --- validSurroundingIndex Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth
 *              3. int boardSize 
 *
 * Description: This function looks at each location on the board and checks
 *              if the surrounding locations are the same. If it finds one the
 *              returns 1 to checkPossibleMoves.
 */
int validSurroundingIndex(int board[], int boardWidth, int boardSize)
{
	// Iterates through board searching for pair values.
	for(int i=0; i<boardSize; i++){
			if(board[i] == board[i-1] || board[i] == board[i+1] ||
			board[i] == board[i+boardWidth] || board[i] == board[i-boardWidth])
			return 1;	
	}
	
	return 0; // when no pairs are found
}// End validSurroundingIndex 


/* --- checkForOpenIndex Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *
 * Description: This function scans the board in search of open spaces. If it 
 *              finds on then it returns 1 otherwise 0 to checkPossibleMoves.
 */
int checkForOpenIndex(int board [], int boardSize)
{
	
	int i = -1;
	for(i=0; i<boardSize; i++){
		if(board[i] == 0 ) return 1; // if open space found
	}
	
	return 0; // if no open space found
		
}// End checkForOpenIndex Function


/* --- checkWinner Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth 
 *              3. int boardSize
 *
 * Description: This function compares value score with value winning score.
 *              If they match then prints out winning text and exits game.
 */
int checkWinner(int board[], int boardWidth, int boardSize)
{
	if(getScore(board, boardSize) == setWinningScore(boardWidth)) {
		printBoard(board, boardWidth, boardSize);	
		cout << "Congrats!! You Won!!\n\n";
		cout << "Exiting...";					
		return 1;
	} 
	return 0; // if winning score is not met
}


/* --- getScore Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *
 * Description: This function scans the board array for the greatest value and 
 *              returns the value to check winner and printBoard to print 
 *              the current score.
 */
int getScore(int board[], int boardSize)
{
	int max = 0;
	
	// Iterates board array for max value
	for(int i=0; i<boardSize; i++){
		if(board[i]>=max)
			max = board[i];
	}

	return max;
}// End getScore 


/* --- getWinningScore Function ----
 * Parameters:  1. int boardWidth 
 *
 * Description: This function sets the winning score based on the size of the
 *              board size set by the user and returns this value to 
 *              printBoard and checkWinner.
 */
int setWinningScore(int boardWidth)
{
	// Adjusted for board width of 4 to be at value 1024 and to double that 
	// value with board width increment of 1. 
	int winningScore = 1024 * (boardWidth-3); 
	
	return winningScore;
}// End getWinningScore


/* --- printBoard Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth
 *              3. int boardSize 
 *
 * Description: This function prints the current positions and score. Where 
 *              there is a value of 0 a '.' is printed. Current scores and 
 *              winning scores are also printed. 
 */
void printBoard(int board [], int boardWidth, int boardSize)
{
	int score = getScore(board, boardSize); // calls for player current score
	int winningScore = setWinningScore(boardWidth); // calls for winning score
	
	cout<<"Game ends when you reach "<< winningScore <<".\n\n";
	cout<<"Score:  " << score; 
	
	// Loops through array and prints '.' where the value 0 is found.
	for(int i=0; i<boardSize; i++){
		if(i%(boardWidth) == 0) cout<<"\n"; // starts new row when input width met
			cout<<" ";			// spaces values and '.' 
			if(board[i] == 0)
			cout<<".";
			else cout<<board[i]; // prints value if > 0
	}
	cout<<"\n\n";	
	
	return;
}// End printBoard 


/* --- setBoardArray Function ----
 * Parameters:  1. int board[]
 *              2. int boardSize 
 *
 * Description: This function sets all values of board array to 0.
 */
void setBoardArray(int board [], int boardSize)
{
	// Loops through board size and assigns 0 values to each element
	for(int i=0; i<boardSize; i++){
		board[i] = 0;
	}
	return;
}// End setBoard 


/* --- setBoardSize Function ----
 * Parameters:  1. int &boardWidth
 *              2. int &boardSize
 *
 * Description: This function prompts user for board width and limits the
 *              the value between 4 an 12. If input is outside these values
 *              then user is prompted again for correct width selection. 
 *              Board size is made by multiplying width by itself.  
 */
void setBoardSize(int &boardWidth, int &boardSize)
{
	//int boardSize = 4;
	
	cout<<"Enter the size board you want, between 4 and 12:  ";
	cin>> boardWidth;
	
	// Restricting user to a boards size between 4 and 12
	while(1){
		if(boardWidth < 4 || boardWidth > 12){
			cout<<"Board size needs to be between 4 and 12, please try again.\n\n";
			cout<<"Enter the size board you want, between 4 and 12:  ";
			cin>>boardWidth;
		}else break; // if correct boardWidth selection
	}
	boardSize = boardWidth*boardWidth; // this make board array length
	
	return;
}// End setBoardSize 


/* --- printHeaderInstructions Function ----
 * Parameters:  *None* 
 *
 * Description: This function displays the CS141 standard header and game 
 *              instructions.   
 */
void printHeaderInstructions()
{
	//CS141 Standard Header
	cout<<"\n";
	cout<<"Author:   FILIP RADZIKOWSKI\n";
	cout<<"Lab:       Thursday 3pm\n";
	cout<<"Program:   #5, 1024 And More.\n";

	//Game Instruction
	cout<<"\nThis Program is based off of Gabriele Cirulli's game online at\n";
	cout<<"  bit.ly/great2048\n\n";
	cout<<"For each move enter a direction as a letter key, as follows:\n";
	cout<<"    W\n  A S D\n";
	cout<<"where A=left, W=up, D=right and S=down.\n\n";
	cout<<"After a move, when two identical valued tiles come together they\n";
	cout<<"join to become a new single tile with the value of the sum of the\n";
	cout<<"two originals. This value gets added to the score. On each move\n";
	cout<<"one new randomly choses value of 2 and 4 is placed in a random ";
	cout<<"open\nsquare. User input of r restarts the game, and x exits the";
	cout<<" game.\n\n";
	
	return;	
}// End printHeaderInstructions
	