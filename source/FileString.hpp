//
//  CFileString.hpp
//  WordCount
//
//  Created by David Miranda on 25/02/2019.
//  Copyright © 2019 Scientific Software. All rights reserved.
//

#ifndef FileString_hpp
#define FileString_hpp

#include <stdio.h>
#include <string.h>


// Class containing a string obtained from a text files
// with utilities to read words from the string sequantialy
// count words and make them lower case
class CFileString
{
private:
    char* szString;
    int nCurrentReadingPosition; // position of the string that is being read
    int nErrorFlag; // set to 1 if an error ocours opening the file
    int nTotalOfWords; // total number of words
    int nMaxWordSize; // --- TODO: get the maximum size a word
    
    // returns true if it the char c is a character from the alphabet
    inline bool isChar(char& c) { return ((c>='a' && c<='z') || (c>='A' && c<='Z')); }
    
    void countTotalOfWords(void); // counts the total number of words
    void convertAllToLowerCase(void); // convert all the caracters A-Z into lower case
public:
     CFileString(const char* szPathName, int& nErrorFlag); // szPathName is the path name of the file to read, and nErrorFlag is an error flag to get as output
    ~CFileString(void);
    
    int getNextWord(char* szNextWord=NULL); // returns 0 in case of success, and 1 in case the document reach to the end, szNextWord==NULL will not save the word in any string
    inline int getTotalOfWords(void) {return nTotalOfWords;} ; // returns the total number of words
};





#endif /* FileString_hpp */
