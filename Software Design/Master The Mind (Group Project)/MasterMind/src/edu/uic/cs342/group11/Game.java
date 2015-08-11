/**
 * 
 * @author George Sullivan
 *
 */

package edu.uic.cs342.group11;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Game implements Subject {
	/* the one and only game instance */
	private static Game uniqueInstance;
	/* fields */
	private Player pHuman;
	private Player pComp;
	private int turnNumber;
	private int gameOver;
	private boolean quit;
	private boolean reset;
	private String turnType;
	private ArrayList<Observer> observers;
	private int results[]  = {0,0};

	//---------------------------------------------------------------Game()---//
	/* constructor */
	private Game() {
		System.out.format("WELCOME TO MASTER THE MIND!!\n");
		observers = new ArrayList<Observer>();
		new Screen(this);
	}//end Game()
	
	//--------------------------------------------------------getInstance()---//
	/*singleton method: getInstance*/
	public static Game getInstance() {
		if (uniqueInstance == null) {
			uniqueInstance = new Game();
		}
		return uniqueInstance;
	}//end getInstance()

	//--------------------------------------------------------------reset()---//
	/* Reset: starts and restarts game by calling initialize and then play */
	public void reset() {
		System.out.format("\nStarting New Game...\n");
		initialize();
		play();
	}//end reset()

	//---------------------------------------------------------initialize()---//
	/* initializes new game */
	private void initialize() {
		//fields
		quit = false;
		reset = false;
		turnNumber = 0;
		gameOver = 0;
		turnType = "human";
		int[] playerSecret = null;
		int[] compSecret = getRandom();
		String compLevel = "";
		for (int i = 0; i < results.length; ++i)
			results[i] = 0;
		
		//gets user input
		Scanner in = new Scanner(System.in);
		String userInput;
		System.out.format("At anytime enter 'r' to restart the game "
		                                                + "or 'q' to quit\n\n");
		
		while (true) {
			userInput = "";
		    while ( userInput.length() != 1) {
				System.out.format("What level of difficulty would you like?"
								+ "\n(Enter 1 for 'easy', 2 for hard):\n");
				
				userInput = in.nextLine();
				char c;
				try{c = userInput.charAt(0);}
				catch(Exception e){continue;}
				
				
				switch(c) {
				case('1'): compLevel = "easy";
					break;
				case('2'): compLevel = "hard";
					break;
				case('r'): reset = true;
					break;
				case('q'): quit = true;
					break;
				default:
				    System.out.println("Please try again...\n");
				    continue;
				}
			}
			
			if (quit) {
				break;
			}
			else if (reset)
				break;
			// if successful break out of loop
			else if (compLevel.length() > 0)
				break;
			else continue;
			
		}

		// enter secret
		while (playerSecret == null && !reset && !quit) {
			System.out.format("\nPlease enter a secret 4 digit number for the "
					      + "computer to guess\n(each digit must be unique):\n");
	
			userInput = in.nextLine();
			char c;
			
			try{c = userInput.charAt(0);}
			catch(Exception e){continue;}
			
			switch(c) {
			case('r'): reset = true;
				break;
			case('q'): quit = true;
				break;
			default:
				break;
			}
			if (quit) {
				break;
			}
			else if (reset)
				break;
			
			//Catch invalid input 
			try{playerSecret = convertNumInput(userInput);}
			catch(Exception e){
			    System.out.println("Oh Oh: Please enter a unique four digit integer\n"
                        + "       Or press \"r\" for reset or \"q\" for quit");
			    continue;
			}
			
			if (playerSecret == null)
				System.out.format("\nThat was not a valid number.\n");
		}
		// initialize players
		if (!reset && !quit) {
			pComp = new Player(compLevel, playerSecret);
			pHuman = new Player("human", compSecret);
		}
	}//end initialize()
	
	//---------------------------------------------------------------play()---//
	public void play() {
		while (true) {
			// checking whether quit or reset got set during initialization
			if (quit || reset)
				break;
			// increment turn number, only on player's turn
			++turnNumber;
			turnType = "human";
			results = pHuman.compareGuess();
			
			if (results[0] == -1) {//reset
				reset = true;
				break;
			}
			else if (results[0] == -2) {//quit
				quit = true;
				break;
			}
			else if (results[1] == 4) { // gameover, player won
				gameOver = 1;
				notifyObservers();
				gameOver();
				break;
			}
			else
				notifyObservers();
			

			// computer turn
			turnType = "computer";
			results = pComp.compareGuess();
			if (results[1] == 4) { // gameover, computer won
				gameOver = 1;
				notifyObservers();
				gameOver();
				break;
			}
			else
				notifyObservers();
	
		}
		// call game over
		if(quit) {
			quit();
			return;
		}
		else
			reset();
	} // end of play()
	
	/* helper functions: getRandom, convertNumInput, quit, gameOver */
	
	//----------------------------------------------------------getRandom()---//
	/* generate secret */
	private int[] getRandom() {
		Random r = new Random();
		ArrayList<Integer> choices = new ArrayList<Integer>();
		int[] numsOut = new int[4];
		for (int i = 0; i < 10; ++i)
			choices.add(i);
		for (int i = 0; i < 4; ++i) {
			int j = r.nextInt(10 - i);
			numsOut[i] = choices.remove(j);
		}
		return numsOut;
	}//end getRandom()

	//----------------------------------------------------convertNumInput()---//
	/* convert to 4 digit number */
	private int[] convertNumInput(String possNums) {
		int[] num = new int[4];
		
		// check length
		if (possNums.length() != 4)
			return null;
		
		// check whether all different
		for (int i = 0; i < 4; ++i) {
			for (int j = i + 1; j < 4; ++j)
				if (possNums.charAt(i) == possNums.charAt(j))
					return null;
			num[i] = Integer.parseInt(String.valueOf(possNums.charAt(i)));}
		
		// convert to int
		if (num.length != 4)
			return null;
		return num;
	}//end convertNumInput()
	
	//---------------------------------------------------------------quit()---//
	/* quit: just prints out goodbye message, work done by just returning */
	private void quit() {
		System.out.format("Thank you for playing Master The Mind\n");
	}//end quit()

	//-----------------------------------------------------------gameOver()---//
	/* game over */
	private void gameOver() {
		Scanner in = new Scanner(System.in);
		String userInput = "";
		
		while (userInput.length() != 1) {
		    System.out.format("Would you like to play again? (y/n)");
			userInput = in.nextLine();
			char c;
			
			//Catch input error
			try{c = userInput.charAt(0);}
			catch(Exception e){continue;}
			
			switch(c) {
			case('y'): reset = true;
				break;
			case('n'): quit = true;
				break;
			case('r'): reset = true;
				break;
			case('q'): quit = true;
				break;
			default:
				userInput = "";
				System.out.format("That's not valid enter y or n \n");
				break;
			}
		}
		return;
	}//end gameOver()

	//---------------------------------------------------registerObserver()---//
	/*  inherited subject methods  */
	@Override
	public void registerObserver(Observer o) {
		observers.add(o);
		return;
	}//end registerObserver()

	//-----------------------------------------------------removeObserver()---//
	@Override
	public void removeObserver(Observer o) {
		observers.remove(o);
		return;
	}//end removeObserver()

	//----------------------------------------------------notifyObservers()---//
	@Override
	public void notifyObservers() {
		for (Observer o : observers)
			o.update(this.turnNumber, this.gameOver, this.turnType, this.results);
	}//end notifyObservers()

}// ***End Game Class ***