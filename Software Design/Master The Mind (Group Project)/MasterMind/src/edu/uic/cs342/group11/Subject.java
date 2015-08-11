/**
 * 
 * Author: Luke Wilimitis
 * 
 */

package edu.uic.cs342.group11;
//The 'Subject' interface for which the 'Game' class will implement
public interface Subject{
	// called by 'Game' to store the observer into its list of Observers
	public void registerObserver(Observer observer);
	
	// called by 'Game' to remove the observer from its list of observers
	public void removeObserver(Observer observer);
	
	// called by 'Game' to notify the list of observers by calling each Observer's
	// 'update(...)' method in a loop
	public void notifyObservers();
}// *** end Subject Interface ***


