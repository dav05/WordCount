//
//  DirectoryCounter.cpp
//  WordCount
//
//  Created by David Miranda.
//

#include "DirectoryCounter.hpp"
#include <dirent.h>
#include <vector>
#include <fstream>
#include <iostream>

// Contructs the directory counter given the directory path name
//  and optionaly nMaxWordsToStream the maximum number of words to stream,
// 10 is the default if that argument is not given
CDirectoryCounter::CDirectoryCounter(const string StringDirectoryName, unsigned int nMaxWordsToStream)
{
    this->StringDirectoryName = StringDirectoryName;
    bOpenedDirectory = readFileNames(); // read the directory and file names
    if (bOpenedDirectory) // if the directory opened successfully
    {
        nSize = (int) this->VectorFileNames.size();
        
        // reserve space for the vectors: VectorFlagAbleToRead and VectorFileCounter
        VectorFlagAbleToRead.reserve(nSize);
        VectorFileCounter.reserve(nSize);
        CFileCounter TemporaryFileCounter(nMaxWordsToStream); // Temporary empty counter
        
        // poplulates the vectors: VectorFlagAbleToRead and VectorFileCounter
        for(int i=0; i<nSize; i++)
        {
            // populate with false
            VectorFlagAbleToRead.push_back(false);
            // populate with the temporary counter
            VectorFileCounter.push_back(TemporaryFileCounter);
        }
        
        // construct the Total counter by copy to have the same nMaxWordsToStream
        TotalDirectoryCounter = TemporaryFileCounter;
        
        // count words in all the files
        countWordsOfAllFiles();
    }
};



// reads the names of the files in the directory.
// Returns true in case of success, and false in case of error.
bool CDirectoryCounter::readFileNames()
{
    DIR *pDirectory;
    struct dirent *pDirectoryEntry;
    if ((pDirectory = opendir (StringDirectoryName.c_str())) != NULL)
    {
        // print all the files and directories within the directory
        while ((pDirectoryEntry = readdir (pDirectory)) != NULL)
        {
            // verify if the file is a regular file and not for instance a directory
            if (pDirectoryEntry->d_type == DT_REG)
            {
                // insert a new file name entry into the set
                this->VectorFileNames.push_back(pDirectoryEntry->d_name);
            }
        }
        closedir (pDirectory);
        return true; // Opened the directory with success
    }
    
    return false; // Error: could not open directory
}

// count the words in all the files
void CDirectoryCounter::countWordsOfAllFiles()
{
    int i;
    bool bFlagAbleToRead;
    string str;
    for(i=0; i<nSize; i++)
    {
        // concatenates strings to produce the full path name
        str = this->StringDirectoryName+"/"+VectorFileNames[i];
        bFlagAbleToRead = VectorFileCounter[i].countWordsInFile(str); // cont the words in the file
        VectorFlagAbleToRead[i] = bFlagAbleToRead;
        if (bFlagAbleToRead)
        {
            // merge with the counter of the directory to obtain the totals
            TotalDirectoryCounter.mergeAnotherVecCounter(VectorFileCounter[i]);
        }
    }
}

// writes a report to a file, returns true in case of success
bool CDirectoryCounter::writeReportToFile(const string StringPathName)
{
    fstream file; //object of fstream class
    //openes file StringPathName in write mode
    file.open(StringPathName,ios::out);
    
    if(!file)
    {
        return false; // error creating file
    }
    
    file<<(*this); // writes the counter to the output file
    file.close();
    return true;
}

// overload the stream operator << in order to output to text
std::ostream& operator<<(std::ostream& os, CDirectoryCounter& DirectoryCounter)
{
    os << "Counter for words in the directory (all files):\n";
    os << DirectoryCounter.StringDirectoryName << "\n";
    if (!DirectoryCounter.bOpenedDirectory)
    {
        os << "Failed to open the directory.\n\n";
        return os;
    }
    os << "=======================================\n";
    os << DirectoryCounter.TotalDirectoryCounter;
    os << "---------------------------------------\n\n";
    
    
    // report on all the files
    for(int i=0; i<DirectoryCounter.nSize; i++)
    {
        os << "Counter for words in the file : "<< DirectoryCounter.VectorFileNames[i]<<"\n";
        if (!DirectoryCounter.VectorFlagAbleToRead[i])
        {
            os << "Failed to open the file.\n\n";
        }
        else
        {
            os << "=======================================\n";
            os << DirectoryCounter.VectorFileCounter[i];
            os << "---------------------------------------\n\n";
        }
    }
    return os;
};
