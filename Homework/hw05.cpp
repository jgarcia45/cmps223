/* Juan Garcia
 * CMPS 223 / Derrick
 * Homework 5
 * May 7, 2013
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

void reverseFile(ifstream &, ofstream &);

int main()
{
    ifstream inFile;
    char iFile[256];

    cout << "Enter a File: ";
    cin.getline(iFile, 256);
    if(cin.fail())
    {
        cout << "The File Name is incorrect..." << endl;
        return 1;
    }

    inFile.open(iFile);
    if(inFile.fail())
    {
        cout << "File input could not open..." << endl;
        return 1;
    }

    ofstream outFile;
    char oFile[260];

    strcpy(oFile, iFile);
    strcat(oFile, ".out");

    outFile.open(oFile);
    if(outFile.fail())
    {
        cout << "File output could not open..." << endl;
        return 1;
    }

    reverseFile(inFile, outFile);
    cout << "The File was a success! It Reversed!" << endl;

    inFile.close();
    outFile.close();

    return 0;
}

void reverseFile(ifstream &inFile, ofstream &outFile)
{
    char c;
    if(inFile.eof())
    {
        return;
    }
    inFile.get(c);
    reverseFile(inFile, outFile);
    outFile << c;

    return;
}
