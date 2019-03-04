//
//  main.cpp
//  WordCount
//
//  Created by David Miranda.
//

#include <iostream>
#include <string>
#include <vector>
#include "DirectoryCounter.hpp"

using namespace std;


// parse the arguments of the main function if an error occour then return false, otherwise return true
// the syntax should be: WordCount -d {directory_path_name} [-o {output_file_path_name}]
bool parseArguments(int argc, const char * argv[], string& StringWorkingDirectory, string& StringOutputFile, bool& bOutputToFile)
{
    int i;
    bool bReadDirectory=false;
    string StringArgument;
    StringOutputFile = "";
    for(i=0; i<argc-1; i++)
    {
        StringArgument = argv[i];
        if (StringArgument == "-d")
        {
            StringWorkingDirectory = argv[i+1];
            bReadDirectory = true;
        }
        else if (StringArgument == "-o")
        {
            StringOutputFile = argv[i+1];
            bOutputToFile = true;
        }
    }
    return bReadDirectory; // returns error if the directory wsa not passed as input
}


int main(int argc, const char * argv[])
{
    
    string StringOutputFile;
    string StringWorkingDirectory;
    bool bOutputToFile;
    
    cout<<"\n";
    cout<<"Word counting utility. Counts the frequency of words in files.\n";
    cout<<"--------------------------------------------------------------\n";
    
    // try to parse the arguments passed to the program
    if (!parseArguments(argc, argv, StringWorkingDirectory, StringOutputFile, bOutputToFile))
    {
        cout << "Invalid syntax. To ouptut to the screen use:\n";
        cout << " WordCount -d full_path_of_directory \n";
        cout << " or to report to an output file:\n";
        cout << " WordCount -d full_path_of_directory -o full_path_of_report_file\n";
        cout << "\n\n";
        return 0;
    }
    
    // creates a DirectoryCounter object
    CDirectoryCounter DirectoryCounter(StringWorkingDirectory, 10);
    
    if (bOutputToFile)
    {
        // output to a file
        bool bFileCreated = DirectoryCounter.writeReportToFile(StringOutputFile);
        if (!bFileCreated)
        {
            cout<< "Failed to open output file.\n\n";
            return 0;
        }
        else
        {
            cout<< "Report file written to:\n";
            cout<< StringOutputFile<<"\n";
            cout<< "\n\n";
            return 0;
        }
    }
    else
    {
        // output to the terminal
        cout<<DirectoryCounter<<"\n\n";
    }
    return 0;
}
