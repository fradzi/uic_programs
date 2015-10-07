/* -----------------------------------------------------------------------------
 *
 * Program Name : Trie Harder
 * 
 * Class: CS 251, Fall 2014. 
 * System: Mac OS X, Version 10.6.8, Sublime, Terminal
 * Author:  Filip Radzikowski          
 * Lab:     Thursday 11AM           
 * Program: # 6
 *
 *
 * Description: 
 *      Importing a dictionary of any size this program will create a
 *      rhyming dictionary based on the suffix or word that is input by the 
 *      user. 
 *      
 *      The program will lookup words starting from the end of the word rather 
 *      than from the beginning.  It will make the simplified assumption that 
 *      we will match only the same ending letters (e.g. words rhyming with 
 *      stakes such as cakes, takes) and not words that are plurals (toothaches) 
 *      or other spellings (sheikhs) that have similar sounds.
 *      
 *      To do this program will store the dictionary words in a trie which is a 
 *      special kind of tree data structure that stores each word prefix only 
 *      once.
 *      
 *      The program example will print out: 
 *
 *      Program 6: Trie Harder
 *      Using a trie to find rhyming words.
 *
 *      Author: Filip Radzikowski
 *      Class: CS 251, Fall 2014
 *      System: Sublime on Mac
 *
 *      Options:
 *      f str    Find str
 *      p n      Print next n
 *      a str    Add str
 *      d str    Delete str
 *      ?        Help
 *      x        Exit
 *      Your instruction: x
 *
 *      Exiting Program ...
 -----------------------------------------------------------------------------*/

//---PreProcessor Commands---//
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
using namespace std;

//---NODE Structure for Trie---//
typedef struct NODE* pNODE;
struct NODE{

    char letter;
    bool isWord;
    bool isPrinted;
    pNODE leftMostChild, rightSibling;

} ;

//---Global Variables---//
const int MinLength = 0;      // minimum word size
const int MaxLength = 50;     // maximum word size 

/*-----------------------------------------------------------isInGeneration---//
 *
 * Parameters:      1). NODE* &headSibling
 *                  2). char currentLetter    
 *
 * Description:     Check if current letter is in current generation. Return
 *                  false if it is not in current generation otherwise true.   
 */
bool isInGeneration(NODE* headSibling, char currentLetter){

    while( headSibling->letter != '\0'){
        if( headSibling->letter == currentLetter)
            return true;

        headSibling = headSibling->rightSibling;
    }

    return false;

}// isInGeneration()    


/*-----------------------------------------------------createNewSiblingNode---//
 *
 * Parameters:      1). NODE* &pTemp
 *                  2). NODE* &pParent
 *                  3). char currentLetter    
 *
 * Description:     Create new node when right sibling nodes does not exist 
 *                  for following letter. Prepend new sibling node without 
 *                  putting in order. Point new sibling to ptemp, repoint
 *                  pTemp to new sibling, and repoint parent to pTemp.   
 */

void createNewSiblingNode( NODE* &pTemp, NODE* &pParent, char currentLetter){

    NODE* newSibling = new NODE;
    newSibling->letter = currentLetter;
    newSibling->isWord = false;
    newSibling->leftMostChild = NULL;
    newSibling->rightSibling = NULL;

    newSibling->rightSibling = pTemp;
    pTemp = newSibling;
    pParent->leftMostChild = pTemp;

}// end createNewSiblingNode()


/*-------------------------------------------------------createNewChildNode---//
 *
 * Parameters:      1). NODE* &pTemp
 *                  2). NODE* pParent
 *                  3). char currentLetter    
 *
 * Description:     Create new node when leftChild node does not exist 
 *                  for following letter. Create a new node for new char and
 *                  a new node for the EOL char. Point EOL node back to parent
 *                  which is brough in as and argument.   
 */

void createNewChildNode( NODE* &pTemp, NODE* pParent, char currentLetter){

    // create new NODE for new letter
    NODE* newChild = new NODE;
    newChild->letter = currentLetter;
    newChild->isWord = false;        //set true when final letter in insertToTrie
    newChild->leftMostChild = NULL;
    newChild->rightSibling = NULL;

    //create NULL NODE pointing back to pParent
    NODE* nullSibling = new NODE;
    nullSibling->letter = '\0';
    nullSibling->isWord = false;
    nullSibling->leftMostChild = NULL;
    nullSibling->rightSibling = pParent;

    pTemp = newChild;
    pTemp->rightSibling = nullSibling;
    pParent->leftMostChild = pTemp;

}// end createNewChildNode()


/*-------------------------------------------------------------insertToTrie---//
 *
 * Parameters:      1). NODE* &pHead
 *                  2). char* word    
 *
 * Description:     Called from readDictionary. Each new word is processed 
 *                  through insertToTrie. Each character of each word will be 
 *                  inserted into Trie. If repeating letters are found then 
 *                  pointers are set to existing current letter. If 
 *                  leftMostChild is NULL then createNewChildNode is called to
 *                  insert a new child node along with a null sibling node. If
 *                  leftMostChild exists then function checks to see  if 
 *                  current letter exists in sibling list and if it does not 
 *                  then createNewSiblingNode is called to create new node with 
 *                  current letter and insert prepending into sibling list. At
 *                  the end of word set final letter as beginning of word.     
 */

void insertToTrie( NODE* &pHead, char* word){

    if( pHead == NULL){
        pHead = new NODE;
        pHead->letter = '\0';
        pHead->isWord = false;
        pHead->leftMostChild = NULL;
        pHead->rightSibling = NULL;
    }

    NODE* pTemp = pHead->leftMostChild;
    NODE* pParent = pHead;

    int length = strlen(word);
    for( int i = 0; i < length; i++){

        // is first leftMostChild is NULL
        if (pTemp == NULL){
            // create new node child with null node and insert
            createNewChildNode(pTemp, pParent, word[i]);

        }
        
        // if letter is not in the current generation create new node
        else if( !isInGeneration (pTemp, word[i])){
            // create new node and insert into generation
            createNewSiblingNode( pTemp, pParent, word[i]);

        }
        
        // advance through genereation and set temp and parent to existing node
        else{
            // isInGeneration found char therefore can advance until found
            while( pTemp->letter != word[i]){
                //advance temp to existing sibling letter node
                pTemp = pTemp->rightSibling;           
            } 
        }
        
        // advance parent to existing sibling letter node
        pParent = pTemp;
        pTemp = pTemp->leftMostChild;

    }

    pParent->isWord = true;

}// end insertToTrie()

/*---------------------------------------------------------------checkAlpha---//
 *
 * Parameters:      1). char* word    
 *
 * Description:     Traverse through list and return false if anything other 
 *                  an alhabetical character is present. Otherwise return true.  
 */
bool checkAlpha ( char* word ){

    int i = 0;
    //loops until end word 
    while( word[i] != '\0'){
        // if any char anything other than apha then returns false
        if( !isalpha(word[i]) )
            return false;
        i++;
    }

    return true;

}// end checkAlpha()


/*-------------------------------------------------------convertToLowerCase---//
 *
 * Parameters:      1). char theWord[]
 *                  2). const int size    
 *
 * Description:     Takes input word and converts all characters to lower case.   
 */
void convertToLowerCase ( char theWord[], const int size){
   // convert dictionary word to lower case
   for (int i=0; i<size; i++) {
      theWord[i] = tolower(theWord[i]);
   }

}

/*---------------------------------------------------------------strReverse---//
 *
 * Parameters:      1). char* str   
 *
 * Description:     Reverses the string by changing the orginal string. 
 */
char * strReverse(char* str){
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;

}

/*----------------------------------------------------------------addString---//
 *
 * Parameters:      1). NODE* pHead
 *                  2). char tempString[MaxLength+1]
 *
 * Description:     This function sets to lower case and reverses the input 
 *                  string. The function insertToTrie is then called to insert 
 *                  the new string one character at a time. 
 *                   
 */

void addString(NODE* &pHead, char tempString[MaxLength+1] ){

    char reverseWord[MaxLength+1];
    int  size;                    // string size

    size = strlen( tempString);
    convertToLowerCase( tempString, size);    // convert word to lower case

    // Only store words that aren't too long or too short
    if ( (size <= MaxLength ) && (size >= MinLength) ) {
        strcpy( reverseWord, tempString);
    }
    
    strReverse(reverseWord);

    //insert new string into tree
    insertToTrie( pHead, reverseWord);

}// addString()


/*-----------------------------------------------------------readDictionary---//
 *
 * Parameters:      1). NODE* &pHead   
 *
 * Description:     Read from the dictionary file into an array only keeping 
 *                  words that are the correct length. Calls convertToLowerCase
 *                  and strReverse to make all lower case characters and 
 *                  reverse the original input word. Before this called 
 *                  checkAlpha to discard any words that have anything by 
 *                  aplhabetical characters in them. This string is then sent to 
 *                  be instered into the Trie tree. All changes of pHead are 
 *                  reflected back to main.
 */

void readDictionary( NODE* &pHead ) // number of words in dictionary
{
    
    ifstream inStream;                     // input file stream
    
    char fileName[] = "dictionary.txt"; // Input file name  
    char tempString[MaxLength+1];         // stores a single string
    
    inStream.open( fileName);
    assert( ! inStream.fail() );  // make sure file open was OK

    while ( inStream >> tempString ) {
        
        // get string of all aplha characters
        if( !checkAlpha(tempString))
            continue;
        
        addString( pHead, tempString);
    }

   inStream.close(); // close the input file stream

}// end readDictionary()


/*----------------------------------------depthFirstSearchPhymingWordsCount---//
 *
 * Parameters:      1). NODE* pRoot
 *                  2). NODE* pCurrent
 *                  3). int &totalWordCount
 *
 * Description:     Recursively searches for each word ryhming with input word
 *                  and inclreased the count by one when found. Also set word
 *                  as not being printed yet.
 *                   
 */

void depthFirstSearchRhymingWordsCount( NODE* pRoot, NODE* pCurrent, 
    int &totalWordCount){

    // if current node is word beginning letter
    if( pCurrent->isWord){
        totalWordCount++;                    //word counter
        pCurrent->isPrinted = false;    // set as not being printed  
    }
    
    // advance to the next level in the tree
    if( pCurrent->leftMostChild != NULL )
        depthFirstSearchRhymingWordsCount( pRoot, pCurrent->leftMostChild, 
                                            totalWordCount );
    // advance to the next sibling in the tree 
    if( pCurrent->rightSibling->letter != '\0' && pCurrent != pRoot )
        depthFirstSearchRhymingWordsCount( pRoot, pCurrent->rightSibling, 
                                            totalWordCount );

    return;

}// depthFirstSearchRhymingWords


/*--------------------------------------------------------------displayWord---//
 *
 * Parameters:      1). NODE* pLetter
 *
 * Description:     Travese the generations up to previous level, print out 
 *                  the parent node character and repeat until root is reached.
 */

void displayWord ( NODE* pLetter){

    // traverse generation until EOL char
    while( pLetter->letter != '\0'){
        
        cout << pLetter->letter;
        // traverse levels until root
        while( pLetter->letter != '\0'){
            //advance to next sibling
            pLetter = pLetter->rightSibling;
        }
        // advance to previous level
        pLetter = pLetter->rightSibling;
    }
    //print word on new line     
    cout << endl;
    
}// displayWord()


/*--------------------------------------depthFirstSearchPhymingWordsDisplay---//
 *
 * Parameters:      1). NODE* pRoot
 *                  2). NODE* pCurrent
 *                  3). int printInstructionAmount
 *                  4). int &printCount
 *
 * Description:     Recursively searches for each word ryhming with input word.
 *                  Word count is used in to keep track of words per line for 
 *                  print out. 
 */

void depthFirstSearchRhymingWordsDisplay( NODE* pRoot, NODE* pCurrent, 
                                            int printInstructionAmount,
                                            int &printCount){

    if( printCount == printInstructionAmount)
        return;

    // if current node is word beginning letter
    if( pCurrent->isWord && pCurrent->isPrinted == false){ 
        displayWord( pCurrent);         //display word from current postion
        pCurrent->isPrinted = true;
        printCount++;
    }
    
    // advance to the next level in the tree
    if( pCurrent->leftMostChild != NULL )
        depthFirstSearchRhymingWordsDisplay( pRoot, pCurrent->leftMostChild, 
                                                printInstructionAmount, 
                                                printCount);

    // advance to the next sibling in the tree 
    if( pCurrent->rightSibling->letter != '\0' && pCurrent != pRoot )
        depthFirstSearchRhymingWordsDisplay( pRoot, pCurrent->rightSibling, 
                                                printInstructionAmount, 
                                                printCount);

    return;



}// depthFirstSearchRhymingWords


/*---------------------------------------------------------------findString---//
 *
 * Parameters:      1). NODE* pHead
 *                  2). NODE* &pChild
 *                  3). char* inputWord
 *                  4). int &totalWordCount
 *
 * Description:     Advances down the tree until the final letter of the input
 *                  word or suffix is found. A depth first search is called
 *                  that first counts all the possible words from the final
 *                  letter position. Then another depth first search is called
 *                  which prints all of those words out. 
 */

void findString( NODE* pHead, NODE* &pChild, char* inputWord, bool &isFound){

    pChild = pHead;
    NODE* pSibling = pChild->leftMostChild;

    isFound = true;
    
    int length = strlen(inputWord);
    
    //reverse user input word
    strReverse(inputWord); 
    // loop for every character of the input word
    for( int i = 0; i < length; i++ ){
        //advance until characer found in generation
        while( pSibling->letter != inputWord[i] 
                                    && pSibling->letter != '\0'){

            pSibling = pSibling->rightSibling; //advance sibling 
        }
        
        // if sibling letter is same as input letter advance child and sibling
        if ( pSibling->letter == inputWord[i]){

            pChild = pSibling;
            pSibling = pChild->leftMostChild;
        }
        // if sibling not equal before input suffix reaches end 
        else{

            cout << "The String was not found." << endl;
            isFound = false;
            return;

        }         
    }  
}// end getRymningWords()


/*---------------------------------------------------------------findString---//
 *
 * Parameters:      1). NODE* pHead
 *                  2). char* inputWord
 *                  3). bool &isFound
 *
 * Description:     Advances down the tree until the final letter of the input
 *                  word or string is found. If the string is not found then an
 *                  error is printed out. If found and the string is a word then
 *                  the string is made into a non word. 
 */
void deleteString( NODE* &pHead, char* inputWord, bool &isFound){

    NODE* pChild = pHead;
    NODE* pSibling = pChild->leftMostChild;

    isFound = true;
    
    int length = strlen(inputWord);
    
    //reverse user input word
    strReverse(inputWord); 
    // loop for every character of the input word
    for( int i = 0; i < length; i++ ){
        //advance until characer found in generation
        while( pSibling->letter != inputWord[i] 
                                    && pSibling->letter != '\0'){

            pSibling = pSibling->rightSibling; //advance sibling 
        }
        
        // if sibling letter is same as input letter advance child and sibling
        if ( pSibling->letter == inputWord[i]){

            pChild = pSibling;
            pSibling = pChild->leftMostChild;
            if(i == length-1)
                pChild->isWord = false;
        }
        // if sibling not equal before input suffix reaches end 
        else{

            cout << "The String was not found." << endl;
            isFound = false;
            return;

        }         
    }  
}// end getRymningWords()

/*--------------------------------------------------------printIntroDisplay---//
 *
 * Parameters:      NONE
 *
 * Description:     Print program information for user
 */
void printIntroDisplay( ){
    
    cout << "\nProgram 6: Trie Harder \nUsing a trie to find rhyming words.\n";

    cout << "\nAuthor: Filip Radzikowski" << endl;
    cout << "Lab: Thurs 11AM" << endl;
    cout << "Program: #6, Trie Harder\n" << endl;

}//end printIntroDisplay()


/*----------------------------------------------------------printDirections---//
 *
 * Parameters:      NONE
 *
 * Description:     Print program directions for user
 */
void printDirections( ){

    cout<<"Options:\nf str    Find str\np n      Print next n\n"
        <<"a str    Add str\nd str    Delete str\n?        Help\nx        Exit"
        << "\nYour instruction: ";;
        
}//end printDirections()

/*------------------------------------------------printAdditionalDirections---//
 *
 * Parameters:      NONE
 *
 * Description:     Print additional program directions for user
 */
void printAdditionalDirections( ){

    cout <<"f str    Finds the string that was input" << endl;
    cout <<"         by user and prints out total words" << endl;
    cout <<"         produced by this string.\n" << endl;
    cout <<"p n      Prints next n words. n is set by the" <<endl;
    cout <<"         user and will only continue printing" << endl;
    cout <<"         while there are still words to print" <<endl;
    cout <<"         without repetition.\n" << endl;
    cout <<"a str    Adds user's string to existing tree." <<endl;
    cout <<"         Create new nodes where letter does " <<endl;
    cout <<"         exist.\n"<<endl;
    cout <<"d str    Deletes the user's string so that it" <<endl;
    cout <<"         no longer exists as a words in the " <<endl;
    cout <<"         tree.\n" <<endl;
    cout <<"?        Prints out detailed directions menu.\n" <<endl;
    cout <<"x        Deallocated all nodes from tree and " <<endl;
    cout <<"         exits program.\n"<< endl;
    cout << "\nYour instruction: ";;
        
}//end printAddictionalDirections()

/*---------------------------------------------------------------deleteTree---//
 *
 * Parameters:      NODE* &pRoot
 *
 * Description:     Recusively delete all nodes that were allocated for tree.
 */
void deleteTree ( NODE* &pRoot){


    // advance to the next level in the tree
    if( pRoot->leftMostChild != NULL )
        deleteTree( pRoot->leftMostChild );
    
    // advance to the next sibling in the tree 
    if( pRoot->rightSibling != NULL && pRoot->rightSibling->letter != '\0' )
        deleteTree( pRoot->rightSibling );
    
    // delete extra node which contains the '\0' character
    else if( pRoot->rightSibling != NULL && pRoot->rightSibling->letter == '\0')
        delete pRoot->rightSibling;

    // deallocate root node
    delete pRoot;

    return;


}// deleteTree()

int main()
{
    
    // declare root of tree
    NODE* pHead = NULL;
    NODE* pChild = NULL;            // for depthfirst search
    NODE* pCurrent = NULL;
    char instruction;
    bool isFound;
    char inputWord[MaxLength+1];        // user word array
    int totalWordCount = 0;             // total number of rhyme words
    int printCount = 0;             // # of words printed thus far from string
    int printInstructionAmount = 0;     // # of words to be printed by user
    int printInstructionCountTracker = 0;   // tallies # of print requests
    
    //print information display and prompt user for input
    printIntroDisplay();
    
    //Reads in words from file and insert into Trie Tree
    readDictionary(pHead);

    do{
        printDirections();
        cin >> instruction;
        instruction = tolower(instruction); 
        cout << endl;

        // instruction for finding string
        if (instruction == 'f'){
            //input user word or suffix
            cin >> inputWord;
            findString(pHead, pChild, inputWord, isFound);
            // if input string was not found then cycle through
            if(!isFound)
                continue;
            
            printInstructionCountTracker = 0;
            totalWordCount = 0;
            pCurrent = pChild;      // keep track of where you are in recursion

            /*search recursively for number of rhyming words and sets words as
            not being printed*/
            depthFirstSearchRhymingWordsCount( pChild, pCurrent, totalWordCount);
            cout << "Found " << totalWordCount << " words.\n" << endl;

        }
        // instruction to print n rhyming words
        else if (instruction == 'p'){
            
            // n words to print
            cin >> printInstructionAmount;

            // check for =< n request
            if( printInstructionAmount > totalWordCount){
                cout << "Error: n is greater than total number" <<endl;
                cout << "       of available words. Try again.\n" << endl;
                continue;
            }
            
            // check if total found equals total requested by user
            if( printInstructionCountTracker >= totalWordCount){
                cout << "Error:  All words have been printed.\n" << endl;
                continue;
            }

            // search recursively for each word that rhymes with input n times
            depthFirstSearchRhymingWordsDisplay( pChild, pCurrent, 
                                                    printInstructionAmount, 
                                                    printCount);

            //sum total words printed by user
            printInstructionCountTracker += printInstructionAmount;    
            printCount = 0;                 //reset words printed from string 
            cout<<endl;   
                
        }
        // instruction to add a word
        else if (instruction == 'a'){

            cin >> inputWord;
            addString( pHead, inputWord );

        }
        // instruction to delete a word
        else if (instruction == 'd'){
            cin >> inputWord;
            deleteString( pHead, inputWord, isFound);

        }
        // instruction for menu information
        else if (instruction == '?'){
            printAdditionalDirections();
        }
        // instruction to exit program
        else if (instruction == 'x'){
            cout << "Exiting Program ...\n" << endl;
            
            // recursively deallocate Trie Tree
            deleteTree(pHead);

            break;
        }
            
        else{
            cout << "Incorrect instruction. Please try again."<<endl;
    
        }

    } while (true);

    
    return 0;
}



