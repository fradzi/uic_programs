package edu.uic.cs342.fradzi1;

import java.util.ArrayList;
import java.util.Collections;

/**
 * 
 * @author fr
 *
 */
public class SelectionSort implements SortType {
    
    /**
     * Insertion from 
     *      http://www.algolist.net/Algorithms/Sorting/Selection_sort
     */
    @Override
    public void sortList(ArrayList<Integer> currList) {
        
        
      //create an array of ints with currList length
        Integer array[] = new Integer[currList.size()];
        //fill array with values from currList
        array = currList.toArray(array);
        int i, j, minIndex, tmp;
        int n = array.length;
        for (i = 0; i < n - 1; i++) {
            minIndex = i;
            for (j = i + 1; j < n; j++)
                if (array[j] < array[minIndex])
                    minIndex = j;
            if (minIndex != i) {
                tmp = array[i];
                array[i] = array[minIndex];
                array[minIndex] = tmp;
            }
        }
        
        currList.clear(); // clear current list
        // fill currList with new ascending array using container Collections
        Collections.addAll(currList, array); 
    }// end sortList()
    
    
}
