/* ----------------------------------------------------------------------------- 
 * 1024 And More! 
 *
 * Class: CS 141, Spring 2014.  Wed 3pm lab.
 * System: Mac OS X 10.6.8 on TextWrangler
 * Author: Filip Radzikowski
 *
 * ToDo: 
 * -----------------------------------------------------------------------------
 */

//-- Header Files ---
#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;


//--- Function Declarations ---
void printHeaderInstructions();
void setBoardSize(int&, int&);
void setBoardArray(int*, int);
void printBoard(int*, int, int);
int getRandomValue();
void userMove(int*, int, int, char, int&);
void slideSumLeft(int*, int, int, int&);
void slideSumRight(int*, int, int, int&);
void slideSumUp(int*, int, int, int&);
void slideSumDown(int*, int, int, int&);
void userInput(char&);
void manuallySetBoardArray(int*, int&);
void setRandomLocation(int*, int);
int checkPossibleMoves(int*, int, int);
int validSurroundingIndex(int*,int, int);
int checkWinner(int*, int, int);
int getScore(int*, int);
int setWinningScore(int);
int checkForOpenIndex(int*, int);
int checkUserInput(int*, int, char, int&);



//----------------------------- Main Function ----------------------------------

int main()
{
	//system("clear");
	//printHeaderInstructions();
	
	int boardWidth = 0;
	int boardSize = 0;
	int winner = 0;
	char input = ' ';
	int checkMove = 1;
	
	// Gets user input size (4-12) and total elements in boards
	setBoardSize(boardWidth, boardSize);
	int board[boardSize];
	
	// Set array elements to 0 for total board size
	setBoardArray(board, boardSize);
	
	// Set initial number on board
	setRandomLocation(board, boardSize);
	

	do{
		//system("clear");
		//printHeaderInstructions();
		
		//if surrounding #a != #a || 0 and board is full then GAME OVER
		if(checkPossibleMoves(board, boardWidth, boardSize) == 1){
			
			// Check if slide or summation was made in order to add random value 
			if(checkMove == 1){
				// Find random open space on board and set random value(2 or 4)
				setRandomLocation(board, boardSize);
			}
			
			printBoard(board, boardWidth, boardSize);
			
			userInput(input);
			if(checkUserInput(board, boardSize, input, checkMove) == 0)break;

			userMove(board, boardWidth, boardSize, input, checkMove);
			winner = checkWinner(board, boardWidth, boardSize);	
		}
		else {
			cout<< "\nGame Over!! You ran out of moves!!\n";
			break;
		}
		
	}while(winner == 0);
										

}

//------------------------ Sub-Function Definitions ----------------------------


/* --- checkUserInput Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *              3. char input
 *
 * Description: This function
 */
int checkUserInput(int board[], int boardSize, char input, int &checkMove)
{
	if(input == 'X'){
		cout << "Exiting...";
		return 0;
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
 *              2. int boardWidth 
 *              3. int boardSize
 *
 * Description: This function
 */
 void manuallySetBoardArray(int board[], int &checkMove)
 {
 	checkMove = 0;
 	int position = 0;
 	int value = 0;
 	
 	cin >> position >> value;
 	board[position] = value;
 
 
 }// End manuallySetBoardArray


/* --- checkWinner Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth 
 *              3. int boardSize
 *
 * Description: This function
 */
int checkWinner(int board[], int boardWidth, int boardSize)
{
	if(getScore(board, boardSize) == setWinningScore(boardWidth)) {
		printBoard(board, boardWidth, boardSize);	
		cout << "Congrats!! You Won!!\n\n";
		cout << "Exiting...";					
		return 1;
	} 
	return 0;
}

/* --- userMove Function ----
 * Parameters:  1. int board []
 *              2. int boardWidth 
 *              3. int boardSize
 *
 * Description: This function prompts user for slide direction. Using switch
 *              case it then calls on the respective slide function.
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
 *					 each element > 0 slides to the bottom of the board.  
 */
 void slideSumDown(int board[], int boardWidth, int boardSize, int &checkMove)
 {
 	checkMove = 0;
 	
 	for(int i=boardSize-1; i >= 0; i--){
		if(i % boardWidth < boardWidth){
			
			int j = i;
			while(board[j]>0 && board[j+boardWidth] == 0 &&
					j <= ((j/boardWidth)*boardWidth + boardWidth-1)){
			
				board[j+boardWidth] = board[j];
				board[j] = 0;
				j+=boardWidth;
				checkMove = 1;
			
			}//end while loop
			// Skip index's for last row when summing
			if(j/boardWidth == boardWidth-1) continue;
			
			// Sum equal values with down slide from bottom most row
			if(board[j] != 0 && board[j] == board[j+boardWidth]){
				board[j+boardWidth] = board[j]*2;
				board[j] = 0;
				checkMove = 1;
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
 *					 each element > 0 slides to the top of the board.  
 */
void slideSumUp(int board[], int boardWidth, int boardSize, int &checkMove){
	
	checkMove = 0;
	
	for(int i=0; i<boardSize; i++){
		if(i % boardWidth < boardWidth){
		
			int j = i;
			while(board[j]>0 && board[j-boardWidth] == 0 &&
					j >= ((j/boardWidth)*boardWidth)){
				
				board[j-boardWidth] = board[j];
				board[j] = 0;
				j-=boardWidth;
				checkMove = 1;
			}// end while loop
			
			// Skip indexs for first row when summing 
			if(j/boardWidth == 0)continue; 
			
			// Sum equal values with upward slide from top most row
			if(board[j] != 0 && board[j] == board[j-boardWidth]){
				board[j-boardWidth] = board[j]*2;
				board[j] = 0;
				checkMove = 1;
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
 *              array, each element > 0 slides to the right of the board.  
 */
void slideSumRight(int board[], int boardWidth, int boardSize, int &checkMove){
	
	checkMove = 0;
	
	for(int i=boardSize-1; i>=0; i--){
	 	if(i % boardWidth < boardWidth){
	 	
	 		int j = i; 
	 		while(board[j]>0 && board[j+1] == 0 && 
	 				j < ((j/boardWidth)*boardWidth) + boardWidth-1){	
				
	 				board[j+1] = board[j];
	 				board[j] = 0;
	 				j++;
	 				checkMove = 1;
	 		}
	 		
	 		// Skip indexs for right column when summing
	 		if(j % boardWidth == 0) continue;
	 		
	 		// Sum equal values with right slide from right most column
	 		if(board[j] != 0 && board[j] == board[j+1]){
	 			board[j+1] = board[j]*2;
	 			board[j] = 0;
	 			checkMove = 1;
	 		}
	 	}
	}
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
 *              array, each element > 0 slides to the left of the board.    
 */
void slideSumLeft(int board[], int boardWidth, int boardSize, int &checkMove){
	
	checkMove = 0;
	
	for(int i=0; i<boardSize; i++){
	 	if(i % boardWidth > 0){
	 	
	 		int j = i; 
	 		//    Value in space...previous space empty....tells which row
	 		while(board[j]>0 && board[j-1] == 0 && j > ((j/boardWidth)*boardWidth) ){	
				
	 				board[j-1] = board[j];
	 				board[j] = 0; 
	 				j--;
	 				checkMove = 1;
	 		}
	 		
	 		// Skip index's for left column when summing
	 		if(j % boardWidth == 0) continue;
	 		
	 		// Sum equal values with left slide from left most column
	 		if(board[j] != 0 && board[j] == board[j-1]){
	 			board[j-1] = board[j]*2;
	 			board[j] = 0;
	 			checkMove = 1;
	 		}
	 	}
	}
	return;
}// End slideSumLeft


/* --- userInput Function ----
 * Parameters:  char &input 
 *
 * Description: This function prompts user for move direction. If input is 
 *              incorrect then the user is prompted again until the correct
 *              entry typed. If move letter is typed in lower case then for 
 *              consistency all correct input letters are made capital. The 
 *              function returns uppercase move letter. 
 */
void userInput(char &input){
	static int moveCount = 1;
	
	// When game is restarted number of moves goes back to 1
	if(input == 'R') moveCount = 1;
	
	cout<< moveCount << ". Your move:  ";
	cin>> input;
	input = toupper(input);
	
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


/* --- setRandomLocation Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *
 * Description: This function prompts user for the size of the board, limits
 *              the size between 4 and 12, and returns input value representing
 *              board size back to main.
 */
void setRandomLocation(int board [], int boardSize){
	//Set random seed value to clock time.
	srand((int)time(NULL));
	int rIndex = rand() % (boardSize);

	//if(){
	while(1){	   
	   
	   if(board[rIndex] == 0){
			board[rIndex] = getRandomValue();
			break;
		}
		else rIndex = rand() % (boardSize);
	}// End find open location loop
	
	return;
}// End setRandomLocation


/* --- printBoard Function ----
 * Parameters:  *None* 
 *
 * Description: This function prompts user for the size of the board, limits
 *              the size between 4 and 12, and returns input value representing
 *              board size back to main.
 */
void printBoard(int board [], int boardWidth, int boardSize){
	int score = getScore(board, boardSize);
	
	cout<<"Game ends when you reach "<<setWinningScore(boardWidth)<<".\n\n";
	cout<<"Score:  " << score;

	for(int i=0; i<boardSize; i++){
		if(i%(boardWidth) == 0) cout<<"\n";
			cout<<" ";
			if(board[i] == 0)
			cout<<".";
			else cout<<board[i];
	}
	cout<<"\n\n";	
	
	return;
}// End printBoard Function


/* --- setBoardArray Function ----
 * Parameters:  *None* 
 *
 * Description: This function prompts user for the size of the board, limits
 *              the size between 4 and 12, and returns input value representing
 *              board size back to main.
 */
void setBoardArray(int board [], int boardSize){
	
	for(int i=0; i<boardSize; i++){
		board[i] = 0;
	}
	return;
}// End setBoard Function


/* --- setBoardSize Function ----
 * Parameters:  *None* 
 *
 * Description: This function prompts user for the size of the board, limits
 *              the size between 4 and 12, and returns input value representing
 *              board size back to main.
 */
void setBoardSize(int &boardWidth, int &boardSize){
	//int boardSize = 4;
	
	cout<<"Enter the size board you want, between 4 and 12:  ";
	cin>> boardWidth;
	
	// Restricting user to a boards size between 4 and 12
	while(1){
		if(boardWidth < 4 || boardWidth > 12){
			cout<<"Board size needs to be between 4 and 12, please try again.\n\n";
			cout<<"Enter the size board you want, between 4 and 12:  ";
			cin>>boardWidth;
		}else break;
	}
	boardSize = boardWidth*boardWidth;
	
	return;
}// End setBoardSize Function


/* --- checkPossibleMoves Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *
 * Description: This function prompts user for the size of the board, limits
 *              the size between 4 and 12, and returns input value representing
 *              board size back to main.
 */
int checkPossibleMoves(int board[], int boardWidth, int boardSize){
	
	// Check for open spaces to place random number 
	if(checkForOpenIndex(board, boardSize) == 0 &&
		validSurroundingIndex(board, boardWidth, boardSize) == 0) return 0;
	else return 1;

}// End checkPossibleMoves


/* --- validSurroundingIndex Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *
 * Description: This function looks at each location on the board and checks
 *              if the surrounding locations are the same.
 */
int validSurroundingIndex(int board[], int boardWidth, int boardSize){
	
	for(int i=0; i<boardSize; i++){
			if(board[i] == board[i-1] || board[i] == board[i+1] ||
			board[i] == board[i+boardWidth] || board[i] == board[i-boardWidth])
			return 1;	
	}
	
	return 0;
}// End validSurroundingIndex 


/* --- checkOpenIndex Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *
 * Description: This function prompts user for the size of the board, limits
 *              the size between 4 and 12, and returns input value representing
 *              board size back to main.
 */
int checkForOpenIndex(int board [], int boardSize){
	
	int i = -1;
	for(i=0; i<boardSize; i++){
		if(board[i] == 0 ) return 1;
	}
	
	return 0;
		
}// End checkForOpenIndex Function


/* --- getRandomValue Function ----
 * Parameters:  *None* 
 *
 * Description: This function randomly flips between 2 and 4 and returns this 
 *              value to setRandomLocation.
 */
int getRandomValue(){
	//Set random seed value to clock time.
	srand((int)time(NULL));
	int rVal = 0;
	
	do{
		rVal = (rand() % 3) + 2;
	}while( rVal == 3);

	return rVal;
}// End getRandomValue


/* --- getScore Function ----
 * Parameters:  1. int board []
 *              2. int boardSize 
 *
 * Description: This function prompts user for the size of the board, limits
 *              the size between 4 and 12, and returns input value representing
 *              board size back to main.
 */
int getScore(int board[], int boardSize){
	int max = 0;
	
	for(int i=0; i<boardSize; i++){
		if(board[i]>=max)
			max = board[i];
	}

	return max;
}// End getScore 


/* --- getWinningScore Function ----
 * Parameters:  1. int boardWidth 
 *
 * Description: This function prompts user for the size of the board, limits
 *              the size between 4 and 12, and returns input value representing
 *              board size back to main.
 */
int setWinningScore(int boardWidth){
	int winningScore = 1024 * (boardWidth-3);

	return winningScore;
}// End getWinningScore


/* --- printHeaderInstructions Function ----
 * Parameters:  *None* 
 *
 * Description: This function displays the CS141 standard header and game 
 *              instructions.   
 */
void printHeaderInstructions(){
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
	