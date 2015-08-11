/*
*     CONTAINS GENERIC FUNCTION THAT COMPARES A TXT FILE LIST TO A CHAR ARRAY
* -----------------------------------------------------------------------------
*
*
*/

// --------------------- Pre-Processor Commands --------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

// -------------------------Global Constants -----------------------------------
int const NUM_OF_SPEECHES = 56;
int const MAXIUM_NUM_OF_CHAR_NEEDED_FOR_SPEECH_LIST = 3000;
int const MAXIMUM_NUM_OF_CHAR_IN_SPEECH = 65000;
int const MAXIMUM_NUM_OF_CHAR_IN_DIR_PATH = 150;
int const MAXIMUM_NUM_OF_CHAR_IN_PRESIDENT_NAME = 100;
int const MAXIMUM_NUM_OF_CHAR_IN_DATE = 100;

// ---------------------- Structure Definition ---------------------------------
typedef struct speech_struct{
    char directoryPath[MAXIMUM_NUM_OF_CHAR_IN_DIR_PATH];
    char words[MAXIMUM_NUM_OF_CHAR_IN_SPEECH];
    char president[MAXIMUM_NUM_OF_CHAR_IN_PRESIDENT_NAME];
    char date[MAXIMUM_NUM_OF_CHAR_IN_DATE];
} speech;

// --------------------- Function Declarations ---------------------------------
void displayHeader( );
void displayEnding( );

void loadSpeechList( char*);

void loadSpeech( speech*, char*);
    void setDirectoryPath( speech*, char*);
    void setSpeech( speech*);
    void setDate( speech*);
    void setPresident( speech*);

void analysisOfSpeech( speech*);
    int countPhrasesPresentOnListInSpeech(char* , const char[], int);
        int hasALineBeenLoadedInPhraseToBeSearched( char , char);
        void formatPhraseToBeSearched( char*, char*);
        int countInstancesOfPhraseInSpeech( char*, char*, int);
        int hasALineBeenLoadedInWordsToBeSearched( char , char);
           int isReturnedAddressInTheMiddleOfAnotherWordInSpeech( char*, char*);
        void displayResults( int, int);


// ------------ Main Function --------------
int main() {
    // Variable Declarations;
    char speechList[MAXIUM_NUM_OF_CHAR_NEEDED_FOR_SPEECH_LIST]; // char array

    // used to store the list of all speeches to be analyzed.
    speech spch; // structure used to store a speech

    //Display Header
    displayHeader();

    //Load .txt file containing all the speeches and load it into speechList
    //   array.
    loadSpeechList( speechList);

    //Cycle of load a speech and then analyze a speech / display results;
    for(int i = 0; i <= NUM_OF_SPEECHES; i++) {
        loadSpeech( &spch, speechList); // load a speech
        analysisOfSpeech( &spch); // analyze the loaded speech and display
    } // end of for loop

    //Display Final Message
    displayEnding();
    return 0;
} // end of Main()

//----------------------- Sub-Function Definitions -----------------------------
/* --- displayHeader Function -------
 *  1. Description: Displays CS141 Standard Header, program instructions
 *
 *  2. Parameters: *None*
 *
 */
void displayHeader() {
    //CS141 Standard Header
    printf("Authors:   Filip Radzikowski and Christopher Schultz\n");
    printf("Lab:       Both in Thursday 3pm\n");
    printf("Program:   Generic Function Test File For Analysis This Program\n");

    //Instructions Display
    printf("\nTest File\n \n");

    //Abbreviation Display
    printf("Table Header Abbreviations:\n");
    printf("Prep: Number of Prepositions\n");
    printf("Past: Number of words used referencing the past\n");
    printf("Pres: Number of words used referencing the present\n");
    printf("Futr: Number of words used referencing the future\n");
    printf("God:  Number of words used referencing God\n");
    printf("War:  Number of words used referencing War\n");
    printf("Min:  Number of words used referencing Minorities\n");
    printf("Wlth: Number of words used referencing Wealth\n");
    printf("Rcsn: Number of words used referencing Recession\n");
    printf("\n");

    //Table Header

    printf("Results Table:\n");
    printf("\n");
    printf("________________________________________________________________");
    printf("_____\n");
    printf("|       Presidents     |Prep|Past|Pres|Futr|God |War |Min |Wlth|");
    printf("Rcsn|\n");
    printf("|______________________|____|____|____|____|____|____|____|____|");
    printf("____|\n");
} // end of displayHeader() ;

void displayEnding() {
    printf("_________________________________________________________________");
    printf("____\n");
}//end displayEnding Function


/* --- loadSpeechList Function -------
 * Parameters:   	1). char speechList[]:	list of speech titles as an array
 *
 * Description:		Function opens a list of speeches saved to a single .txt
 *					file using fopen. It check if file exists and returns an
 *					error if it does not. If file does exit then the function
 *					copies the contents of the .txt file into an array called
 *					speechList.
 */
void loadSpeechList( char speechList[]) {
    FILE* speechListFile;
    int i = 0;
    //Load speechlist.txt file
    speechListFile = fopen("datafiles/speechlist.txt", "r");
    if( speechListFile == NULL) printf("Error reading speechlist.txt\n");
    //configure speechList
    while( fscanf(speechListFile, "%c", &speechList[i]) != EOF){
        i++;
    }
    fclose(speechListFile);
    return;
}// end loadSpeechList Function


/* --- loadSpeech Function -------
 * Parameters:   	1). speech* spch:		pointer to structure spch
 *					2). char speechList[]:	list of speech titles as an array
 *
 * Description:		Function calls on four other functions including
 *					setDirectory, setSpeech, setPresident, and setDate. This
 *					is primarily used to consolidate all the speech_struct
 *					functions under into one function.
 */
void loadSpeech( speech* spch, char speechList[]) {

    //Setup Speech Struct Functions
    setDirectoryPath( spch, speechList);
    setSpeech( spch);
    setPresident( spch);
    setDate( spch);

    //Return memory location of speech structure;
    return;
}// end loadSpeech Function


/* --- setDirectoryPath Function -------
 * Parameters:   	1). speech* spch:		pointer to structure spch
 *					2). char speechList[]:	list of speech titles as an array
 *
 * Description:		Function takes contents of speechList[] which includes all
 *					the directories of each speech and breaks them into
 *					individual directories stored as arrays in directoryPath.
 *					The directoryPath is a data member of speech_struct.
 *					With each pass the following directory overwrites the
 *					previous and is stored and passed back to loachSpeech.
 */
void setDirectoryPath( speech* spch, char speechList[]) {
    static int arrayIndex = 0;
    int instanceArrayIndex = 0;


    while(speechList[arrayIndex] != '\n' && speechList[arrayIndex] != EOF){
        spch->directoryPath[instanceArrayIndex] = speechList[arrayIndex];
        instanceArrayIndex++;
        arrayIndex++;

    }
    spch->directoryPath[instanceArrayIndex] = '\0';
    arrayIndex++;
}//end setDirectoryPath


/* --- setSpeech Function -------
 * Parameters:   	1). speech* spch:		pointer to structure spch
 *
 * Description:		Function uses contents of directoryPath which is an array
 *					of the directory to the current speech. It checks if the
 *					directory exists and returns and error if it does not. If
 *					the file does exist then it copies the contents of that
 *					directory, which is the current speech, into an array
 *					called setSpeech. setSpeech is data member of speech_struct.
 *					With each pass the following directory overwrites the
 *					previous and is stored and passed back to loachSpeech.
 */
void setSpeech( speech* spch){
    FILE* speechFile = fopen( spch->directoryPath, "r");
    if(speechFile == NULL) printf("error\n");

    int i = 0;
    while( fscanf(speechFile, "%c", &(spch->words[i])) != EOF){
        spch->words[i] = tolower(spch->words[i]);
        i++;
    }
    spch->words[i] = '\0';
}// end setSpeech Function


/* --- setDate Function -------
 * Parameters:   	1). speech* spch:		pointer to structure spch
 *
 * Description:		Function uses the contents of the array directoryPath where
 *					it finds the date and extracts it and stores the date from
 *					the current directory into an array called date. The setDate
 *					array is a data member of speech_struct.
 *					With each pass the following directory overwrites the
 *					previous and is stored and passed back to loachSpeech.
 */
void setDate( speech* spch) {

    char* address1 = strrchr( spch->directoryPath, '/');
    char* address2 = strchr(spch->directoryPath, '_');
    int distance;
    address1++;
    address2++;

    address2 = strchr(address2, '_');
    address2++;

    address2 = strchr(address2, '_');

    distance = address2 - address1;
    strncpy( spch->date, address1, distance);
    spch->date[distance] = '\0';

}// end setDate Function


/* --- setPresident Function -------
 * Parameters:   	1). speech* spch:		pointer to structure spch
 *
 * Description:		Function uses the contents of the array directoryPath where
 *					it finds the presidents name in the current directory and
 *					extracts it and stores the date into an array called date.
 *					The setpresident array is a data member of speech_struct.
 *					With each pass the following directory overwrites the
 *					previous and is stored and passed back to loachSpeech.
 */
void setPresident( speech* spch){
    char* address1 = strchr(spch->directoryPath, '_');
    char* address2 = strrchr(spch->directoryPath, '.');

    int distance = 0;
    address1++;

    address1 = strchr(address1, '_');
    address1++;

    address1 = strchr(address1, '_');
    address1++;

    distance = address2 - address1;
    strncpy( spch->president, address1, distance);
    spch->president[distance] = '\0';
}// end setPresident Function


/* --- analysisOfSpeech Function -------
 * Parameters:   	1). speech* spch:		pointer to structure spch
 *
 * Description:		Function calls multiple functions which analyze every
 *					speech for specific data and displays the results. Each
 *					function uses the spch structure int their paramaters. Each
 *					function displays its only data which include word count,
 *					sentence count, paragraph count, words per sentence, word
 *					length, first person singular pronoun count, first person
 *					plural pronoun count, and the ration between singular and
 *					plural counts.
 */
void analysisOfSpeech(speech* spch) {

    // int numberOfCalls used to count number of times
    //	analysisOfSpeech function was called
    static int numberOfCalls = 1;

    //Variables used to keep track of data for other analysis files


    // Display President to Indicate what speech is being looked at
    printf("|%2d." , numberOfCalls); // sequential numbering
    printf("%-19.19s|", spch->president); // president
    
    // Counts the number of 		 defined by specific list
    countPhrasesPresentOnListInSpeech( spch->words, 
    		"datafiles/prepositionList.txt", 4);
    countPhrasesPresentOnListInSpeech( spch->words, 
    		"datafiles/pastList.txt", 4);
    countPhrasesPresentOnListInSpeech( spch->words,
    		"datafiles/presentList.txt", 4);
    countPhrasesPresentOnListInSpeech( spch->words, 
    		"datafiles/futureList.txt", 4);
    countPhrasesPresentOnListInSpeech( spch->words, 
    		"datafiles/godList.txt", 4);
    countPhrasesPresentOnListInSpeech( spch->words, 
    		"datafiles/warList.txt", 4);
    countPhrasesPresentOnListInSpeech( spch->words, 
    		"datafiles/minorityList.txt", 4);
    countPhrasesPresentOnListInSpeech( spch->words, 
    		"datafiles/wealthList.txt", 4);
    countPhrasesPresentOnListInSpeech( spch->words, 
    		"datafiles/recessionList.txt", 4);
    printf("\n");

    numberOfCalls++;
}// end analysisOfSpeech Function

/* --- countPhrasesPresentOnListInSpeech Function -------
 * Parameters:    1). char speech[]:		   Presidential Inaugural Speech
 *                2). const char fileName[]:   Directory path to a File that
                                               contains a list word phrases to
 *                                             be search. Formating requirements
 *                                             of the file explained are in the
 *                                             description of  this function.
 *                3). int  precisionOfDisplay: number of digits of results to
 *                                             be display
 *
 * Description:	  Function counts the instances of a list of phrases in an
 *                inaugural speech. The list of phrases need to be in a txt
 *                file for this function to work. The name of the txt name does
 *                not matter because its directory path is an input; however,
 *                the formatting does matter. The following is an example of
 *                a list in a text file that could be used with this function:
 *                  "future
 *                  destiny
 *                  fate
 *                  millennium
 *                  "
 *                Please take note that the end of the txt is a blank line.
 *                This function works by reading in one line of the txt file and
 *                then counts occurrences of the line in the speech. This
 *                function does not reset its instance counter for each phrase.
 *                This function calls several sub-functions to help with the
 *                readability of the code. PrecisionOfDisplay parameter is used
 *                to adjust the digits used for the display of the results.
 *
 *
 *
 */
int countPhrasesPresentOnListInSpeech(char speech[],
                                    const char fileName[],
                                    int precisionOfDisplay) {

    char phraseToBeSearchedFor[100]; // char array used to store phrase to be
                                    //   searched for in speech. Hard Coded
                                    //   to 50 characters for now.
    int instanceCounter = 0;
    // Open list of phrases to be searched
    FILE* fileOfSearchPhrases = fopen( fileName, "r");

    // Error Message If file does not exist
    if(fileOfSearchPhrases == NULL) {
        printf("Error: %s file could not be opened\n", fileName);
    }

    /* Array Index Declaration used to point to locations inside
       phraseToBeSearchedFor array
     */
    int index = 0;

    /*  While loop that loads characters into phraseToBeSearchedFor array. If
        a whole phrase is loaded into phraseToBeSearchedFor array,
     */
    while(fscanf(fileOfSearchPhrases, "%c", &phraseToBeSearchedFor[index]) 
    != EOF){
          /* If statement used to determine if a full phrase has been loaded
             into phraseToBeSearchedFor array or not.
          */
          if(hasALineBeenLoadedInPhraseToBeSearched( 
          									phraseToBeSearchedFor[index], 
          									phraseToBeSearchedFor[index-1])){
            
            // Format phraseToBeSearched into a valid string
            formatPhraseToBeSearched( &phraseToBeSearchedFor[index],
                                    &phraseToBeSearchedFor[index+1]);
            // Count instances of phraseToBeSearched in speech
            instanceCounter = countInstancesOfPhraseInSpeech( speech,
                                                          phraseToBeSearchedFor,
                                                               instanceCounter);
            index = 0; // resets index so a new phrase can be loaded into
                       //   phraseToBeSearchedFor array.

          } else index++; // end of nested if,
    } // end of while loop

    //Display Results
    displayResults( instanceCounter, precisionOfDisplay);
    fclose(fileOfSearchPhrases);
    return instanceCounter;
} //end of countPhrasesPresentOnListInSpeech Function

/* --- hasALineBeenLoadedInPhraseToBeSearched Function -------
 * Parameters:    1). char character1:		   a character in an array
 *                2). char character2:         the character PRECEEDING
                                               character1 in an array.
 *
 * Description:	  Function determines if a whole phrase has been loaded onto the
 *                phraseToBeSearchedFor array  in the
 *                countPhrasesPresentOnListInSpeech function. It does so by
 *                determining if a new line character has been reached. This
 *                function returns 1 (i.e. true) if it determines that an entire
 *                phrase been loaded in phraseToBeSearchedFor. Otherwise, it
 *                returns 0 (i.e. false).
 *
 *
 *
 *
 */
int hasALineBeenLoadedInPhraseToBeSearched( char character1, char character2) {
    if( (character1 == '\n') &&
        character2 >= 'a' && character2 <= 'z'){//this line is needed to prevent
                                                //spaces at the end of a list
                                                //file to cause this function to
                                                //return 1
        return 1;
        } else return 0;
} // end of hasALineBeenLoadedInPhraseToBeSearch function


/* --- formatPhraseToBeSearched Function -------
 * Parameters:    1). char* character1:		   address of a character at the end
 *                                             line of line
 *                2). char* character2:        address of a character PROCEEDING
 *                                             character1.
 *
 * Description:	  Function formats phraseToBeSearchedFor array  in the
 *                countPhrasesPresentOnListInSpeech function into a valid
 *                string.
 *
 *
 */
void formatPhraseToBeSearched( char* characterAddress1, 
								char* characterAddress2){
    *characterAddress1 = ' ';
    *characterAddress2 = '\0';
    return;
} // end of formatPhraseToBeSearched function

/* --- countInstancesOfPhraseInSpeech Function -------
 * Parameters:    1). char* speechAddress:     address of an inaugural speech
 *                2). char* phraseToBeSearch:  address of a phrase to be found
 *                                             in an inaugural speech
 *                3). counterStartingValue:    used to set the value of the
 *                                             counter in this function to some
 *                                             beginning value.
 *
 * Description:	  Function counts the number times the phrase pointed to by
 *                phraseToBeSearch parameter is in the speech pointed to by
 *                speechAddress parameter.
 *
 *
 */
int countInstancesOfPhraseInSpeech( char* speechAddress,
                                       char* phraseToBeSearch,
                                       int counterStartingValue ) {
    char* searchAddress = speechAddress;
    int counter = counterStartingValue;

    while(1){
        //search for the instance of the phrase in the speech
        searchAddress = strstr( searchAddress, phraseToBeSearch);

        /* break loop by returning the value of counter when searching is
           complete
         */
        if(searchAddress == NULL) return counter;
        /* The following else if is used to not count finds when strstr returns
            an address which points to the middle of a word in the speech.
         */
        else if(isReturnedAddressInTheMiddleOfAnotherWordInSpeech(
                                                                speechAddress,
                                                                searchAddress));
        /* If the two previous if-statements did not evaluate true, then an
           instance of search phrase has been found. Therefor, counter is
           incremented
         */
        else counter++;
        // increment search address to prevent repeat finds
        searchAddress++;
    } // end of while loop
} //end of countInstanceOfPhraseInSpeech Function

/* --- isReturnedAddressInTheMiddleOfAnotherWordInSpeech Function -------
 * Parameters:    1). char* speechAddress:         address of an inaugural
 *                                                 speech
 *                2). char* locationInsideSpeech:  address of a location inside
 *                                                 of an inaugural speech.
 *
 * Description:	  Function determines if the address the locationInsideSpeech
 *                parameter points to location in the middle of a word inside
 *                an inaugural speech.  This function returns 1 (i.e. true) if
 *                 locationInsideSpeech parameter points to location inside of
 *                 a word; otherwise, it returns 0 (i.e false).
 */

int isReturnedAddressInTheMiddleOfAnotherWordInSpeech( char* speechAddress,
                                                    char* locationInsideSpeech){
    if( locationInsideSpeech - 1 >= speechAddress && // used to determine if
                                                     // locationInsideSpeech is
                                                     //  not pointing to first
                                                     //  char in speech
        (*(locationInsideSpeech - 1) >='a' &&
         *(locationInsideSpeech - 1) <='z')) { // determine if letter before
                                //  locationInsideSpeech is a letter which
                                // indicates if found something inside another
                                // word.
        return 1;
    } else return 0;
} // end of isReturnedAddressInTheMiddleOfAnotherWordInSpeech function

/* --- isReturnedAddressInTheMiddleOfAnotherWordInSpeech Function -------
 * Parameters:    1). int result:     result to be displayed
 *                2). int precision:  number of digits to be displayed
 *
 * Description:	  Function prints out results. Note: numbers larger than 5 for
 *                the precision parameter have no effect.
 */

void displayResults( int result, int precision){
    //switch case to the precision desired for the display
    switch(precision) {
        case 1:
            printf("%1d|", result);
            return;
        case 2:
            printf("%2d|", result);
            return;
        case 3:
            printf("%3d|", result);
            return;
        case 4:
            printf("%4d|", result);
            return;
        case 5:
            printf("%5d|", result);
            return;
        default:
            printf("%d|", result);
            return;
    } // end of switch
} // end of displayResults function





