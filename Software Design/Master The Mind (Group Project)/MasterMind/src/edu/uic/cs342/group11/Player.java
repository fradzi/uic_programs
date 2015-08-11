/**
 * 
 * @author Filip Radzikowski
 *
 */

package edu.uic.cs342.group11;

import java.util.ArrayList;

public class Player {

    public GuessLog guessLog;
    private GuessBehavior guessBehavior;
    private int[] secretCode;
    private int[] playerGuess;
  //-------------------------------------------------------Player Constructor---//
    public  Player(String playerType, int[] key) {
        
        // Constructor set guessBehavior and initializes secretCode
        if(playerType.equalsIgnoreCase("human"))
            this.guessBehavior = new HumanGuess();
        else if (playerType.equalsIgnoreCase("easy"))
            this.guessBehavior = new CompGuessEasy();
        else if (playerType.equalsIgnoreCase("hard"))
            this.guessBehavior = new CompGuessHard();
        
        //Initialize secret code
        secretCode = new int[key.length];
        System.arraycopy(key, 0, secretCode,0, key.length);
        
        guessLog = new GuessLog();
    }// end Player Constructor

    
    //--------------------------------------------------------playerGuess()---//
    /**
     * @return
     */
    public void setPlayerGuess() {
        
        playerGuess = this.guessBehavior.guessAlg(guessLog);
        
    }//end setPlayerGuess()
    
    
    //-----------------------------------------------------getPlayerGuess()---//
    /**
     * Returns int[].
     * @return
     */
    public int[] getPlayerGuess(){
        
        return playerGuess;
        
    }// end getPlayerGuess()
    
    
    //---------------------------------------------------getPlayerHistory()---//
    /**
     * ArrayList passed so as not to lose an leading 0 value in playerGuess
     * @return
     */
    public ArrayList<String> getPlayerHistory(){
        return guessLog.getHistory();
    }//end getPlayerHistory()
    
    
    //-------------------------------------------------------compareGuess()---//
    /**
     * Compares the secretCode with the player guess and returns an int[]
     * with the number of correct int / incorrect location value in the 
     * first index [0] and correct int / correct location in second index [1]
     * @param currGuess
     * @param key
     */
    public int[] compareGuess() {
       // Stores right num in result[0] and right num right place in result[1]
       int[] results = {0, 0};
       
       //Promt the player for their guess
       setPlayerGuess();
       
       //Check whether reset or quit was called
       if(playerGuess[0] == -1 || playerGuess[0] == -2){
           return playerGuess;
       }
       
       //record player guess
       guessLog.setGuessHistory(getPlayerGuess());
       
       //Check for RNRP and RNWP
       for (int i=0; i < playerGuess.length; i++){
           if(playerGuess[i] == secretCode[i]){
               results[1]++;
           }else{
               for(int j=0; j < secretCode.length; j++){
                   if(playerGuess[i] == secretCode[j])
                       results[0]++;
               }   
           }  
       }
       
       //Update log 
       guessLog.setRNWP(results[0]);
       guessLog.setRNRP(results[1]);
       
       return results; 
    }//end compareGuess()

}// *** end Player Class ***