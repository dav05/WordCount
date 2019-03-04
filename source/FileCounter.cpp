//
//  FileCounter.cpp
//  WordCount
//
//  Created by David Miranda.
//

#include <string>
#include <fstream>
#include "FileCounter.hpp"

// counts the words in the file
bool CFileCounter::countWordsInFile(string StrFileName)
{
    std::ifstream File(StrFileName);
    string StrLine;

    
    if (!File.is_open())
    {
        return false; // failed to open the file
    }
    while ( std::getline (File,StrLine) )
    {
        countWordsInString(StrLine); // counts words in the line
    }
    
    File.close();
    return true; // file was read
}

// counts the words in the words in one line (string)
void CFileCounter::countWordsInString(string StrLine)
{
    int i;
    long int nSize = StrLine.size();
    char c; // character
    bool bIsRedingAWord = false; // indicates the state: reading/not_reading
    std::string StrTemp;
    for(i=0; i<nSize; i++) // loop the charaters along the string
    {
        c = StrLine[i];
        if (bIsRedingAWord)
        {
            if (isInAlphabet(c))
            {
                StrTemp += makeCharLowerCase(c);;
            }
            else
            {
                this->addWord(StrTemp)   ; // add a new word to the counter
                bIsRedingAWord = false; // change the state
                
            }
        }else
        {
            if (isInAlphabet(c))
            {
                // start readig a new word
                StrTemp = "";
                StrTemp += makeCharLowerCase(c);
                bIsRedingAWord = true; // change the state
            }
        }
    }
    if (bIsRedingAWord) // if finished the string while still reading a word
    {
        this->addWord(StrTemp); // add a new word to the counter
    }
}

// returns the input character, making it lower case if it is upper case
char CFileCounter::makeCharLowerCase(const char c)
{
    if (c>='A' && c<='Z')
    {
        return c-('A'-'a');
    }
    return c;
};

// returns true if the char is belongs to the alphabet
bool CFileCounter::isInAlphabet(const char c)
{
    return ((c>='a' && c<='z') || (c>='A' && c<='Z'));
    
};
