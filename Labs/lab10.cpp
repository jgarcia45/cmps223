/* Juan Garcia
 * CMPS 223 / Derrick
 * Lab 10
 * June 4, 2013
 */

#include <iostream>
#include <fstream>
#include "quicksort.cpp"

using namespace std;

int main()
{
    int count = 0, i = 0, num;
    int SIZE;
    int arr[300];
    char iFile[256];

    cout << "Enter a File: ";
    cin.getline(iFile, 256);
    ifstream inFile(iFile);

    while(inFile >> num)
    {
        arr[i++] = num;
        count++;
        SIZE++;
    }

    quicksort(arr, 0, count - 1);

    inFile.close();

    return 0;
}
