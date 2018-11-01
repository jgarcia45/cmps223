/* Juan Garcia
 * CMPS 223 / Derrick
 * Lab 7
 * May 14, 2013
 */

#include <iostream>
#include <limits>    // For numeric_limits
using namespace std;

#ifndef ELEMTYPE
#define ELEMTYPE int
#endif

// Binary search is given the array of elements, the element to search for,
// the index of the start of the search and the index of the end of the search.
// It returns the index where the value is found, or -1 if it is not found.
int binarySearch(ELEMTYPE *, ELEMTYPE, int, int);

int main()
{
  ELEMTYPE array[] = { 5, 9, 14, 23, 28, 32, 45, 64, 73, 92 };
  int size = 10;
  int index;
  ELEMTYPE key;

  while(1)
  {
    cout << "Enter element to search for (-1 to exit): ";
    cin >> key;

    if(cin.fail())
    {
      cout << "Invalid datatype. Please try again.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    if(key == -1) break; // exit loop

    // Call binary search originally with the start=0 and the end=size-1
    index = binarySearch(array, key, 0, size-1);

    if(index == -1)
      cout << key << " not found in the array.\n";
    else
      cout << key << " found at index " << index << endl;

    cout << endl;
  }

  return 0;
}

int binarySearch(ELEMTYPE *array, ELEMTYPE elem, int start, int end)
{
    int mid;

    if(start < 0 || end < 0 || end < start)
    {
        return -1;
    }

    if(start >= end)
    {
        if(array[start] == elem)
        {
            return start;
        }
        else
        {
            return -1;
        }
    }

    mid = start + (end - start) / 2;

    if(array[mid] == elem)
    {
        return mid;
    }
    else if(array[mid] < elem)
    {
        return binarySearch(array, elem, mid + 1, end);
    }
    else
    {
        elem < array[mid];

        return binarySearch(array, elem, start, mid - 1);
    }

    return elem || -1;

}
