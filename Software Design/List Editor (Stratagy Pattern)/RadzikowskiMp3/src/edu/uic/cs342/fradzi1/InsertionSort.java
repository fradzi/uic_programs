package edu.uic.cs342.fradzi1;

import java.util.ArrayList;
import java.util.Collections;

public class InsertionSort implements SortType{
    
    /**
     * Insertion Sort from 
     *          http://java2novice.com/java-interview-programs/insertion-sort/
     */
    @Override
    public void sortList(ArrayList<Integer> currList) {
        //create an array of ints with currList length
        Integer array[] = new Integer[currList.size()];
        //fill array with values from currList
        array = currList.toArray(array);
        
        for(int i = 1; i < array.length; i++){
            
            int temp = array[i];
            int j;
            // choose next element among those still being sorted and slide it
            // into place
            for (j = i - 1; j >= 0 && temp < array[j] ; j--)
                array[j+1] = array[j];
            
            array[j+1] = temp;
            
        }// end insertion sort portion
        
        currList.clear(); // clear current list
        // fill currList with new ascending array using container Collections
        Collections.addAll(currList, array); 
    }// end sortList()
    

}
