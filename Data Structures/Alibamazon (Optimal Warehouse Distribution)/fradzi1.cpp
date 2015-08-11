/* -----------------------------------------------------------------------------
 *
 * Program Name : Alibamazon
 * 
 * Class: CS 251, Fall 2014. 
 * System: Mac OS X, Version 10.6.8, Sublime, Terminal
 * Author:  Filip Radzikowski          
 * Lab:     Thursday 11AM           
 * Program: # 4
 *
 *
 * Description: During senior year at UIC with a couple of friends you form a 
 * start-up company called Insite providing business logistics advice.  Insite 
 * has just been hired by Chinese e-commerce giant Alibaba, who wants to compete 
 * with Amazon for items shipped via truck from warehouses directly to customers 
 * in the lower-48 states.  Alibaba wants to limit shipping fuel costs, which 
 * are directly related to the distance from distribution warehouses to other 
 * cities.
 *     
 * To minimize shipping costs how many warehouses should Alibaba build, and 
 * in which cities should they be located?  What is the average shipping 
 * distance over all US cities in each case?  This program will figure this out!
 *
 * 
 -----------------------------------------------------------------------------*/

//----------------------------------------------------PreProcessor Commands---//
#include <iostream>
#include <iomanip>      // for formating
#include <cstdlib>
#include <fstream>      // For file input
#include <cassert> 
#include <cstring>      // for assertions
using namespace std;


#define INSERT_IN_ORDER true    // adjacency lists vertices in ascending order
#define MAX_INT 100007          // Big enough not overflow 

// Adjacencvertex list Node struct, also storing weights
struct Node {
    int vertex;     // Adjacent vertex
    int weight;     // Edge weight, if anvertex
    Node *pLink;    // Next edge in list
};

//---------------------------------------------------------------Prototypes---//
void loadCities(FILE*&, int&, int&, string*&);
void createAdjacencyLists( Node *graph[], int, FILE*&);
void calcAverageDistance( int*, int, int, int**, int&, int*&);
void combinations (int*, int, int, int, int, int**, int&, int*&);
void dijkstraShortestPath( Node *graph[], int, int*, int, int*);
void storeEdgeIntoGraph( Node *graph[], int vertex1, int vertex2, int weight);
void storePairIntoAdjacencyLists( Node *graph[], int vertex1, int vertex2, 
                                    int weight);
void insertIntoListInOrder( Node *pNewNode,Node * &pHead);
void displayAdjacencyLists( Node *graph[], int);
void printIntroDisplay();
void printFormatDisplay();
void printData(int numberOfVertices, int choose_k, int** shortestPathes, 
                string* cityNames);

//---------------------------------------------------------------------main---//
int main()
{
    //print initial information
    printIntroDisplay();

    int choose_k;
    cin>> choose_k;
    cout<<endl;
    //file stream for all distances between adjacent cities
    FILE* cityDistanceFile;
    
    int numberOfVertices, numberOfEdges;
    
    //array of strings of City names
    string* cityNames;                  
    //get number of edges and array string of city names
    loadCities(cityDistanceFile, numberOfVertices, numberOfEdges, cityNames);

    // Graph represented by array of adjacency lists
    Node** graph = new Node*[ numberOfVertices + 1];
    
    // Array of parents representing connection into spanning tree
    int parent[ numberOfVertices + 1];  
    // Min distance found so far for each vertex
    int distance[numberOfVertices + 1];  
    
    //allocate memory for adjacency matrix
    int** shortestPathes = new int *[numberOfVertices+1];
    for( int i = 1; i <= numberOfVertices+1; i++)
        shortestPathes[i] = new int [numberOfVertices+1];

    // Create the graph of cities
    createAdjacencyLists( graph, numberOfVertices, cityDistanceFile);
    
    // Create the min cost spanning tree using Dijkstra's approach
    for(int i = 1; i <= numberOfVertices; i++){
        //from city i get minimal path to every other city
        dijkstraShortestPath(graph, i, parent, numberOfVertices, distance);
        
        for( int j = 1; j <= numberOfVertices; j++){
            //matrix of shortest pathes
            shortestPathes[i][j] = distance[j];    
        }   
    }
    //print infomative display 
    printFormatDisplay();
    //print data of average length for k cities
    printData(numberOfVertices, choose_k, shortestPathes, cityNames);

    return 0;  // Keep C++ happy
}//end main()


/*----------------------------------------------------------------printData---//
 *
 * Parameters:      1). int numberOfVerticies
 *                  2). int choose_k
 *                  3). int** shortestPathes
 *                  4). string* cityNames    
 *
 * Description:     Call combinations to get the lowest average distance for
 *                  k cities. Format the print out so that three columns form
 *                  for k, city average distance, and cities. Adjust for 
 *                  comma placement.
 */
void printData(int numberOfVertices, int choose_k, int** shortestPathes, 
                string* cityNames){

    int name;
    int avgMinDist;
    int cityComb[numberOfVertices + 1];
    int* currentCityComb = new int[numberOfVertices + 1];

    for(int currentK = 1; currentK <= choose_k; currentK++){
        
        avgMinDist = 999999;
        combinations( cityComb, 1, numberOfVertices, 1, currentK, 
                        shortestPathes, avgMinDist, currentCityComb);
        //print formating
        cout.width(10); cout << left << currentK;
        cout.width(10); cout << left << avgMinDist;
        cout.width(10); cout << left << "";

        //loop for k value
        for(int j = 1; j <= currentK; j++){
            //print out the string name of city represented by the value
            //at currentCityComb
            cout << cityNames[currentCityComb[j]];
            //setting ',' in correct location
            if (currentK == 1)
                cout<<"";
            else if( currentK > 1){
                if ( j < currentK )
                    cout << ", ";
                else
                    cout <<"";
            }      
        }
        cout<<endl;
    }
    cout<<endl;
    return;
}// end printData()

/*--------------------------------------------------------printIntroDisplay---//
 *
 * Parameters:      NONE
 *
 * Description:     Print program information for user
 */
void printIntroDisplay( ){
    
    cout << "\nDescription: Insite Warehouse Recommendations to Alibaba\n";

    cout << "\nAuthor: Filip Radzikowski" << endl;
    cout << "Lab: Thurs 11AM" << endl;
    cout << "Program: #4, Alibamazon\n" << endl;

    cout<<"Please enter a k value for the number of cities to consider: ";
    
}//end printIntroDisplay()

/*-----------------------------------------------------printFormatedDisplay---//
 *
 * Parameters:      NONE
 *
 * Description:     Print format to house data printout
 */
void printFormatDisplay(){

    cout.width(10); cout << left << " ";
    cout.width(10); cout << left << "Avg City" << endl;
    cout.width(10); cout << left << "K";
    cout.width(10); cout << left << "Distance";
    cout.width(10); cout << right << "";
    cout << right << "Cities" << endl;

    cout<< "--------------------------------------------------------" << endl;

}// end printFormatDisplay()


/*------------------------------------------------------calcAverageDistance---//
 *
 * Parameters:      1). int cityComb[]
 *                  2). int choose_k
 *                  3). int numCities
 *                  4). int** shortestPathes
 *                  5). int &avgMinDist
 *                  6). int* &currentCityComb  
 *
 * Description:     Taking the current combination of cities, finding the 
 *                  shortest distance of the two to all other cities, summing
 *                  those values and then comparies them to all other 
 *                  combination average distances to find the smallest 
 *                  average distance.
 */
void calcAverageDistance( int cityComb[], int choose_k, int numCities, 
                            int** shortestPathes, int &avgMinDist, 
                            int* &currentCityComb){
    
    int minCombDist = 999999;
    int avgDist = 0;
    
    for(int i = 1; i <= numCities; i++){
        minCombDist = 999999;
        //set shortest distance
        for( int j = 1; j <= choose_k; j++){
            //if current distance smaller than previous set current
            if (shortestPathes[ i][cityComb[j]] < minCombDist)
                minCombDist =  shortestPathes[ i][cityComb[j]];
        }
        //accumulate the minimal cities
        avgDist += minCombDist;    
    }
    //get average by dividing by total cities
    avgDist/=numCities;
    
    /*set smallest average distance from all other combinations 
     and city(ies) that hold the smallest distance and
     return that value */
    if(avgDist < avgMinDist){
        avgMinDist = avgDist;
        for(int i = 1; i <= choose_k; i++){

            currentCityComb[i] = cityComb[i]; 
        }
    }
        
}// end calcAverage


/*-------------------------------------------------------------combinations---//
 *
 * Parameters:      1). int cityComb[]
 *                  2). int start
 *                  3). int numCities
 *                  4). int k
 *                  5). int choose_k
 *                  6). int** shortestPathes
 *                  7). int &avgMinDist
 *                  8). int* &currentCityComb   
 *
 * Description:     Implementing and algorithm for finding all possible 
 *                  combinations from at total numCities number choose_k.
 */
void combinations (int cityComb[], int start, int numCities, int k, 
                    int choose_k, int** shortestPathes, int &avgMinDist,
                    int* &currentCityComb) {
    int i;
     
    /* k here counts through positions in the choose_k-element cityComb.
     * if k > choose_k, then the cityComb is complete and we can use it.
     */
    if (k > choose_k) {
        
        // choose min distance from index city to k cities and save min value
        calcAverageDistance(cityComb, choose_k, numCities, shortestPathes, 
                            avgMinDist, currentCityComb); 
        return;
    }
    
    //for this k'th element of the cityComb,all start..n elements in position
    for (i=start; i<=numCities; i++) {
        
        cityComb[k] = i;
        
        //recursively generate combinations of integers from i+1..n
        combinations (cityComb, i+1, numCities, k+1, choose_k, shortestPathes, 
                        avgMinDist, currentCityComb);
    }
}

/*-----------------------------------------------------dijkstraShortestPath---//
 *
 * Parameters:      1). Node *gragh[]
 *                  2). int start
 *                  3). int parent[]
 *                  4). int numberOfVertices
 *                  5). int* distance   
 *
 * Description:     Implementing the Dijkstra shortest path algorithm to get
 *                  the shortest path from one city to all other cities.
 */
void dijkstraShortestPath(
                               Node *graph[],// Graph represented by adjacency lists
                               int start,// Starting node for building min spanning tree
                               int parent[],// Array of parent pointers, 
                                            // which will represent spanning tree
                               int numberOfVertices,
                               int* distance) // How many vertices are in tree
{
    Node *pTemp;                    // temporary graph node pointer
    bool isInTree[numberOfVertices + 1];    // Marks if vertex is in the tree     
    int currentVertex;              // current vertex to process
    int adjacentVertex;             // Adjacent vertex
    int weight;                     // edge weight
    int shortestNewNodeDistance;    // shortest distance of some new node from current node
    
    // Initialize all vertices as not being in the tree, 
    // having max distance and no parent.
    for (int i=1; i<=numberOfVertices; i++) {
        isInTree[i] = false;
        distance[i] = MAX_INT;
        parent[i] = -1;
    }
    
    // Set values for starting node
    distance[start] = 0;
    currentVertex = start;
    
    // main loop, continued until all vertices are handled
    while (isInTree[ currentVertex] == false) {
        isInTree[ currentVertex] = true;    // Include current vertex into tree
        
        // Examine in turn each edge incident to the current vertex
        pTemp = graph[ currentVertex];       // Get first edge
        while (pTemp != NULL) {
            adjacentVertex = pTemp->vertex;  // Get vertex on othe end of this edge
            weight = pTemp->weight;          // Get weight of this edge
            
            // implement length from the start, not just local length.
            if (distance[ adjacentVertex] > (distance[currentVertex] + weight) ) {
                // Store new lower-cost distance and spanning tree connection point
                distance[ adjacentVertex] = distance[currentVertex] + weight;
                parent[ adjacentVertex] = currentVertex;
            }
            
            pTemp = pTemp->pLink;// advance to next edge incident on currentVertex
        }
        
        // Find next vertex to be processed.  
        // It should be the closest one not already in tree.
        currentVertex = start;
        shortestNewNodeDistance = MAX_INT;    // Initialize to some large number
        // Examine each vertex in graph
        for (int i=1; i<=numberOfVertices; i++) {
            if ((isInTree[i] == false) && (shortestNewNodeDistance > distance[i])) {
                // This ith vertex is not yet in tree and is closest so far
                shortestNewNodeDistance = distance[i];  // set new shortest distance
                currentVertex = i;                      // set new closest vertex
            }
        }//end for( int i...   
    }
    
}//end dijkstraShortestPath(...)


/*-----------------------------------------------------displayAdjacencyList---//
 *
 * Parameters:      1). Node* graph[]
 *                  2). int numberOfVertices
 *
 * Description:     Display adjacency lists associated with each vertex. No use
 *                  in program except for debugging.
 */
void displayAdjacencyLists( Node *graph[], int numberOfVertices)  
{
    Node * pTemp;
    
    cout << endl
    << "   Vertex     Adjacency List \n"
    << "   ------     -------------- \n"
    << endl;
    
    // Display adjacency lists for non-empty rows
    for( int i=1; i<=numberOfVertices; i++) {
        if( graph[ i] != NULL) {
            // Display vertex number
            printf("%7d          ", i);
            
            // Display associated list
            pTemp = graph[ i];
            while( pTemp!=NULL) {
                cout << pTemp->vertex << " ";
                pTemp = pTemp->pLink;
            }//end while( pTemp...
            cout << endl;
            
        }//end if( graph[ i]...
    }//end for( int i...
    
    cout << endl;
}//end displayAdjacencyLists(...)


/*----------------------------------------------------insertIntoListInOrder---//
 *
 * Parameters:      1). Node* pNewNode
 *                  2). Node* &pHead
 *
 * Description:     Store a node into an adjacency list in ascending order.
 *                  This code is only used if  INSERT_IN_ORDER  is set to true 
 *                  at the top of the program, and is then called from function:
 *                  storePairIntoAdjacencyLists(...)
 */
void insertIntoListInOrder(
                           Node *pNewNode,// New Node to be inserted in order into list
                           Node * &pHead) // Head of the list, which may change
{
    Node *pTemp = pHead;
    int newVertex = pNewNode->vertex;
    
    // Check to see if list is empty
    if (pHead == NULL)  {
        // list is empty, so make this the first node
        pHead = pNewNode;
    }
    else  {
        // list is not empty
        pTemp = pHead;
        
        // Iterate through list to find insertion location
        while ( (pTemp->pLink != NULL) && (newVertex > pTemp->pLink->vertex) )  {
            pTemp = pTemp->pLink;        // advance to next node
        }
        
        // See if number goes at front of list
        if ( newVertex < pHead->vertex)  {
            // insert at front of list
            pNewNode->pLink = pHead;
            pHead = pNewNode;
        }
        else {
            // Node goes in the middle or at the end of list
            // Insert after node pointed to by pTemp
            pNewNode->pLink = pTemp->pLink;   // Redundant assignment of NULL
            //    if appending to end of list
            pTemp->pLink = pNewNode;
        }
    } // end else
}//end insertIntoListInOrder(...)


/*-----------------------------------------------storePairIntoAdjacencyList---//
 *
 * Parameters:      1). Node *gragh[]
 *                  2). int vertex1
 *                  3). int vertex2
 *                  4). int weight    
 *
 * Description:     Store vertex1 into the adjacency list for vertex2.
 *                  The macro  INSERT_IN_ORDER  defined at the top of the 
 *                  program determines whether vertices on each adjacency list 
 *                  are stored in LIFO order or in ascending order.
 */
void storePairIntoAdjacencyLists(
                                 Node *graph[],  // Array of adjacency list heads
                                 int vertex1,    // First vertex of edge being added
                                 int vertex2,    // Second vertex of edge being added
                                 int weight)     // Weight of edge being added
{
    // Place vertex 1 in vertex 2's adjacency list
    Node *pTemp = (Node *) malloc( sizeof( Node) );
    pTemp->vertex = vertex1; // Store vertex number
    pTemp->weight = weight;  // Store the weight
    pTemp->pLink = NULL;     // If this will be 1st node, ensure NULL termination
    
    // The macro at the top of the program determines which of the following
    // two get executed.  When first deciphering this program I recommend
    // you use the code in the "else" part.
    if( INSERT_IN_ORDER) {
        // Vertices on adjacency lists are stored in ascending order.
        insertIntoListInOrder( pTemp, graph[ vertex2]);
    }
    else {
        // Vertex vertex1 (now stored in pTemp) is prepended to front of the
        // adjacency list for vertex2, giving LIFO order.
        pTemp->pLink = graph[ vertex2]; // Set link to current head of adj. list
        graph[ vertex2] = pTemp;        // New node becomes new head of list
    }
}//end storePairIntoAdjacencyLists(...)


/*-------------------------------------------------------storeEdgeIntoGraph---//
 *
 * Parameters:      1). Node *gragh[]
 *                  2). int vertex1
 *                  3). int vertex2
 *                  4). int weight    
 *
 * Description:     Store vertex1 into the adjacency list for vertex2, and 
 *                  vertex2 into the adjacency list for vertex1.
 */
void storeEdgeIntoGraph(
                        Node *graph[],   // Array of adjacency list heads
                        int vertex1,     // First vertex of edge being added
                        int vertex2,     // Second vertex of edge being added
                        int weight)      // Weight of edge
{
    
    // Store vertex 1 onto the adjacency list for vertex 2.
    storePairIntoAdjacencyLists( graph, vertex1, vertex2, weight);
    
    // Store vertex 2 onto the adjacency list for vertex 1.
    storePairIntoAdjacencyLists( graph, vertex2, vertex1, weight);
}//end storeEdgeIntoAdjacencyLists(...)


/*-----------------------------------------------------createAdjacencyLists---//
 *
 * Parameters:      1). Node *gragh[]
 *                  2). int numberOfVerticies
 *                  3). FILE* &cityDistanceFile    
 *
 * Description:     Create a graph adjacency list by calling storeEdgeIntoGraph
 *                  function. Using fscanf to input data from file.
 */
void createAdjacencyLists(
                          Node *graph[],    //Array of adjacency lists, 
                                            //representing the graph
                          
                          int numberOfVertices,// Number of vertices in the graph.
                          FILE* &cityDistanceFile)
{
    // Initialize all adjacency lists to NULL
    for (int i = 1; i <= numberOfVertices; i++) {
        graph[i] = NULL;
    }
    
    int vertex1, vertex2, weight;// Vertices and weight for new edge to be added
    while (fscanf(cityDistanceFile, "%d", &vertex1) != EOF){
        
        fscanf(cityDistanceFile, "%d", &vertex2);
        fscanf(cityDistanceFile, "%d", &weight);
        
        // If not quiting (not -1), add vertices to adjacency lists
        if(vertex1 > 0)  {
            
            // Allocate a new node and store vertex 1 onto adj.list for vertex 2
            storeEdgeIntoGraph( graph, vertex1, vertex2, weight);
        }//end if( vertex1...     
    }

    fclose(cityDistanceFile);
    
}//end createAdjacencyLists(...)

/*---------------------------------------------------------------loadCities---//
 *
 * Parameters:      1). FILE* &cityDistanceFile
 *                  2). int &numberOfVerticies
 *                  3). int &numberOfEdges
 *                  4). string* &cityNames     
 *
 * Description:     Using file stream access information and store to 
 *                  correspoting variables and return them.
 */
void loadCities(FILE* &cityDistanceFile, int &numberOfVertices, 
                int &numberOfEdges, string* &cityNames ) {
    
    //Load CityDistancesSanitized.txt file
    cityDistanceFile = fopen("CityDistancesSanitized.txt", "r");
    if( cityDistanceFile == NULL) 
        printf("Error reading CityDistancesSanitized.txt\n");
    
    //get half the number of edges
    fscanf(cityDistanceFile, "%d", &numberOfEdges);
    numberOfEdges = numberOfEdges * 2;      //adjust for remaining edges


    //Input file stream for City Names
    ifstream inStream;                     
    inStream.open( "CityNames.txt");
    assert( ! inStream.fail() );  // make sure file open was OK
    
    // First read the number of cities from the first line, then read
    // the city names.
    inStream >> numberOfVertices;

    //allocate memory for array of strings
    cityNames = new string[numberOfVertices+2]; 
    string name;
    
    int i = 0;
    while( getline(inStream, name) != false){
        //check for no ',' symbol before erasing
        if(name.find(',') != -1){
            name.erase(name.find(','));
        }
        cityNames[ i] = name;
        i++;
    }
    //clear stream
    inStream.close();

    return;
}// end loadCities() 


