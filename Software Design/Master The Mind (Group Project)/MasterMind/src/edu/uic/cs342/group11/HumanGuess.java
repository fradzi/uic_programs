/**
 * 
 * @author Filip Radzikowski
 *
 */
package edu.uic.cs342.group11;

import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class HumanGuess implements GuessBehavior {

    
    //-----------------------------------------------------------guessAlg()---//
    public int[] guessAlg(GuessLog guessLog) {
        
        //Get user guess and error check for size and uniqueness
        String stringGuess = getUserInput();
        
        while(true){
            // check for reset
            if(stringGuess !=null && stringGuess.equalsIgnoreCase("r")){
                int[] r = {-1};
                return r;    
            }
            // check for quit
            else if(stringGuess !=null && stringGuess.equalsIgnoreCase("q") ){ 
                int[] q = {-2};
                return q;
            }
            // Check for four unique int characters  
            else if(stringGuess != null){
                return stringToIntArray(stringGuess);
            }else{
                System.out.println("Oh Oh: Please enter a unique four digit integer\n"
                        + "       Or press \"r\" for reset or \"q\" for quit");
                stringGuess = getUserInput();
            }
   
        }// input loop
            
    }// end guessAlg()
    

    //---------------------------------------------------stringToIntArray()---//
    public int[] stringToIntArray(String guess){
        
        char[] charArray = guess.toCharArray();
        
        int[] intArray = new int[guess.length()];
        
        int i = 0;
        for(char singleChar : charArray){
            intArray[i] = Character.getNumericValue(singleChar);
            i++;
        }
        
        return intArray;
    }// end stringToIntArray()
    

    //-------------------------------------------------------getUserInput()---//
    /**
     * Returns string if exists or null if string pattern does not exist. 
     * Checks if user requests to quit or reset the game.
     * @return
     */
    public String getUserInput(){

        System.out.println("\nWhat's the computer\'s secret number? "
                + "\nPlease enter your guess...");
        Scanner scanner = new Scanner(System.in);
        String userInput = null;
        
        //create the regular expression string. 
        //This will only pick up the first four integers
        String regex = "\\d\\d\\d\\d"; 

        //compile the pattern
        Pattern pattern = Pattern.compile(regex);
        
        //Begin by checking if player wants to reset or quit
        userInput = scanner.nextLine();
        if(userInput.equalsIgnoreCase("r"))
            return userInput;
        else if(userInput.equalsIgnoreCase("q"))
            return userInput;
        else{
            //Create matcher string using userInput
            Matcher matcher = pattern.matcher(userInput);
    
            //Search through string for pattern
            userInput = null;
            while(matcher.find()){
                userInput = matcher.group();
                //System.out.format("%s\n",matcher.group());
            }
            
            //Check string for unique integers and return null for non unique
            if (userInput != null){
               for(int i = 0; i < userInput.length(); i++){
                   for(int j = i+1; j < userInput.length(); j++){
                     if( userInput.charAt(i) == userInput.charAt(j))
                         return null;
                   }
               }
            }
        }// end conditions
        
        //can return string or null if match not found
        return userInput;
        
    }// end getUserInput()
    
}// *** end HumanGuess Class ***
