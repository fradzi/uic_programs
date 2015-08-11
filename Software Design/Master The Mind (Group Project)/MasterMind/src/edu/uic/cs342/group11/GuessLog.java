/**
 * 
 * @author Filip Radzikowski
 *
 */

package edu.uic.cs342.group11;

import java.util.ArrayList;
import java.util.Arrays;

public class GuessLog {

    //Fields
    private ArrayList<Integer> RNRP = new ArrayList<Integer>();
    private ArrayList<Integer> RNWP = new ArrayList<Integer>();
    private ArrayList<String> guessHistory = new ArrayList<String>();
    
    //----------------------------------------------------------Constructor---//
    public GuessLog(){};
    
    //----------------------------------------------------setGuessHistory()---//
    public void setGuessHistory(int[] currGuess){

        guessHistory.add(Arrays.toString(currGuess));
    
    }// end setGuessHistory()
    
    //------------------------------------------------------------setRNRP()---//
    public void setRNRP(int rnrp){
        
        RNRP.add(rnrp);
        
    }// end setRNRP()
    
    //------------------------------------------------------------setRNWP()---//
    public void setRNWP(int rnwp){
        
        RNWP.add(rnwp);
        
    }// end setRNWP()
    
    //------------------------------------------------------------getRNRP()---//
    public int[] getRNRP() {
        
        return listToArray(RNRP);
    }//end getRNRP()
    
    //------------------------------------------------------------getRNWP()---//
    public int[] getRNWP() {
        
        return listToArray(RNWP);
    }//end getRNWP()
    
    //---------------------------------------------------------getHistory()---//
    public ArrayList<String> getHistory() {
        
        return guessHistory;
    }//end getHistory()
    
    //--------------------------------------------------------listToArray()---//
    public int[] listToArray(ArrayList<Integer> list ){
        
        int i = 0;
        int[] intArray = new int[list.size()];
  
        for(int x : list){
            intArray[i] = x;
            i++;
        }
        
        return intArray;
    }//end listToArray()

}// ***End  GuessLog Class ***