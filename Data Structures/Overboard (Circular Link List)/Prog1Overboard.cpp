/* -----------------------------------------------------------------------------
 *
 * Program Name : Overboard
 * 
 * Class: CS 251, Fall 2014. 
 * System: Mac OS X, Version 10.6.8, Sublime, Terminal
 * Author:  Filip Radzikowski          
 * Lab:     Thursday 11AM           
 * Program: # 1
 *
 *
 *
 * Description: Stardate 2015. You are captain on a spaceship which is losing 
 *              all life-support systems.  On board, you have passengers 
 *              consisting of both humans and androids operating under the 
 *              illusion that they too are humans.  The thing is that the 
 *              escape pod is limited in size and can only hold all the humans. 
 *              You must select the passengers that will not survive. 
 *					
 *              Humans being so cleaver have devised a system that will eject
 *              all of the androids and make it look as though it was by chance.
 *              
 *				A Stardate is boarded by a crew of androids and humans of 
 *              varying size. The size is noted and an iteration from 1 to n-1
 *				is run by the computer (how ironic) until an iteration is found
 *				that succeeds in only ejecting the androids wihtout any 
 *              retaliation. This iteration is returned as N. 


 -----------------------------------------------------------------------------*/
 


//---PREPROCESSOR COMMANDS---//
#include<iostream>
#include<fstream>
#include<cassert>

using namespace std;

//Data structure Node for creating link list
struct Node{
	char passenger;
	Node* pNextSeat;
};

//---FUNCTION DECLARATIONS---//	
void recruitCrew(char*&, int&, int&, int&); //Grab string from .txt
void seatCrew(Node*& , char*, int);			//Transfer string to link list	
void displaySeatedCrew(Node*);				//Display link list
void ejectPassenger( Node*&);				//Deallocate Android node
void memoryCleanup(Node*&);					//Deallocate ship

int main ()
{
	int n = 0;					//The correct iteration
	int crewSize;				//How many folks on board
	int dynamicCrewSize = 10;	//Initial size of crew and allocating multiple
	char *boardingShip = new char[dynamicCrewSize]; // original passengers               
	int androidCount = 0;		//Number of androids
	int remainingAndroids;		//Track ejections to total count
	
	Node* pTail = NULL;
	
	cout << "\nAuthor: Filip Radzikowski" << endl;
 	cout << "Lab: Thurs 11AM" << endl;
 	cout << "Program: #1, Overboard\n" << endl;

	
	cout << "\nStardate 2015. You are captain on a spaceship which is losing \n";
	cout << "all life-support systems.  On board, you have passengers \n"; 
    cout <<"consisting of both humans and androids operating under the\n"; 
    cout <<"illusion that they too are humans.  The thing is that the\n";
    cout <<"escape pod is limited in size and can only hold all the humans.\n";
    cout <<"You must select the passengers that will not survive.\n\n";         
    cout <<"Humans being so cleaver have devised a system that will eject\n";
    cout <<"all of the androids and make it look as though it was by chance.\n\n";
    cout <<"A Stardate is boarded by a crew of androids and humans of \n";
    cout <<"varying size. The size is noted and an iteration from 1 to n-1\n";
    cout <<"is run by the computer (how ironic) until an iteration is found\n";
    cout <<"that succeeds in only ejecting the androids wihtout any\n";
    cout <<"retaliation. This iteration is returned as N." << endl;
    
    //Get passenger from file and put into array
	recruitCrew(boardingShip, crewSize, androidCount, dynamicCrewSize);
	
	printf("The size of the crew onboard is %d.\n", crewSize);
	printf("The number of androids on board is %d.\n\n", androidCount);
	
	//Transfer data from array to link list
	seatCrew(pTail, boardingShip, crewSize);
	
	//Delete previously allocated link list 
	memoryCleanup(pTail);
	
	cout << "The visual representation of Stardate's remaining passengers\n";
	cout << "with each iteration of N:\n" << endl;
	// Iteration of from 1 to n-1 in search of magic number that will 
	// eject only the androids
	for(int n = 1; n <= crewSize; n++){
		
		//Reset original crew in original link list order and size	
		seatCrew(pTail, boardingShip, crewSize);

		remainingAndroids = androidCount;  // Tracks androids left
		
		do{
										
			//Iterating pEjectionSeat by n through the circle
			for(int i = 0; i < n; i++){
					
					pTail = pTail->pNextSeat;	//advance to next seat
					
			}// end n iterating loop
			
			// If passenger happens to be a human we break out 
			// to for loop and iterate to next n value 
			if ( pTail->pNextSeat->passenger == 'H'){
	
				break; 
			}
			
			// If passenger happens to be an android we call
			// ejectPassenger() to get rid of the non-soul
			if ( pTail->pNextSeat->passenger == 'A') {
				
				ejectPassenger(pTail);		//call to eject
				
				displaySeatedCrew(pTail); //Current printout of remainging 
										  // passengers
				
				remainingAndroids--;	//Decrement number of androids
				//cout << "remainingAndroids is " << remainingAndroids << endl;
			}	
			
		
		} while ( remainingAndroids != 0 ); // Looking for no androids to exist
		
		//If we attain the goal of an all human crew the n value that 
		// made it happen is printed out here.
		if(remainingAndroids == 0){
			printf("\nThe magic number for fooling the androids is :  %d\n", n);
			break;
		}// end of conditional
		
		memoryCleanup(pTail);
	}// end of FOR loop
	
	return 0;

}//end MAIN

/* ---memeoryCleanup---
 * Parameters: 	1). Node* &pTail
 *				
 * Description:	This function deletes previously allocated link list that 
 *              failed to avoid humans to avoid running out of memory on 
 *              large strings. 
 */
void memoryCleanup (Node* &pTail){
	
	Node* pTemp = pTail->pNextSeat;	//pointer pTemp to head
	Node* pNext = pTemp->pNextSeat; //pointer pNext one ahead of head

	// Advance through list deallocating every node
	// This loop leave one unaccounted node
	while ( pTemp != pTail){
		delete(pTemp);
		pTemp = pNext;
		pNext = pTemp->pNextSeat;
	}

	//Cleanup last unaccounted node
	delete(pTail);
	pTail = NULL; //Set pTail to point at the sky

	return;

}//end memoryCleanup()

/* ---ejectPassenger---
 * Parameters: 	1). Node* &pTail
 *				
 * Description:	This function ejects the unfortunate non-soul who happens 
 *              to be an android so that the actual souls on board can be saved.
 *              Using pTail and reflecting changes to main() a pEjectionSeat 
 *              pointer acts like a pHead. Using pEjectionSeat and  pointing 
 *              pNextSeat pTail is linked two ahead closing the gap between
 *              the ejected seat.              
 */
void ejectPassenger(Node* &pTail){
	
	Node* pTemp = pTail;					//Set pTemp to pTail

	Node* pEjectionSeat = pTemp->pNextSeat;	//pointer to unwanted crew member
	
	pTemp->pNextSeat = pEjectionSeat->pNextSeat; //point around unwanted member

	delete pEjectionSeat;					//Sayonara droid

	Node* pWhereWereWe = pTail->pNextSeat;		//Pointer to head
	while(pWhereWereWe->pNextSeat != pTail) {
		pWhereWereWe = pWhereWereWe->pNextSeat;	//Loop once stoping before tail
	}
	pTail = pWhereWereWe; 	//Set pTail one back 

		
}//end ejectPassenger()

/* ---displaySeatCrew---
 * Parameters: 	1). Node* pTail
 *				
 * Description:	This function displays the circular link list with a single
 *              loop around from head to tail. 
 */
void displaySeatedCrew(Node* pTail){
	
	Node* pFirstSeated = pTail->pNextSeat;	//Set pointer to head of list
	do{
		cout << pFirstSeated->passenger;	//Seats Passenger Identity (SPI)
		pFirstSeated = pFirstSeated->pNextSeat;//Adnance to next seat
	}while(pFirstSeated != pTail);			//Loop head up to tail
	
	cout << pTail->passenger; 				//Adjust to print pTail
	cout << "\n";

}//end displaySeatedCrew()

/* ---seatCrew---
 * Parameters: 	1). Node* &pTail
 *				2). char boardingShip[]
 *				3). int crewSize
 * Description:	This function takes the array boardingShip[] created in
 *              recruitCrew() and creates a circular link list of all the 
 *              elements in the array by appending each node to the previous. 
 */
void seatCrew (Node* &pTail, char boardingShip[], int crewSize){

	int i;
	// Create a new node for each passenger 
	// and append to previous passenger.
	for(i = 0; i < crewSize; i++){
		
		Node* pTemp = new Node;				//Allocate space 
		pTemp->passenger = boardingShip[i]; //Identify passenger A or H in seat
		pTemp->pNextSeat = NULL;			
		
		if(pTail != NULL){					//NULL check if full
			pTemp->pNextSeat = pTail->pNextSeat; //Point new node to head
			pTail->pNextSeat = pTemp;		//Advance pTemp to end
		}
		else{
			pTemp->pNextSeat = pTemp;		//If NULL then create pTemp and
		}									// point to itself
		
		pTail = pTemp; 						//Set pTemp to end of list
	}
	
}//end seatCrew()

/* ---recruitCrew---
 * Parameters: 	1). char* &boardingShip
 *				2). int &crewSize
 *				3). int &androidCount
 *				4). int &dynamicCrewSize
 * Description:	This function takes the characters of a .txt file in the 
 *				directory and using fscanf() copies them into an array called
 *				boardingShip[]. The crewSize, androidCount and dynamicCrewSize 
 *              are returned to main().
 */
void recruitCrew (	char* &boardingShip, int &crewSize, int &androidCount, 
					int &dynamicCrewSize ){
	
	int seatIndex = 0;	//Counter for seat position
	androidCount = 0;	//Counter for number of androids
	
	//Object type that identifies a stream including a pointer to its buffer
	FILE *pPassengers;
	pPassengers = fopen("passengers.txt","r"); //return a pointer to FILE
	assert(pPassengers);	//Check for programming errors

	//Copy characters from text file to boardingShip[] using fscanf()
	char userInput = ' ';
	while(fscanf(pPassengers, "%c", &userInput) != EOF){
		if(userInput == 'A' || userInput == 'H') {

			//Tracks number of androids onboard
			if(userInput == 'A') androidCount++;	

			//Allow next passenger onboard
			boardingShip[seatIndex] = userInput;	
			seatIndex++; //Advance counter to next seat

			// If apporaching memory limit allocate more
			if((dynamicCrewSize - 1) == seatIndex){
				
				//Allocate memory for temporary array
				char* pTemp = new char[dynamicCrewSize + 10];
				dynamicCrewSize += 10;	//Increment with each input
				
				//Copy boardingShip array into larger pTemp array
				for(int j = 0; j <= seatIndex; j++) {
					pTemp[j] = boardingShip[j];
				}
				
				//Deallocate boardingShip 
				delete(boardingShip);
				//Reassign boardingShip to pTemp array
				boardingShip = pTemp;
			}//end if()
		}//end if()
	}// end while()
		
	crewSize = seatIndex;	// Lives of board
	
	cout << endl;
	
	fclose(pPassengers); //Disassociate and flush all internal FILE buffers 
	return;
}//End recruitCrew()
