//
//  CWord.hpp
//  WordCount
//
//  Created by David Miranda.
//

#ifndef CWord_hpp
#define CWord_hpp

#include <ostream>
#include <string>
using namespace std;

// Represents a word entry, with the number of times that repeats
class CWord
{
    string KeyWord;
    int nCount;
public:
    inline CWord(string KeyWord, int nCount=1) {this->nCount=nCount; this->KeyWord=KeyWord;}; // constructor
    inline bool operator==(const CWord& WordComparing) {return KeyWord == WordComparing.KeyWord;}; // comparison of Words
    inline void incrementCount(int n=1){nCount +=n;}; // increments the word count
    inline int getCount() {return nCount;}; // return the number of counts
    friend std::ostream& operator<<(std::ostream& os, CWord& Word) {os << Word.nCount << "  " << Word.KeyWord; return os;}; // overload stram operator <<
};
#endif /* CWord_hpp */
