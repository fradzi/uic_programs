package edu.uic.cs342.fradzi1;

import java.util.ArrayList;

/**
 * SortType interface for concrete subclasses
 *      SelectionSort
 *      InsertionSort
 *      QuickSort
 *      
 * @author fr
 *
 */
public interface SortType {
    // all sorting classes implement sortList() method
    public void sortList(ArrayList<Integer> currList);

}// *** end SortType interface ***
