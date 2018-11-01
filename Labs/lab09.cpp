/* Juan Garcia
 * CMPS 223 / Derrick
 * Lab 9
 * May 28, 2013
 */

#include <iostream>
#include <limits>    // For numeric_limits
using namespace std;

#ifndef ELEMTYPE
#define ELEMTYPE int
#endif

// Use selection sort to sort the given array.
// Given: Pointer to array, size of array (int)
void selectionSort(ELEMTYPE *, int);

// Use insertion sort to sort the given array.
// Given: Pointer to array, size of array (int)
void insertionSort(ELEMTYPE *, int);

int main()
{
  ELEMTYPE *array1 = NULL, *array2 = NULL;
  int size = 0;

  // Note: While this lab reads the array from the keyboard, you may also
  // update this code to read from a file if you wish (e.g. take your file
  // input loop from the homework assignment and put it here). Make sure to
  // keep TWO arrays of the data (which are copies of one another), so you
  // can be sure that both sorting algorithms are working correctly.
  do
  {
    cout << "Enter the size of the array: ";
    cin >> size;

    if(cin.fail())
    {
      cout << "Invalid entry. Must enter an integer. Please try again.\n";
      size = 0;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if(size < 2)
    {
      cout << "Size must be greater than 2 for sorting.\n";
    }
  } while(size < 2);

  try
  {
    array1 = new ELEMTYPE[size];
    array2 = new ELEMTYPE[size];
  }
  catch(bad_alloc)
  {
    cout << "Allocation failure. Run again with a smaller array size.\n";
    return 1;
  }

  // Read in the data into array1, then copy the value from array1 into array2
  // so that array1 and array2 are copies of one another by the end of this loop
  for(int i = 0; i < size; i++)
  {
    cout << "Enter element " << (i+1) << ": ";
    cin >> array1[i];       // Read into array1
    array2[i] = array1[i];  // Copy from array1 to array2
  }

  // You should see the same sorted array for both algorithms since they were
  // passed the same sequence of data.
  selectionSort(array1, size);
  cout << "After calling selection sort, values are:\n";
  for(int i = 0; i < size; i++)
    cout << array1[i] << " ";
  cout << endl;

  insertionSort(array2, size);
  cout << "After calling insertion sort, values are:\n";
  for(int i = 0; i < size; i++)
    cout << array2[i] << " ";
  cout << endl;

  return 0;
}

void selectionSort(ELEMTYPE *array, int size)
{
    int min;
    int minPos;

    for(int i = 0; i < size - 1; i++)
    {
        min = array[i + 1];
        minPos = i + 1;

        for(int j = i + 2; j < size; j++)
        {
            if(array[j] < min)
            {
                min = array[j];
                minPos = j;
            }
        }
        if(min < array[i])
        {
            array[minPos] = array[i];
            array[i] = min;
        }
    }
}

void insertionSort(ELEMTYPE *array, int size)
{
    int value;
    int j;

    for(int pos = 1; pos < size; pos++)
    {
        value = array[pos];
        j = pos;

        while(value < array[j - 1])
        {
            array[j] = array[j - 1];
            j--;

            if(j == 0)
            {
                break;
            }
        }
        array[j] = value;
    }
}
