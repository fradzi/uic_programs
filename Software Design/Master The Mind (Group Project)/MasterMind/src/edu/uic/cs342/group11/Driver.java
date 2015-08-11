/**
 * 
 * MASTER THE MIND
 * 
 * U. of Illinois, Chicago
 * Group Project 1b
 * Group 11 :
 *          George Sullivan
 *          Luke Wilimitis
 *          Filip Radzikowski
 *          Andriy Serafyn
 *          Kirk Rehal
 *          
 *  Our Client is Buzz Gameplayer, the chief technology officer of the software
 *  firm Computer Games 'R' Us. Buzz sees a valuable market opportunity to 
 *  develop new games downloadable as apps for a variety of platformes 
 *  ranging from desktop and laptop computers, to smart phones and tablets.
 *  
 *  Prospective customers are the users of these platforms: Gameplayers's 
 *  marketing department believes that the popular Mastermind game will 
 *  be a runaway success. 
 *  
 *  In this game, each player sets up a sequence of four decimal digits, where 
 *  each digit is not repeated. For instance, 2015 is a legal sequence, and 
 *  2012 is not because the digit 2 is repeated. The two players take turns
 *  guessing the sequence of digits of their opponent's guess by specifying 
 *  the number of digits that were successfully guessed i the correct position 
 *  and the number of digits that were successfully guessed but in the wrong 
 *  positions. Thus, if a player's chosen number is 2015 and the opponent 
 *  guesses 1089, the opponent would be told that one digit was guessed 
 *  correctly in the correct position( i.e. , the 0), and another digit was 
 *  guessed in the wrong position, (i.e., the 1). 
 *  
 *  In this application a human has the choice to play and easy version of the 
 *  computer opponent or a hard version of the computer openent. 
 *
 */

package edu.uic.cs342.group11;

public class Driver {
	//---------------------------------------------------------------main()---//
	/* starts the game */
	public static void main(String[] args) {
		Game g = Game.getInstance();
		g.reset();
	}//end main()
}// ***End Driver Class ***
