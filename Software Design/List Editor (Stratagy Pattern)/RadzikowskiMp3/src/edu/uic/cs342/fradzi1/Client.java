/* --------------------------------------------------------
 * List Editor
 * 
 * Class: CS 342, Spring 2015. 
 * System: Mac OS X, Version 10.10.1, Eclipse
 * Author:  Filip Radzikowski                     
 * Program: #3 (2.9.15)
 * 
 * Description: This program uses the Strategy Design Pattern. 
 * The program allows an interactive user to perform operations on a 
 * variable-length list. The list editor uses a command line interface, 
 * scanning commands entered by user and responding to the commands until
 * the user exits the system. 
 * 
 * The editor implements the list as a Java ArrayList storing only integer 
 * numbers.The list editor uses different algorithms for sorting the list, 
 * namely SelectionSort, InsertionSort, and QuickSort. The governing 
 * design pattern that is implemented is stratagy. 
 ----------------------------------------------------------*/

package edu.uic.cs342.fradzi1;

import java.io.*;
import java.util.*;

public class Client {

    // Initialize instance of Scanner for user input
    private static Scanner input = new Scanner(System.in);
    // Initialize instance of ListEditor where ArrayList of 
    // integers will be stored and sorted
    private static ListEditor editor = new ListEditor();
    
    /**
     * Main encloses the console features
     *      c   -   clear list
     *      a <num>..<num>   -   append numbers in input order
     *      r <aString>     -   append integers from a file
     *      d   -   display list
     *      s   -   sort list with appropriate sort algorithm
     *      q   -   quit
     * @param args
     */
    
    
    public static void main (String[] args){
    	System.out.format("Valid Commands: \n\tc   -   clear list\n\t"
                + "a <num>..<num>   -   append numbers in input order\n\t"
                + "r <aString>     -   append integers from a file\n\t"
                + "d   -   display list\n\ts   -   sort list with appropriate "
                + "sort algorithm\n\tq   -   quit\n\n");
    	while(true){
           
           System.out.format("Please enter a command:");
           
           String currInput = input.nextLine();//get first string of values
           String []tokens = currInput.split(" "); // break into string tokens
           String currCommand = tokens[0]; // get first char of first string
          
           
           if( currCommand.equalsIgnoreCase("c"))
              editor.clearList(); // clear the list
           else if ( currCommand.equalsIgnoreCase("a"))
               addNum(tokens); // append new values to list
           else if ( currCommand.equalsIgnoreCase("r"))
               readNumFile(tokens); // append file of values
           else if ( currCommand.equalsIgnoreCase("d"))
               editor.displayList(); // display current list
           else if ( currCommand.equalsIgnoreCase("s"))
               editor.performSort(); // sort current list
           else if ( currCommand.equalsIgnoreCase("q")){
               System.out.format("GOOD BYE....\n");
               input.close(); // close Scanner instance
               return;
           }
           else {
               System.out.format("Incorrect input. Please try again by entering "
                    + "valid command.\n"
                    + "Valid Commands: \n\tc   -   clear list\n\t"
                    + "a <num>..<num>   -   append numbers in input order\n\t"
                    + "r <aString>     -   append integers from a file\n\t"
                    + "d   -   display list\n\ts   -   sort list with appropriate "
                    + "sort algorithm\n\tq   -   quit\n\n");     
           }   

       }// end command loop   
    }// end main()
    
    /**
     * Checks for a file using input string file name. If file 
     * exists then values are appended to list.
     * @param tokens
     */
    public static void readNumFile(String[] tokens){
 
        try{
        
            // add additional return to main option 
            File file = new File(tokens[1]);
            Scanner inputFile = new Scanner(file);
     
            String currInput = inputFile.nextLine();//get first string
            String []fileTokens = currInput.split(" ");// create string of tokens
                
                // call addNum to take each integer and append to list
                addNum(fileTokens);
    
            }
            catch(Exception e){
                
                System.out.format("\tFile does not exist. Please try again"
                    + " by using command 'r' \n\tfollowed by file name"
                    + "and don't forget extention .txt.\n");
               
            } 
    }// end readNumFile();
    

    /**
     * Takes each element from string token input and appends to list
     * @param tokens
     */
    public static void addNum(String[] tokens){
        // loop through tokens
        for(int i = tokens.length-1; i > 0 ; --i){
            
            try{
                
                editor.setListElement(Integer.parseInt(tokens[i]));
            }
            catch(Exception e){
                System.out.format("\tInput Error. Please enter command 'a' followed by "
                        + "integer(s).\n");
                //input.nextLine();
            }    
        }// end loop for tokens
           
         
    }// end addNum();   
}// *** end client class ***   
