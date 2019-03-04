//
//  FileString.cpp
//  WordCount
//
//  Created by David Miranda on 25/02/2019.
//  Copyright © 2019 Scientific Software. All rights reserved.
//

#include "FileString.hpp"
#include <stdio.h>
#include <stdlib.h>

/*
char* szString;
int nCurrentReadingPosition;
 */

// opens the file, allocates a string, reads the file to the string and closes the file
CFileString::CFileString(const char* szPathName, int& nErrorFlag) // szPathName is the path name of the file to read
{
    long int i;
    long int nSizeString; // Size of the string to allocate
    FILE* file = fopen(szPathName, "r");
    if (file==NULL)
    {
        // Error opening the file
        nErrorFlag = 1;
        // allocate the string with only one character, in order to avoid errors using the remaining methods
        nSizeString=1;
        nCurrentReadingPosition = 0;
        szString = (char*) malloc(nSizeString * sizeof(char));
        szString[0] = 0;
        nTotalOfWords = 0;
        return;
    }
    fseek(file, 0L, SEEK_END); // go to the end of the file
    nSizeString = ftell(file); // get the position at the end of the file
    rewind(file); // go back to the begining of the file
    
    // allocate memory for the string
    szString = (char*) malloc(nSizeString * sizeof(char));
    
    // load the string character by character
    for(i=0;i<nSizeString; i++)
    {
        szString[i] = fgetc(file);
    }
    szString[i] = 0; // make the string null terminated
    
    fclose(file); // close the file
    
    convertAllToLowerCase(); // convert all the string to lower case
    
    nCurrentReadingPosition = 0;
    countTotalOfWords(); // count the words in the string
    nErrorFlag = 0;
}

CFileString::~CFileString(void)
{
    // TODO: need to verify if the memory was allocated in first place
    free(szString); // Free memory if memory, was reserved before
}

// if szNextWord is a null pointer, than reads but does not save the word
int CFileString::getNextWord(char* szNextWord) // returns 0 in case of sucess, and 1 in case the document reach to the end
{
    int nNextWordPosition = 0;
    char c = szString[nCurrentReadingPosition];
    
    // read until it reaches the first character of a word or the end of the string
    while (!isChar(c) && c!=0)
    {
        nCurrentReadingPosition++;
        c = szString[nCurrentReadingPosition];
    }
    
    // read until it reaches an non alphabetic character
    while (isChar(c))
    {
        if (szNextWord!=NULL) // dont save the word if the null pointer was passed
        {
            szNextWord[nNextWordPosition] = c;
            nNextWordPosition++;
        }
        nCurrentReadingPosition++;
        c = szString[nCurrentReadingPosition];
    }
    if (szNextWord!=NULL) // dont save the word if the null pointer was passed
    {
        szNextWord[nNextWordPosition] = 0;
    }
    if (c==0)
    {
        return 1;
    }
    return 0;
}

void CFileString::countTotalOfWords(void) // counts the total number of words
{
    nTotalOfWords = 0;
    // save the current reading position and go to the begining of the string
    int nTemp = nCurrentReadingPosition;
    nCurrentReadingPosition = 0;
    
    // keep reading words until the end of the string, NULL means that the word will not be saved
    while (getNextWord(NULL)==0)
    {
        nTotalOfWords++;
    }
    nCurrentReadingPosition = nTemp; // store the reading position before calling the function
}

void CFileString::convertAllToLowerCase(void) // convert all the caracters A-Z into lower case
{
    const char cDeltaUpperLower = 'A'-'a';
    long int nPosition = 0;
    while (szString[nPosition]!=0)
    {
        if (szString[nPosition] >= 'A' && szString[nPosition] <= 'Z')
        {
            szString[nPosition] -= cDeltaUpperLower;
        }
        nPosition++;
    }
}

