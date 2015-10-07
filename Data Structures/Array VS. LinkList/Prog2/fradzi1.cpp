/* -----------------------------------------------------------------------------
 *
 * Program Name : Array vs. link list
 * 
 * Class: CS 251, Fall 2014. 
 * System: Mac OS X, Version 10.6.8, Sublime, Terminal
 * Author:  Filip Radzikowski          
 * Lab:     Thursday 11AM           
 * Program: # 2
 *
 *
 *
 * Description: The program consists of creating Bjarne Stroustrup's missing 
 *              graph that compares the performance between an array and a 
 *              link list. There is a clock timer that starts and ends at the
 *              beginning and conclusion of each array and each link list
 *              with incrementing data sizes. To even the playing field the
 *              memory for arrays and the link list are pre allocated for a 
 *              maximum size outside of clock time. The data times are then 
 *              converted to a graph on a separate program.
 *
 * 
 -----------------------------------------------------------------------------*/
//---PreProcessor Commands---//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip> // std::setw
using namespace std;

//---GLOBAL MAX SIZE--//
#define MAX_SIZE 32768

//---Link list Data Structure---//
struct Node {
    int data;
    Node* pNext;
}; 


/* ---displayArray---
 * Parameters:  1). int* pArray
 *              2). int size
 *              
 * Description: Traverses through array and prints out value at
 *              each index.
 */
void displayArray( int *pArray, int size)
{
    // new pointer to head of array
    int *pCurrent = pArray;
    // Traverse through array
    for( int i=0; i<size; i++) {
        cout << *pCurrent << " ";
        pCurrent++;
    }
    printf("\n");
}//end displayArray()


/* ---deleteIndex---
 * Parameters:  1). int* &pArray
 *              2). int index
 *              3). int &size
 *              
 * Description: Traverses through array from index to end of array 
 *              swaping the current index value with following index
 *              value. The size of array is decremented by one. 
 */
void deleteIndex( int* &pArray, int index, int &size ){

    for( int i = index; i < size - 1 ; i++){
        pArray[ i ] = pArray[ i + 1 ];
    }

    // Decrement size
    size--;
}//end deleteIndex


/* ---insertArray---
 * Parameters:  1). int newNumber
 *              2). int* &pArray
 *              3). int &size
 *              
 * Description: Traverses through array and prints out value at
 *              each index.
 */
void insertArray( int newNumber, int * &pArray, int &size)
{
    // Position j is second to last
    int j = size - 1;

    /* Start from second to last element in array 
        and swap if new number is less than value
        before it in the array */
    while( j > 0 && newNumber < pArray[j] ){

        pArray[ j+1 ] = pArray[ j ];
        --j;
    }

    /* If new number is less than first value in 
        array then swap first value into second 
        position and new value into first position
        in the array */ 
    if( j==0 && newNumber < pArray[0]){
        pArray[ 1 ] = pArray[ 0 ];
        pArray[ 0 ] = newNumber;

    }    
    /* If new number is bigger than all values
        in the array then place at the end of 
        the array */
    else{
        pArray[j+1] = newNumber;
    }

    // Increment size 
    size++;
}//end add

/* ---displayList---
 * Parameters:  1). Node* pHead
 *              
 * Description: Traverses though the link list until pHead until NULL and 
 *              prints out each value.
 */
void displayList ( Node* pHead){
    // If list is empty
    if(pHead == NULL){
        cout << "THERE IS NOTHING IN THE LIST" << endl;
    }
    // If list not empty traverse and print
    while (pHead != NULL){
        cout << pHead->data << " ";
        pHead = pHead->pNext;
    }
    cout << endl;
    return;

}// end displayList()


/* ---deleteLinkList---
 * Parameters:  1). Node* &pHead
 *              2). int index
 *              3). int &size
 *              
 * Description: Two conditions are met to delete a node from a link list 
 *              at a given index which is tracked by a counter called size.
 *              The first condition is implemented if the first node is to 
 *              be deleted a and the second is if the remainder of the nodes
 *              are to be deleted.
 */
void deleteLinkList(Node* &pHead, int index, int &size){

    // pTemp points to same node at pHead
    Node* pTemp = pHead;
    // if first node on the list to be deleted
    if ( index == 0){
        pHead = pTemp->pNext;   // advance pHead 
        //delete pTemp;           // deallocate pTemp
        --size;                 // decrement size
        return;
    }

    /* if node other than the first node advance pTemp
        through the list stopping at the node before the 
        one to be deleted */
    int i;
    for( i = 0; i < index - 1; i++){

        pTemp = pTemp->pNext;
    }
    // pNext is the node to be deleted
    Node* pNext = pTemp->pNext; 
    pTemp->pNext = pNext->pNext;
 
    //delete pNext;

    //decrement size
    --size;

}// end deleteLinkList()


/* ---insertLinkList---
 * Parameters:  1). Node* arrayNodes[]
 *              2). Node* &pHead
 *              3). int randomInput
 *              4). int listSize
 *              
 * Description: Four conditions are met to insert a node to a link list.
 *              The first is if the Node is inserted to the front of the 
 *              list. The second is if the node to be inserted falls in the 
 *              middle of list. The third condition is if the node is inserted
 *              at the end of the list. The fourth is if the list is empty. The
 *              randomInput is assigned to the data value of the current node.
 */
void insertLinkList( Node* arrayNodes[], Node* &pHead, 
                        int randomInput, int listSize)
{
    /* Set new value pointer to preallocated memory of arrayNodes
        at index listSize. This will just add new node to the array 
        of nodes */
    Node* pNew = arrayNodes[listSize];
    
    // Declare temp and prev pointers
    Node* pTemp;
    Node* pPrev;

    // Assign new random value to new node 
    pNew->data = randomInput;
   
    // If there aren't any Nodes
    if( pHead == NULL){
        pHead = pNew;
        
    }
    else{
        
        pTemp = pHead;
        
        /* If value less than first value in list then prepend to the
            front of the list */
        if ( randomInput < pTemp->data ){

            pNew->pNext = pTemp;
            pHead = pNew;
        }
        /* If value is greater than fist value in list and less than
            last value in list then advance through list until 
            new value is less than next value in list */ 
        else{
            pPrev = pTemp;          // trailing pointer
            pTemp= pTemp->pNext;    // current pointer
            
            // Advance until value less than next value in list 
            while ( pTemp != NULL && randomInput > pTemp->data){
                pTemp = pTemp->pNext;
                pPrev = pPrev->pNext;

            }
            // If reach the end of list then append to list
            if(pTemp == NULL){
                pPrev->pNext = pNew;

            }
            // If condition met before the end of list
            else{
                pPrev->pNext = pNew;
                pNew->pNext = pTemp;
            }
        }
    }
}// end insertLinkList()

int main()
{
    cout << "\nAuthor: Filip Radzikowski" << endl;
    cout << "Lab: Thurs 11AM" << endl;
    cout << "Program: #2, Arrays VS. LinkLists\n" << endl;

    cout << "The program consists of creating Bjarne Stroustrup's missing" 
         << " graph \nthat compares the performance between an array and a"
         << " link list.\n" << endl; 

    printf("SIZE\t\tARRAY TIME IN SECONDS\tLINKLIST TIME IN SECONDS\n");

    srand((int)time(0));

    int increment;
    for(increment = 2; increment <= MAX_SIZE; increment*=2){

        int randomInput = 0;

        //--- Allocate space for maximum array size ---//
        int *pArray;
        pArray = (int*)malloc(sizeof(int) * MAX_SIZE);
        int arraySize = 0;
        int arrayIndex = 0;

        //--- Allocate space for maximum array of Nodes (1,000,000)---//
        Node** arrayNodes = new Node*[MAX_SIZE];
        
        int index;
        for( index = 0; index < MAX_SIZE; index++){
            arrayNodes[index] = new Node;      //allocate for each node in array
            arrayNodes[index]->pNext = NULL;   //set each Node pointing to NULL
        }

        //Clock time variables
        clock_t begin, end;
        double time_spent;

        //---ARRAY START TIME---//
        begin = clock();

        //---DYNAMIC ARRAY INSERT AND DELETE---/
        int i;
        for(i = 0; i < increment; i++){
            randomInput = rand() % 10000;
            insertArray( randomInput, pArray, arraySize); 
        }
        
        while ( arraySize != 0) {
            arrayIndex = rand() % arraySize;
            // Delete element in array and decrement arraySize
            deleteIndex( pArray, arrayIndex, arraySize);
        }
        
        // end time for array
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%d\t\t%f", increment, time_spent );
        
        
        //---LINKLIST START TIME---//
        begin = clock();
        // pointer to head of link list
        Node* pHead = NULL; 
        int listSize = 0;
        int listIndex = 0;
        
        //---LINKLIST INSERT AND DELETE---// 
        int j = 0;
        for( j = 0 ; j < increment; j++){
            randomInput = rand() % 10000;
            // add it to list
            insertLinkList(arrayNodes, pHead, randomInput, listSize);
            // increment size of list
            listSize++;
        } 
        
        //cout << "the list size is " << listSize << endl;
        
        while ( pHead != NULL){

            listIndex = rand() % listSize; 
            //Delete node in array of nodes and decrement listSize
            deleteLinkList (pHead, listIndex, listSize);
        }
        
        //displayList( pHead);

        // end timer
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("\t\t");
        printf("%f\n", time_spent);

        //Delete each individual node outside clock time
        int t;
        for( t = 0; t < MAX_SIZE; t++){

            delete arrayNodes[t];
        }
        //Delete array of nodes 
        delete arrayNodes;

    }

    return 0;
}



