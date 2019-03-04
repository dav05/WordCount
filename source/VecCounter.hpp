//
//  VecCounter.hpp
//  WordCount
//
//  Created by David Miranda.
//

#ifndef VecCounter_hpp
#define VecCounter_hpp

#include <vector>
#include <ostream>
#include "Word.hpp"

// The standard vector class enchiched with some feautures for counting
class CVecCounter : vector<CWord>
{
protected:
    unsigned int nMaxWordsToStream;
    int getNumberOfWordsToPresent();
public:
    CVecCounter(int n=10) {setMaxWordsToStream(n);};
    int findWord(const CWord& Word);
    
    // set maximum number of words to stream, set to 0 for maximum, 10 is the default
    void setMaxWordsToStream(unsigned int n) {nMaxWordsToStream = n;};
    
    void addWord(CWord Word);
    void addWord(const string& strKeyWord);
    void SortByNumberCounts();
    void mergeAnotherVecCounter(const CVecCounter& VecCounter);
    friend std::ostream& operator<<(std::ostream& os, CVecCounter& VecCounter);
};

#endif /* VecCounter_hpp */
