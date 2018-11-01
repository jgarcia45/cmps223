/* Juan Garcia
 * CMPS 223
 * Lab 2
 * April 9, 2013
 */

#include <iostream>
#include <cstdlib>
using namespace std;

#ifndef LISTELEM
#define LISTELEM int
#endif

#ifndef MAX_SIZE
#define MAX_SIZE 200
#endif

struct arrayList
{
    LISTELEM array[MAX_SIZE];
    int count;
};

// Creates a new list and returns a pointer to it
arrayList *createList();

// // Traverses the list and prints each element
void printList(arrayList *);

// Takes a given list, a list element and an index number. Inserts the
// element at the given index number
bool insertList(arrayList *, LISTELEM, int);

int main()
{
  LISTELEM elem;
  int index;

  // Create a new list
  arrayList *list = createList();
  if(list == NULL)
  {
      cout << "Error: Could not allocate a list. Aborting program....\n";
      exit(1);
  }

  while(true)
  {
      cout << "Enter an index number to insert at (-1 to exit loop): ";
      cin >> index;
      if(cin.fail())
      {
          cin.clear();
          cin.ignore(50, '\n');
          cout << "Error: You must type an integer.\n";
          continue;  // go to the next iteration and try again
       }
       if(index == -1) break;  // Exit loop when user types -1

       cout << "Enter element to insert at index " << index << ": ";
       cin >> elem;

       if(insertList(list, elem, index))
       {
           cout << elem << " inserted at index " << index << endl;
           cout << "List now contains:\n";
           printList(list);
        }
        else
        {
            cout << "Error: Could not insert " << elem << " at index " << index << endl;
        }
  }

  cout << "Ending program....\n";

  // Since list was created dynamically in createList, we need to delete it
  delete list;

  return 0;
}

arrayList *createList()
{
    arrayList *ptr = NULL;

    // Try to allocate the list, return NULL if it fails
    try
    {
        ptr = new arrayList;
    } catch(bad_alloc) {
      ptr = NULL;
    }
    if(ptr == NULL) return ptr;

    // Initialize the member variables
    ptr->count = 0;
    for(int i = 0; i < MAX_SIZE; i++)
        ptr->array[i] = 0;

    return ptr;
}

void printList(arrayList *ptr)
{
    // Sanity check to make sure the function wasn't passed a NULL pointer
    if(ptr == NULL) return;

    for(int i = 0; i < ptr->count; i++)
        cout << ptr->array[i] << " ";
    cout << endl;
}

bool insertList(arrayList *list, LISTELEM elem, int index)
{
    if(index < 0 || index > list->count)
    {
        cout << "invalid index" << endl;
        return false;
    }
    if(list->count == MAX_SIZE)
    {
        cout << "list full...error" << endl;
        return false;
    }
    for(int i = list->count; i > index; i--)
    {
        list->array[i] = list->array[i -1];
    }
    list->array[index] = elem;
    list->count++;
    return true;
}
