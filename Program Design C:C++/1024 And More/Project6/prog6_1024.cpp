/*
 *  prog5_1024.cpp
 *     Text-based version of the game 1024, a variant of 2048 available online at:
 *        http://gabrielecirulli.github.io/2048/
 *     Object of game is to combine number tiles with the same value, accumulating
 *     points as the game progresses, to try and create the tile with the value 1024.
 *     Each move consists of sliding pieces to the left, up, right or down.
 *
 *  Class: Program #6 for CS 141, Spring 2014.
 *  System: Mac OS X
 *  Authors: Filip Radzikowski (Undo command). 
 *           Originally written by Dale Reed on 4/19/14. 
 *  
 *  Running program looks like:
 
     Filip Radzikowski
     UIC CS 141, Spring 2014
     Welcome to 1024 and More.
     This program is based off of Gabriele Cirulli's game online at
     bit.ly/great2048
     
     For each move enter a direction as a letter key, as follows:
         W
       A S D
     where A=left,W=up, D=right and S=down.
     
     After a move, when two identical valued tiles come together they
     join to become a new single tile with the value of the sum of the
     two originals. This value gets added to the score.  On each move
     one new randomly chosen value of 2 or 4 is placed in a random open
     square.  User input of x exits the game.
     
     Game ends when you reach 1024.
     
     Score: 0
             .     4     .     .
     
             .     .     .     .
     
             .     .     4     .
     
             .     .     .     .
     
     1. Your move: a
     
     Score: 0
             4     .     .     .
     
             .     .     .     .
     
             4     .     .     .
     
             .     .     2     .
     
     2. Your move: a
     .
     .
     .
*/

#include <iostream>
#include <iomanip>   // used for setting output field size using setw
#include <cstdlib>
using namespace std;


//--------------------------------------------------------------------
// Structure keeps track of each board change, score change and move change
struct Node {
	int *board;		// dynamically allocated board
	int score;		// will store current score
	int move;		// will store current move
	
	Node *pNext;	// pointer to next node
};

//--------------------------------------------------------------------
// Create new Node where current board, score, and move will be stored 
// and attached to the front of the linked list.
Node * createNode( int *board , int boardSize, int score, int move)
{
	Node *pTemp = new Node;			// allocate memory for temporary node pointer
	pTemp->board = new int[boardSize*boardSize]; // allocated memory for board[]
	
	// Copy current board to pointer temporary board
	for( int i = 0; i<boardSize*boardSize; i++){ 
		pTemp->board[i] = board[i];
	}
	
	pTemp->score = score;		// Copy current score to temporary score
	pTemp->move = move;			// Copy current move value to temporary move

	return pTemp;
}// End createNode


//--------------------------------------------------------------------
// Restoring previous moves board, score and move value. The head pointer is 
// returned after being set to previous board positions.
void restoreToPreviousValues(Node * &pHead, int boardSize, int board[], 
										int &score, int &move){
	
	Node* pTemp;					// Set temporary node
	
	pTemp = pHead->pNext;		// pTemp pointing to previous move  
	score = pTemp->score;		// reset score to previous score
	move = pTemp->move;			// resent move to previous move value
	
	pHead->pNext = NULL;			// Disconnect old node and set to NULL
	delete pHead->board;			// Delete dynamically allocated board in old head 
	delete pHead;					// Delete old head of list
	pHead = pTemp;					// This new node becomes the new head of the list
	
	// Reset previous board conditions using pointer pTemp
	for(int i=0; i<boardSize*boardSize; i++){
		board[i] = pTemp->board[i];
	}
}// End restoreToPreviousValues


//--------------------------------------------------------------------
// Display ID info
void displayIDInfo()
{
    cout << "Filip Radzikowski          \n";
    cout << "UIC CS 141, Spring 2014           \n";
    cout << "Welcome to 1024 and More. \n";
    cout << "This program is based off of Gabriele Cirulli's game online at \n";
    cout << "    bit.ly/great2048 \n";
    cout << " \n";
}//end displayIDInfo()


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "For each move enter a direction as a letter key, as follows: \n"
         << "    W    \n"
         << "  A S D  \n"
         << "where A=left,W=up, D=right and S=down. \n"
         << "  \n"
         << "After a move, when two identical valued tiles come together they    \n"
         << "join to become a new single tile with the value of the sum of the   \n"
         << "two originals. This value gets added to the score.  On each move    \n"
         << "one new randomly chosen value of 2 or 4 is placed in a random open  \n"
         << "square.  User input of x exits the game.                            \n"
         << "  \n";
}//end displayInstructions()


//--------------------------------------------------------------------
// Place a randomly selected 2 or 4 into a random open square on
// the board.
void placeRandomPiece( int board[], int boardSize)
{
    // Randomly choose a piece to be placed (2 or 4)
    int pieceToPlace = 2;
    if( rand()%2 == 1) {
        pieceToPlace = 4;
    }
    
    // Find an unoccupied square that currently has a 0
    int index;
    do {
        index = rand() % (boardSize*boardSize);
    }while( board[ index] != 0);
    
    // board at position index is blank, so place piece there
    board[ index] = pieceToPlace;
}//end placeRandomPiece()


//--------------------------------------------------------------------
// Prompt for and get board size, dynamically allocate space for the
// board, initialize the board and set the max tile value that
// corresponds to the board size.
void getSizeAndSetBoard( int * &board,          // dynamically allocated board
                         int * &previousBoard,  // space for copy of board
                         int &boardSize,        // user input board size
                         int &maxTileValue)     // max tile value, depending 
                                                //    on board size
{
    // Prompt for board size and set corresponding game end value
    cout << "Enter the size board you want, between 4 and 12: ";
    cin >> boardSize;
    
    // Allocate space for the 2-d board (and board copy), stored as a 1-d array
    board = new int[ boardSize * boardSize];  // e.g. a board of size 4 will have 4x4=16 elements
    previousBoard = new int[ boardSize * boardSize];
    
    // Initialize board to all 0's
    for( int row=0; row<boardSize; row++) {
        for( int col=0; col<boardSize; col++ ) {
            board[ row*boardSize + col] = 0;
        }
    }
    
    // Calculate and display game ending value
    for( int i=4; i<boardSize; i++) {
        maxTileValue = maxTileValue * 2;   // double for each additional board dimension > 4
    }
    cout << "Game ends when you reach " << maxTileValue << "." << endl;
    
    // Set two random pieces to start game
    placeRandomPiece( board, boardSize);
    placeRandomPiece( board, boardSize);
    
}//end getSizeAndSetBoard()


//--------------------------------------------------------------------
// Display the Board
void displayBoard( int *board, int boardSize, int score)
{
    // Set display width value depending on boardSize (corresponding max value)
    int displayWidth;
    switch( boardSize) {
        case 4:
        case 5:
        case 6:
        case 7: displayWidth = 5; break;  // up to   8,192
        case 8:
        case 9:
        case 10: displayWidth = 6; break; // up to  65,536
        case 11:
        case 12: displayWidth = 7; break; // up to 262,144
        default:
             // Sanity check, should never get here
             cout << "Invalid boardSize of " << boardSize
                  << ". Exiting program..\n" << endl;
             exit( -1);
             break;
    }
    
    cout << "\n"
         <<"Score: " << score << endl;
    for( int row=0; row<boardSize; row++) {
        cout << "   ";
        for( int col=0; col<boardSize; col++ ) {
            
            // 1-d index corresponding to row & col
            int current = row*boardSize + col;  
            
            // set output field size to 6 (Requires #include <iomanip> )
            cout << setw( displayWidth);    
            // display '.' if board value is 0
            if( board[ current] == 0) {
               cout << '.';
            }
            else {
               cout << board[ current];
            }
        }
        cout << "\n\n";
    }
}//end displayBoard()


//--------------------------------------------------------------------
// Make a copy of the board.  This is used after an attempted move
// to see if the board actually changed.
void copyBoard(
               int previousBoard[], // destination for board copy
               int board[],         // board from which copy will be made
               int boardSize)       // size of the board
{
    for( int row=0; row<boardSize; row++) {
        for( int col=0; col<boardSize; col++ ) {
            // 1-d index corresponding to row & col
            int current = row*boardSize + col;  
            previousBoard[ current] = board[ current];
        }
    }
}//end copyBoard()


//--------------------------------------------------------------------
// See if board changed this turn. If not, no additional piece
// is randomly added and move number does not increment in main().
// Returns true if boards are different, false otherwise.
bool boardChangedThisTurn( int previousBoard[], int board[], int boardSize)
{
    // Compare element by element.  If one is found that is different
    // then return true, as board was changed.
    for( int row=0; row<boardSize; row++) {
        for( int col=0; col<boardSize; col++ ) {
            int current = row*boardSize + col;  // 1-d index corresponding to row & col
            if( previousBoard[ current] != board[ current]) {
                return true;
            }
        }
    }
    
    return false;  // No board difference was found
}


// While the 4 functions below (slideLeft(), slideRight(), slideUp(), 
// slideDown() ) could be all combined into a single function, that single 
// function would be difficult to understand, so these 4 functions were left 
// separate.


//--------------------------------------------------------------------
// Slide all tiles left, combining matching values, updating the score
void slideLeft( int board[], int boardSize, int &score)
{
    // handle each row separately
    for( int row=0; row<boardSize; row++) {
        // set index limit for this row to be index of left-most tile on this row
        int limit = row * boardSize;
        
        // Start from the second column and process each element from left to right
        for( int col=1; col<boardSize; col++) {
            
            // get 1-d array index based on row and col
            int current = row * boardSize + col;

            // slide current piece over as far left as possible
            while( board[ current-1] == 0 && current > limit) {
                board[ current-1] = board[ current];
                board[ current] = 0;
                current--;
            }
            
            // Combine it with left neighbor if values are the same and non zero.
            // The additional check for (current > limit) ensures a tile can be combined
            // at most once on a move, since limit is moved right every time a combination is made.
            // This ensures a row of:  2 2 4 4   ends up correctly as:  4 8 0 0   and not:  8 4 0 0
            if( (board[ current-1] == board[ current]) && (board[ current] != 0) && (current > limit)) {
                board[ current-1] = board[ current-1] + board[ current];
                board[ current] = 0;
                limit = current;           // Reset row index limit, to prevent combining a piece more than once
                score += board[ current-1];  // Update score
            }
            
        }//end for( int col...
    }//end for( int row...
    
}//end slideLeft()


//--------------------------------------------------------------------
// Slide all tiles right, combining matching values, updating the score
void slideRight( int board[], int boardSize, int &score)
{
    // handle each row separately
    for( int row=0; row<boardSize; row++) {
        // set index limit for this row to be index of right-most tile on this row
        int limit = row * boardSize + boardSize - 1;
        
        // Start from the second-to-last column and process each element from right to left
        for( int col=boardSize - 1; col>=0; col--) {
            
            // get 1-d array index based on row and col
            int current = row * boardSize + col;
            
            // slide current piece over as far right as possible
            while( board[ current+1] == 0 && current < limit) {
                board[ current+1] = board[ current];
                board[ current] = 0;
                current++;
            }
            
            // Combine it with right neighbor if values are the same and non zero.
            // The additional check for (current < limit) ensures a tile can be combined
            // at most once on a move, since limit is moved left every time a combination is made.
            // This ensures a row of:  4 4 2 2   ends up correctly as:  0 0 8 4   and not:  0 0 4 8
            if( (board[ current+1] == board[ current]) && (board[ current] != 0) && (current < limit)) {
                board[ current+1] = board[ current+1] + board[ current];
                board[ current] = 0;
                limit = current;           // Reset row index limit, to prevent combining a piece more than once
                score += board[ current+1];  // Update score
            }
            
        }//end for( int col...
    }//end for( int row...
    
}//end slideRight()


//--------------------------------------------------------------------
// Slide all tiles up, combining matching values, updating the score
void slideUp( int board[], int boardSize, int &score)
{
    // handle each column separately
    for( int col=0; col<boardSize; col++) {
        // set index limit for this column to be index of top-most tile on this row
        int limit = col;
        
        // Start from the second row and process each element from top to bottom
        for( int row=1; row<boardSize; row++) {
            
            // get 1-d array index based on row and col
            int current = row * boardSize + col;
            
            // slide current piece up as far as possible
            while( board[ current-boardSize] == 0 && current > limit) {
                board[ current-boardSize] = board[ current];
                board[ current] = 0;
                current = current - boardSize;
            }
            
            // Combine it with upper neighbor if values are the same and non zero.
            // The additional check for (current > limit) ensures a tile can be combined
            // at most once on a move, since limit is moved down every time a combination is made.
            if( (board[ current-boardSize] == board[ current]) && (board[ current] != 0) && (current > limit)) {
                board[ current-boardSize] = board[ current-boardSize] + board[ current];
                board[ current] = 0;
                limit = current;           // Reset row index limit, to prevent combining a piece more than once
                score += board[ current-boardSize];  // Update score
            }
            
        }//end for( int col...
    }//end for( int row...
    
}//end slideUp()


//--------------------------------------------------------------------
// Slide all tiles down, combining matching values, updating the score
void slideDown( int board[], int boardSize, int &score)
{
    // handle each column separately
    for( int col=0; col<boardSize; col++) {
        // set index limit for this column to be index of bottom-most tile on this row
        int limit = (boardSize - 1) * boardSize + col;
        
        // Start from the next to last row and process each element from bottom to top
        for( int row=boardSize-1; row>=0; row--) {
            
            // get 1-d array index based on row and col
            int current = row * boardSize + col;
            
            // slide current piece down as far as possible
            while( board[ current+boardSize] == 0 && current < limit) {
                board[ current+boardSize] = board[ current];
                board[ current] = 0;
                current = current + boardSize;
            }
            
            // Combine it with lower neighbor if values are the same and non zero.
            // The additional check for (current < limit) ensures a tile can be combined
            // at most once on a move, since limit is moved up every time a combination is made.
            if( (board[ current+boardSize] == board[ current]) && (board[ current] != 0) && (current < limit)) {
                board[ current+boardSize] = board[ current+boardSize] + board[ current];
                board[ current] = 0;
                limit = current;           // Reset row index limit, to prevent combining a piece more than once
                score += board[ current+boardSize];  // Update score
            }
            
        }//end for( int col...
    }//end for( int row...
    
}//end slideDown()


//--------------------------------------------------------------------
// Return true if we're not done, false if we *are* done
//    Game is done if board is full and no more valid moves can be made
//    or if a tile with maxTileValue has been created.
bool notDone( int board[],      // current board
              int boardSize,    // size of one side of board
              int maxTileValue) // max tile value for this size board
{
    // See if the maxTileValue is found anywhere on the board.
    // If so, game is over.
    for( int i=0; i<boardSize*boardSize; i++) {
        if( board[ i] == maxTileValue) {
            cout << "Congratulations!  You made it to " << maxTileValue << " !!!" << endl;
            return false;  // there are open squares, so we are not done yet
        }
    }
    
    // See if there are any open squares.  If so return true since we aren't done
    for( int i=0; i<boardSize*boardSize; i++) {
        if( board[ i] == 0) {
            return true;  // there are open squares, so we are not done yet
        }
    }
    
    // All squares are full.
    // To check if board is done, make a copy of board, then slide left
    // and slide down.  If resulting board is same as original, we are done
    // with game since there are no moves to be made.
    int *boardCopy = new int[ boardSize * boardSize];
    copyBoard( boardCopy, board, boardSize);
    int tempScore = 0;   // used as a placeHolder only for function calls below
    slideLeft( boardCopy, boardSize, tempScore);
    slideDown( boardCopy, boardSize, tempScore);
    
    // Compare each square of boards.  If any is different, a move is possible
    for( int i=0; i<boardSize*boardSize; i++) {
        if( boardCopy[ i] != board[ i]) {
            return true;  // Game is not done
        }
    }
    
    cout << "\n"
         << "No more available moves.  Game is over.\n"
         << "\n";
    return false;  // Game is done since all squares are full and there are no moves
}//end notDone()


//--------------------------------------------------------------------

int main()
{
    int score = 0;
    int boardSize = 4;        // user will enter this value.  Set default to 4
    int *board;               // dynamically allocated space depends on set size
    int *previousBoard;       // store copy of board, did move change the board
    int maxTileValue = 1024;  // 1024 for 4x4 board, 2048 for 5x5, etc.
    char userInput = ' ';     // handles user input
    int move = 1;             // user move counter
    Node *pHead = NULL;			// pointer to head of list
    Node *pTemp = NULL;			// pointer used to allocate nodes
    
    
    // Display ID info and instructions
    displayIDInfo();
    displayInstructions();
    
    // get the board size, create and initialize the board, 
    // and set the max tile value
    getSizeAndSetBoard( board, previousBoard, boardSize, maxTileValue);
    
    pHead = createNode( board, boardSize, score, move);
    
    // Main loop to display board, prompt for and handle move and check for win
    do {
        // Display the board
        displayBoard( board, boardSize, score);
        
        // Copy board.  After attempting a move this is used to verify that the 
        // board changed, which allows randomly placing an additional piece on 
        // board and updating the move number.
        copyBoard( previousBoard, board, boardSize);  // copy from board into 
        																//    previousBoard
        // Prompt for and handle user input
        cout << move << ". Your move: ";
        cin >> userInput;
        switch (userInput) {
            case 'x':
                    cout << "Thanks for playing. Exiting program...";
                    exit( 0);
                    break;
            case 'u':
            		  cout << "\n"
            				 << "Undo was selected. "
            			    << "Restoring game back to previous move.\n";
            		  // Retrieve node information from previous moves
            		  // without going beyond the first move
            		  if (pHead->pNext != NULL){
            				restoreToPreviousValues(pHead, boardSize, board, 
            												score, move);
            		  }
            		  // Undo beyond the first move is not allowed
            		  else{
            		      cout << "Sorry, you cannot undo past the beginning "
            					  << "of the game.  Please retry move.";
            		  }
            		  continue;       // continue back up to redisplay board and 
            		  						//   get new user input   
            		  break;
            
            case 'r':
                    cout << "\n"
                         << "Resetting board \n"
                         << "\n";
                    getSizeAndSetBoard( board, previousBoard, boardSize, 
                    							maxTileValue);
                    score = 0;
                    move = 1;
                    continue;  // go back up to main loop and restart game
                    break;
            case 'a':
                    slideLeft( board, boardSize, score);  // Slide left
                    break;
            case 's':
                    slideDown( board, boardSize, score);  // Slide down
                    break;
            case 'd':
                    slideRight( board, boardSize, score); // Slide right
                    break;
            case 'w':
                    slideUp( board, boardSize, score);    // Slide up
                    break;
            case 'p':
                    // Place a piece on the board
                    int index;  // 1-d array index location to place piece
                    int value;  // value to be placed
                    cin >> index >> value;
                    board[ index] = value;
                    continue;  // Do not increment move number or 
                  				 //   place random piece
                    break;
            default:
                    cout << "Invalid input, please retry.";
                    continue;
                    break;
        }//end switch( userInput)
        
        // If the move resulted in pieces changing position, then it was a valid 
        // move so place a new random piece (2 or 4) in a random open square and 
        // update move number.
        if( boardChangedThisTurn( previousBoard, board, boardSize)) {
            // Place a random piece on board
            placeRandomPiece( board, boardSize);
            
            // Update move number after a valid move
            move++;
        }
        
        // Attach new node to front of linked list of moves
        pTemp = createNode( board, boardSize, score, move); // create new node
        pTemp->pNext = pHead;  // Connect new node to the old head of list
        pHead = pTemp;         // This new node becomes the new head of the list
 
        
        // clear the screen, which is system("clear") on UNIX 
        system("clear");
        
    }while( notDone( board, boardSize, maxTileValue));
    
    // Display final board
    displayBoard( board, boardSize, score);
    
    cout << "Exiting program...\n\n";
    return 0;
}//end main()

