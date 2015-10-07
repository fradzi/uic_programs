/**
 * 
 * @author Filip Radzikowski
 *
 **/

package edu.uic.cs342.group11;
import java.util.Random;
import java.util.ArrayList;

public class CompGuessEasy implements GuessBehavior {

    //-----------------------------------------------------------guessAlg()---//
    public int[] guessAlg(GuessLog guessLog) {
        int[] guess = new int[4];
        String temp = new String();
        
        //implementing Fisher-Yates Shuffle to get unique random values
        do{
            int[] randomPool = {0,1,2,3,4,5,6,7,8,9};
            Random rnd = new Random();
            for (int i = randomPool.length-1; i > 0; i--)
            {
              int index = rnd.nextInt(i + 1);
              // Simple swap
              int a = randomPool[index];
              randomPool[index] = randomPool[i];
              randomPool[i] = a;
             
            }
            
            //Select only the first four of shuffle results
            for(int i=0; i<4; i++)
                guess[i] = randomPool[i];
            
            temp = intArrayToString(guess);
            
        } while (containsGuess(guessLog.getHistory(), temp));
       
        System.out.println("\nThe guess from computer is : " 
                                                    + intArrayToString(guess));
        return guess;   
    
    }// end guessAlg()
    
    
    //---------------------------------------------------intArrayToString()---//
    public String intArrayToString(int[] array){    
        //For ease of appending each value from int[]
        StringBuilder strNum = new StringBuilder();
        
        //Append ints to string
        for (int num : array){
             strNum.append(num);
        }
        return strNum.toString();
    }// end intArrayToString()
    
    
    //------------------------------------------------------containsGuess()---//
    public boolean containsGuess(ArrayList <String> array, String key){
        
        return array.contains(key) ? true : false; 
    }// end containsGuess()
}// ***End CompGuessEasy Class ***
