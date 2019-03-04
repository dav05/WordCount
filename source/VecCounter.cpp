//
//  VecCounter.cpp
//  WordCount
//
//  Created by David Miranda.
//

#include "VecCounter.hpp"

// Finds a keyword in the vector and returns the index, if not found returns -1
int CVecCounter::findWord(const CWord& Word)
{
    size_type nSize = this->size();
    for(int i=0; i<nSize; i++)
    {
        if ((*this)[i] == Word)
        {
            return i; // keyword found
        }
    }
    return -1; // keyword not found
}

// Adds a new word to the vector if does not exists, otherwise updates the counter
void CVecCounter::addWord(CWord Word)
{
    int nPosition = findWord(Word);
    
    if (nPosition < 0) // word not found
    {
        this->push_back(Word); // keyword not found, insert new keyword at the end
    }
    else
    {
        (*this)[nPosition].incrementCount(Word.getCount()); // keyword found, increment the count
    }
}

// Implementation of addWordd with string as input
void CVecCounter::addWord(const string& strKeyWord)
{
    CWord Word(strKeyWord);
    addWord(Word);
}

// Sorts the words the words with more counts from higher to lower count
// only a number of words enough to reported is sorted
void CVecCounter::SortByNumberCounts()
{
    int i,j,k;
    int iMax = getNumberOfWordsToPresent();
    int nSize = (int) size();
    CWord TempWord("");
    for(i=0;i<iMax;i++) // loop only until get the words that will be reported
    {
        k = (*this)[i].getCount();
        for(j=i+1;j<nSize;j++) // compare with all the other words
        {
            if ((*this)[j].getCount() > k)
            {
                TempWord = (*this)[i];
                (*this)[i] = (*this)[j];
                (*this)[j] = TempWord;
                k = (*this)[i].getCount();
            }
        }
    }
}

// Merge another VecCounter, to the current one
void CVecCounter::mergeAnotherVecCounter(const CVecCounter& VecCounter)
{
    int nSize = (int) VecCounter.size();
    for(int i=0; i<nSize; i++)
    {
        this->addWord(VecCounter[i]);
    }
}

// gets the number of words to present in report,
// when nMaxWordsToStream==0 is the the size of the structure
// when nMaxWordsToStream!=0 is the minimum between the size of the set and the limit nMaxWordsToStream
int CVecCounter::getNumberOfWordsToPresent()
{
    int nSize = (int) size();
    int iMax = nSize; // maximum number of words to stream
    
    // limit the maximum of words to stream
    if ((nMaxWordsToStream !=0) && (nSize > nMaxWordsToStream))
    {
        iMax = nMaxWordsToStream;
    }
    return iMax;
}

// overload the stream operator << to stream the object easily
std::ostream& operator<<(std::ostream& os, CVecCounter& VecCounter)
{
    int iMax = VecCounter.getNumberOfWordsToPresent();
    
    // sort the Counter before streaming
    VecCounter.SortByNumberCounts();
    
    for(int i=0; i<iMax; i++)
    {
            // stream the instance i
            os << "["<< i+1 << "] " <<VecCounter[i] << "\n";
    }
    return os;
};



