package edu.uic.cs342.fradzi1;

import java.util.ArrayList;
import java.util.Collections;

/**
 * 
 * Using parts of code from
 *      http://gauss.ececs.uc.edu/Courses/C321/html/quicksort.java.html
 *       and Dale Reed
 *
 */
public class QuickSort implements SortType {

    /**
     * Swap two array elements. Used in sorting.
     * @param A
     * @param x
     * @param y
     */
    public void swap(Integer A[], int x, int y) {
        int temp = A[x];
        A[x] = A[y];
        A[y] = temp;
    }

    /**
     * Partition array on a pivot so that all elements < pivot are to the left 
     * of the pivot position, and all elements >= pivot are to the right of the
     * pivot position.
     * 
     * Select the pivot as the middle array element, then store it out of the 
     * way at the far right end of the array, swapping it back into the middle
     *  at the end of the partitioning.
     * @param A
     * @param l
     * @param r
     * @return
     */
    public int partition(Integer A[], int l, int r) {
        
        // to find index of middle by avoiding integer overflow
        int pivotIndex = l + (r-l)/2;
        int pivotValue = A[pivotIndex];
        int storeIndex = l;
        // Number of elements in subarray is : right - left+1
        
        /**
         * Put pivot value out of the way at far right of array, to be swapped 
         * back into place at the end.
         */
        swap( A, pivotIndex, r);
        
        
        /**
         * Go through the current range being considered of array elements,
         * moving each element into the left part of the partition if its value
         * is less than the pivot value.
         */
        for (int i=l; i<r ; i++){
            if(A[i] < pivotValue){
                swap(A, i ,storeIndex);
                storeIndex++;
            }
        }
        /**
         * storeIndex is now the index of the location just to the right of the
         * last element that is < pivot, so its value >= pivot. Swap the pivot 
         * back to this spot.
         */
        swap(A, storeIndex, r); // move pivot to its final place
        return storeIndex;
    }// end partition()
    
    
    public void Quicksort(Integer A[], int f, int l)
    {
       if (f >= l) return;
       // Partition around a pivot and return index of pivot
       int pivot_index = partition(A, f, l);
       // recursively sort the portion to the left of the pivot
       Quicksort(A, f, pivot_index);
       // recursively sort the portion to the RIGHT of the pivot
       Quicksort(A, pivot_index+1, l);
    
    }// end Quicksort()
    
 
    @Override
    public void sortList(ArrayList<Integer> currList) {
        
        Integer array[] = new Integer[currList.size()];
        array = currList.toArray(array);
        
        //Call Quicksort function using array, left start and right end
        Quicksort(array, 0, array.length-1);

        currList.clear(); // clear current list
        // fill currList with new ascending array using container Collections
        Collections.addAll(currList, array); 
    }

}
