/**
 * 
 * Author: Luke Wilimitis
 * 
 */

package edu.uic.cs342.group11;

// interface to be implemented by the 'Screen' class to use the Observer Design Pattern
interface Observer {
		
	// updates private data members of the Observer aka the Screen
	public void update(int turnNumber, int gameOver, String turnType, int [] results);
}// *** end Observer interface ***