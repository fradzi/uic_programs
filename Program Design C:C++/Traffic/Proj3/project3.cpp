#include<stdio.h>
#include <stdlib.h>


void setupBoard(char*, int);

void displayBoard(char*, int);

void getUserInput(char*, char*, char*);

int doesUserWantToQuit(char);

int isValidInput(char, char, char);

void moveCar(char, char, char);

int checkForWinningCondition(char*, int);

void printResults(int);

void printHeaderInstructions ();



int main ()
{
	
	int const boardSize = 64;
	char board[boardSize];
	int winner = 0;
	
	char car, direction, distance = ' '; // user input storage characters
	
	printHeaderInstructions();

	setupBoard( board, boardSize);
	
	
	
	do{
	
	displayBoard( board, boardSize);
	getUserInput( &car, &direction, &distance); //formatUserInput(); Pass by pointer
	if( doesUserWantToQuit(car)) break;
	
	if(isValidInput( car, direction, distance) ){
		
		moveCar( car, direction, distance); // decompose further function for directions
		winner = checkForWinningCondition(board, boardSize);
		} else {
		printf("Not a valid move. Please Enter again."); 
		}
		
	
	
	} while(winner == 0);
	
	printResults(winner);
	
	
    return 0;	
	
}



void setupBoard(char board[], int boardSize){
	
	FILE *pInputFile;        // file pointer 
   	//char board[ 25];         // the 5x5 board
   	int i=0;                 // loop counter 
   	char inputFileName[] = "TRAFFIC.txt"; 

   	// Associate the actual file name with file pointer and try to open it 
   	pInputFile = fopen(inputFileName, "r");
   	// Verify input file was found
   	if( pInputFile == NULL) {
      printf("Attempt to open file %s failed.  Exiting ... \n", inputFileName);
      exit( -1);       
   	}
   
   	// Read from the file into the board.  Space in front of %c is important!
   	while( fscanf(pInputFile, " %c", &board[ i]) != EOF)  {
    	  i++;
   	}

   	fclose( pInputFile);   // close input file
   
	
	return; 
}

void displayBoard(char board[], int boardSize){

	int i = 0;
	// show contents of board
  	printf("Board is: ");
   	for( i=0; i<boardSize; i++) {	  
   		if( i%8 == 0) {
        	printf("\n");
        }
    printf("%c", board[ i]);
   	}
   
   printf("\n");
   
	return;
}

void getUserInput(char* car, char* direction, char* distance){


	return;
}

int doesUserWantToQuit(char car){


	return 1;
}

int isValidInput(char car, char direction, char distance){


	return 1;
}

void moveCar(char car, char direction, char distance){


	return;
}

int checkForWinningCondition(char board[], int boardSize){


	return 1;
}

/* --- printResults Function ----
 * Parameters:  1). int winner: interger parameter that should be 0 if the user 
 *                              did not win the game, and 1 if the user has won
 *                              the game.
 *                               
 * Description: This function displays the end results of the game. If the
 *              winner parameter is 1, i.e. the user has won, the function 
 *              displays the "winner" message. Then, this functions
 *              displays the exit message.
 *          
 */
void printResults(int winner){
    char temp = ' '; // char variable used to pause the program before it exits
    
    if(winner == 1) { // User has won message
        printf("\nWinner, Winner, Chicken Dinner!!!!");
    }
    printf("\nThank you for playing. Exiting....\n");
    printf("Press any key to continue. . .");
    scanf("%c", &temp);
	return;
} 

/* --- printHeaderInstructions Function ----
 * Parameters:  *None* 
 *
 * Description: This function displays the CS141 stnadard header and game 
 *              instructions
 *   
 */
void printHeaderInstructions (){
    //CS141 Standard Header
    printf("Authors:   Filip Radzikowski and Christopher Schultz\n");
    printf("Lab:       Both in Thursday 3pm\n");
    printf("Program:   #3, Traffic\n");
    
    //Game Instructions
    printf("\nWelcome to the traffic game! \n \n");
    printf("Move the vehicles so that the Red car (RR) can\n");
    printf("exit the board to the righ. Each move should be\n");
    printf("of the form:  CDN  where  C  is the vehicle to\n");
    printf("be moved,  D  is the direction (u for up, d for down,\n");
    printf("l for left or r for right), and  N  is the number of\n");
    printf("squares to move it. For example  GR2  means move the\n");
    printf("G vehicle to the right 2 squares. Lower-case input\n");
    printf("such as  gr2  is also accepted. Enter x to exit\n");
    printf("the program.\n \n");
    
    
	return;
}





























