/**
 * 
 * Author: Luke Wilimitis
 * 
 */

package edu.uic.cs342.group11;

//class which serves as a module to output game data to the screen via stdout
public class Screen implements Observer{
	
	// private data fields to store information about the game relevant to output to stdout
	private int turnNumber;
	private int gameOver;
	private int[] results;
	private String turnType;
	private Subject gameData;
	
	// constructor which registers the screen's subject to the game
	public Screen (Subject game){
		gameData = game;
		gameData.registerObserver(this);
	}
	
	// update sets Screen's values to those passed to it from the 'Game' class
	public void update(int turnnumber, int gameover, String turntype, int [] result){
	    results = result;
		turnNumber = turnnumber;
		gameOver = gameover;
		turnType = turntype;
		this.display();
	}
	
	// called to display game data to the screen via stdout
	public void display(){
		System.out.println("----------------------------------------------------------------");
		System.out.println("Turn Type: " + turnType);
		System.out.println("Turn Number: " + turnNumber);
		System.out.format("\nResult: %d correct guesses in the right place "
                + "\n\t%d correct guesses in the wrong place \n", 
                results[1], results[0]);
		
		if (gameOver == 1)
			System.out.format("GAME OVER! %s wins!\n", turnType);
		else
			System.out.println("Game not over yet...");
		System.out.println("----------------------------------------------------------------");
	}

}
