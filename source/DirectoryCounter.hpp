//
//  DirectoryCounter.hpp
//  WordCount
//
//  Created by David Miranda.
//

#ifndef DirectoryCounter_hpp
#define DirectoryCounter_hpp

#include <vector>
#include "FileCounter.hpp"
#include "VecCounter.hpp"

// A class to count the number of diferent words within a folder
class CDirectoryCounter
{
    string StringDirectoryName; // name of the directory
    bool bOpenedDirectory=0; // flag indicating if was able to open the dirctory
    int nSize=0; // number of opened files
    vector<string> VectorFileNames; // files in the directory
    vector<bool> VectorFlagAbleToRead; // flags indicating if was able to read each file or not
    vector<CFileCounter> VectorFileCounter; // counters for the files
    CVecCounter TotalDirectoryCounter; // general counter accumulating the overall results
    
    bool readFileNames(); // reads the names of the files in the directory
    void countWordsOfAllFiles(); // count the words in all the files
public:
    // Contructs the directory counter given the directory path name
    CDirectoryCounter(const string StringDirectoryName, unsigned int nMaxWordsToStream=10);
    bool writeReportToFile(const string StringPathName); // writes a report to a file, returns true in case of success
    
    friend std::ostream& operator<<(std::ostream& os, CDirectoryCounter& DirectoryCounter); // overload the stream operator <<
};

#endif /* DirectoryCounter_hpp */
