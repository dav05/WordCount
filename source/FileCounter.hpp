//
//  FileCounter.hpp
//  WordCount
//
//  Created by David Miranda.
//

#ifndef FileCounter_hpp
#define FileCounter_hpp

#include <string>
#include "VecCounter.hpp"


// A counter extended with methods to read words from strings and files
class CFileCounter : public CVecCounter
{
    bool isInAlphabet(const char c);
    char makeCharLowerCase(const char c);
public:
    CFileCounter(int n=10) {setMaxWordsToStream(n);};
    void countWordsInString(string StrLine);
    bool countWordsInFile(string StrFileName);
};



#endif /* FileCounter_hpp */
