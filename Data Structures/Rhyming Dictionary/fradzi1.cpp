/* -----------------------------------------------------------------------------
 *
 * Program Name : Rhymes With
 * 
 * Class: CS 251, Fall 2014. 
 * System: Mac OS X, Version 10.6.8, Sublime, Terminal
 * Author:  Filip Radzikowski          
 * Lab:     Thursday 11AM           
 * Program: # 5
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
 *      Program 5: Rhymes With
 *      Using a trie to find rhyming words.
 *
 *      Author: Filip Radzikowski
 *      Class: CS 251, Fall 2014
 *      System: Sublime on Mac
 *
 *      Enter the suffix to find rhyming words: akes
 *      Found 3 words which are:
 *      rakes sakes takes
 *
 *      Exiting program...
 * 
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

    for( int i = 0; i < strlen(word); i++){

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
void convertToLowerCase ( char theWord[], const int size)
{
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

char * strReverse(char* str)
{
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
    char reverseWord[MaxLength+1];
    int  size;                            // string size
   
    inStream.open( fileName);
    assert( ! inStream.fail() );  // make sure file open was OK

    //cout << "\n Reading dictionary file from " << fileName << "\n";   
    
    //currentRow = 0;
    while ( inStream >> tempString ) {
        
        // get string of all aplha characters
        if( !checkAlpha(tempString))
            continue;

        size = strlen( tempString);
        convertToLowerCase( tempString, size);    // convert word to lower case

        // Only store words that aren't too long or too short
        if ( (size <= MaxLength ) && (size >= MinLength) ) {
            strcpy( reverseWord, tempString);
        }
        
        strReverse(reverseWord);

        //cout << reverseWord << endl;
        insertToTrie( pHead, reverseWord);

    }

   inStream.close(); // close the input file stream

}// end readDictionary()


/*----------------------------------------depthFirstSearchPhymingWordsCount---//
 *
 * Parameters:      1). NODE* pRoot
 *                  2). NODE* pCurrent
 *                  3). int &wordCount
 *
 * Description:     Recursively searches for each word ryhming with input word.
 *                   
 */

void depthFirstSearchRhymingWordsCount( NODE* pRoot, NODE* pCurrent, 
                                        int &wordCount){

    // if current node is word beginning letter
    if( pCurrent->isWord)
        wordCount++;            //word counter
    
    // advance to the next level in the tree
    if( pCurrent->leftMostChild != NULL )
        depthFirstSearchRhymingWordsCount( pRoot, pCurrent->leftMostChild, 
                                            wordCount );
    // advance to the next sibling in the tree 
    if( pCurrent->rightSibling->letter != '\0' && pCurrent != pRoot )
        depthFirstSearchRhymingWordsCount( pRoot, pCurrent->rightSibling, 
                                            wordCount );

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
    //space between words
    cout << " ";
    
}// displayWord()


/*--------------------------------------depthFirstSearchPhymingWordsDisplay---//
 *
 * Parameters:      1). NODE* pRoot
 *                  2). NODE* pCurrent
 *                  3). int &wordCount
 *
 * Description:     Recursively searches for each word ryhming with input word.
 *                  Word count is used in to keep track of words per line for 
 *                  print out. 
 */

void depthFirstSearchRhymingWordsDisplay( NODE* pRoot, NODE* pCurrent, 
                                            int &wordCount){

    // if current node is word beginning letter
    if( pCurrent->isWord){ 
        displayWord( pCurrent);         //display word from current postion
        if (wordCount++ % 7 == 6)       //allow 7 words a line
            cout << endl;
    }
    
    // advance to the next level in the tree
    if( pCurrent->leftMostChild != NULL )
        depthFirstSearchRhymingWordsDisplay( pRoot, pCurrent->leftMostChild, 
                                                wordCount);

    // advance to the next sibling in the tree 
    if( pCurrent->rightSibling->letter != '\0' && pCurrent != pRoot )
        depthFirstSearchRhymingWordsDisplay( pRoot, pCurrent->rightSibling, 
                                                wordCount);

    return;



}// depthFirstSearchRhymingWords


/*--------------------------------------------------------printRhymingWords---//
 *
 * Parameters:      1). NODE* pHead
 *                  2). char* inputWord
 *                  3). int &wordCount
 *
 * Description:     Advances down the tree until the final letter of the input
 *                  word or suffix is found. A depth first search is called
 *                  that first counts all the possible words from the final
 *                  letter position. Then another depth first search is called
 *                  which prints all of those words out. 
 */

void printRhymingWords( NODE* pHead, char* inputWord, int &wordCount){

    NODE* pChild = pHead;
    NODE* pSibling = pChild->leftMostChild;

    int length = strlen(inputWord);
    
    //reverse user input word
    strReverse(inputWord); 
    // loop for every character of the word
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
        else return;

    }
    //search recursively for number of rhyming words
    depthFirstSearchRhymingWordsCount( pChild, pChild, wordCount );
    cout << "Found " << wordCount << " words which are: " << endl;  
    cout << endl;   

    // reset count to have correct words per line 
    wordCount = 0;
    // search recursively for each word that rhymes with input
    depthFirstSearchRhymingWordsDisplay( pChild, pChild, wordCount);
    cout << endl;
    
}// end getRymningWords()


/*--------------------------------------------------------printIntroDisplay---//
 *
 * Parameters:      NONE
 *
 * Description:     Print program information for user
 */
void printIntoDisplay( ){
    
    cout << "\nProgram 5: Rhymes With \nUsing a trie to find rhyming words.\n";

    cout << "\nAuthor: Filip Radzikowski" << endl;
    cout << "Lab: Thurs 11AM" << endl;
    cout << "Program: #5, Trie Rhymes\n" << endl;

    cout<<"Enter the suffix to find rhyming words: ";
    
}//end printIntroDisplay()




int main()
{
    //print information display and prompt user for input
    printIntoDisplay();

    // declare root of tree
    NODE* pHead = NULL;
    char inputWord[MaxLength+1];    // user word array
    int wordCount = 0;              // number of rhyme words
    
    //Reads in words from file and insert into Trie Tree
    readDictionary(pHead);

    //input user word or suffix
    cin >> inputWord;

    /*print out number of words rhyming with user input 
      and all such words */
    printRhymingWords( pHead, inputWord, wordCount);

    cout << endl;
    cout << "Exiting Program..." << endl;

    return 0;
}






