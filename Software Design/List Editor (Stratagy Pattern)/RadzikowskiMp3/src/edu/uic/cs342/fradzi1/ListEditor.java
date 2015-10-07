package edu.uic.cs342.fradzi1;

import java.util.ArrayList;

/**
 * Concrete class that creates, stores, prints, gets/sets, and sorts
 * ArrayList instance.
 * @author fr
 *
 */
public class ListEditor {
  
    /**
     * Constructor
     */
    public ListEditor() { 
        list = new ArrayList<Integer>();
        this.sortType = new SelectionSort();
        
    }
  
    /**
     * Set the sorting behavior based on list length every time a new element
     * or list of elements is appended to the list. Call instance of SortType
     * interface passing the current list in the parameter to the appropriate 
     * sorting method.
     */
    public void performSort(){
        
        this.setSortType();
        this.sortType.sortList(this.list);
    
    }
  
    /**
     * This method sets the appropriate sort behavior based on list length.
     */
    public void setSortType(){
        int currSize = list.size();
        
        // using selection sort for < 10 elements. Initialize new only if 
        // sortType is not an instance of Selection sort yet.
        if (currSize <= 10 && !(sortType instanceof SelectionSort)){
            
            this.sortType = new SelectionSort();
        }
        // using selection sort for 10 < list length <= 100.Initialize new only if 
        // sortType is not an instance of Insertion sort yet.
        else if ((currSize > 10 && currSize <= 100) && 
                                !(sortType instanceof InsertionSort)){
            
            this.sortType = new InsertionSort();
        }
        // using quick sort for lists longer than 100.Initialize new only if 
        // sortType is not an instance of Quick sort yet.
        else if(currSize > 100 && !(sortType instanceof QuickSort)){ 
            
            this.sortType = new QuickSort();
        }
        
    }
    
    
    /**
     * List getter
     * @return
     */
    public ArrayList<Integer> getList(){
        return list;
    }
    
    /**
     * List setter that appends to the front of list
     * @param newValue
     */
    public void setListElement(int newValue ){
        
        list.add(0, newValue);
    }
    
    /**
     * Clears current list
     */
    public void clearList(){ 
        list.clear();       
    }// end clearList()
    
    /**
     * Displays current list
     */
    public void displayList(){
        
        System.out.println("Current list : " + list.toString());
        
    }// end displayList()
    

    // Fields
    private SortType sortType;
    private ArrayList<Integer> list;
    
}// *** end ListEditor class ***
