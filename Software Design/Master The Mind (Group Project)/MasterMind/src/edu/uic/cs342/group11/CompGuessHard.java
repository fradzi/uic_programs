/**
 * 
 * @author George Sullivan
 *
 **/

package edu.uic.cs342.group11;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class CompGuessHard implements GuessBehavior {
	private ArrayList<int[]> guessPool = new ArrayList<int[]>();//need to reset in new game
	
	
	//------------------------------------------------------CompGuessHard()---//
	/* Initializes a pool of all 4 digit numbers without duplicates
	 * each represented as int-array*/
	public CompGuessHard() {
		
		for (int i = 0; i < 10000; ++i)
		{
			boolean add = true;
			int[] nextNum = {(i/1000) % 10, (i/100) % 10, (i/10) % 10, i % 10};
			for (int j = 0; j < 4; ++j)
				for (int k = j + 1; k < 4; ++k)
					if (nextNum[j] == nextNum[k])
						add = false;
			if (add)
				guessPool.add(nextNum);
			
		}
	}//end CompGuessHard()

	//-----------------------------------------------------------guessAlg()---//
	@Override
	public int[] guessAlg(GuessLog guessLog) {
		// Looks at results of last guess
		ArrayList<String> guessHistory = guessLog.getHistory();
		
		// If guessHistory is not empty, uses it to eliminate pool members
		if (!guessHistory.isEmpty()) {
			//Gets information about the last guess
			int histLength = guessHistory.size();
			int rnwp = guessLog.getRNWP()[histLength-1];
			int rnrp = guessLog.getRNRP()[histLength-1];
			int[] lastGuessResults = {rnwp, rnrp};
			int[] lastGuess = arrayFromHistString(guessHistory.get(histLength-1));
			ArrayList<int[]> toRemove = new ArrayList<int[]>();
			
			/* Removes elements that don't have the correct number
			*  of right place/other right from last guess*/
			for (int[] poolElt : guessPool) {
				if (!Arrays.equals(compareGuess(lastGuess, poolElt), lastGuessResults))
					toRemove.add(poolElt);}
			
			for (int[] l : toRemove) {
				guessPool.remove(l);
			}
		}
		
		// Makes new guess
		Random r = new Random();
		int g = r.nextInt(guessPool.size());
		int[] compGuess = guessPool.get(g);
		
		System.out.format("The guess from computer is: %s\n", intArrayToString(compGuess));
		return compGuess;
	}//end guessAlg()
	
	//---------------------------------------------------intArrayToString()---//
	public String intArrayToString(int[] array){    
        //For ease of appending each value from int[]
        StringBuilder strNum = new StringBuilder();
        
        //Append ints to string
        for (int num : array){
             strNum.append(num);
        }
        return strNum.toString();
    }//end  intArrayToString()
	

	//-------------------------------------------------------compareGuess()---//
	/* core of Filip's compareGuess fn, gives number in right place
	 * and the number of other correct numbers from two int arrays */
	private int[] compareGuess(int[] lastGuess, int[] poolElt) {
		int[] results = {0,0};
		
		for (int i=0; i < poolElt.length; i++){
			if(poolElt[i] == lastGuess[i]){
				results[1]++;
			}
			else{
				for(int j=0; j < lastGuess.length; j++){
					if(poolElt[i] == lastGuess[j])
						results[0]++;
				}   
			}  
		}
		return results;
	}//end compareGuess()
	
	
	//------------------------------------------------arrayFromHistString()---//
	/* Converts string of form '[i,j,k,l]' (as stored in guessHistory)
	 * to the int-array it represents */
	private int[] arrayFromHistString(String s) {
		int[] result = new int[4];
		String trimmed = s.substring(1, s.length() - 1);
		String[] sList = trimmed.split(", ");
		
		for (int i = 0; i < sList.length; ++i)
			result[i] = Integer.parseInt(sList[i]);
		return result;
	}//end arrayFromHistString()
}// ***End CompGuessHard Class ***
