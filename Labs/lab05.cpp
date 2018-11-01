/* Juan Garcia
 * CMPS 223 / Derrick
 * Lab 5
 * April 30, 2013
 */

#include <iostream>
#include <cstdlib>
using namespace std;

#ifndef LISTELEM
#define LISTELEM int
#endif

#ifndef ZEROELEM
#define ZEROELEM 0
#endif

#ifndef MAX_SIZE
#define MAX_SIZE 200
#endif

// Define a macro to temporarily advance the queue indices and wrap the indices
// back around to 0 when they advance beyond the valid range using modulo
#define advance(x) ((x + 1) % MAX_SIZE)

// This macro will temporarily decrement an index using modulo math. The way
// this works is it subtracts 1 from the index (resulting in a value from the
// range -1 to MAX_SIZE-2). -1 is an invalid index but all of the rest are
// fine. To bypass the need for an if statement, we will add MAX_SIZE to the
// result, converting it to a value in the range of MAX_SIZE-1 to 2*MAX_SIZE-2.
// If we then modulo that by MAX_SIZE, we will convert it back into a value
// from 0 to MAX_SIZE-1.
// For example:
//   index is currently 0                    index is currently 5
//   index - 1 = -1                          index - 1 = 4
//   -1 + 200 = 199                          4 + 200 = 204
//   199 % 200 = 199                         204 % 200 = 4
//   199 is one index back from 0            4 is one index back from 5
#define decrement(x)  ((MAX_SIZE + (x - 1)) % MAX_SIZE)

struct arrayQueue
{
  LISTELEM array[MAX_SIZE];
  int frontIndex;
  int backIndex;
};

// Initialize all elements to 0 and the front and back indices to 0
void initQueue(arrayQueue *);

// Check if the queue is empty (front and back indices are the same)
bool emptyQueue(arrayQueue *);

// Check if the queue is full (back index is one behind front index)
bool fullQueue(arrayQueue *);

// Add an element to the back of the queue.
bool enqueue(arrayQueue *, LISTELEM);

// Remove an element from the front of the queue.
bool dequeue(arrayQueue *);

// Return the value at the front of the queue
LISTELEM front(arrayQueue *);

// Return the value at the back of the queue
LISTELEM back(arrayQueue *);

// A debugging report on the queue
void debugReport(arrayQueue *);

int main()
{
  arrayQueue line;
  LISTELEM elem;
  int selection;

  // Initialize the queue by passing the initQueue function the address of
  // our local queue called 'line'
  initQueue(&line);

  cout << "                 Lab 5 Menu\n";
  cout << "============================================\n";
  cout << "1. Enqueue an element (insert operation)\n";
  cout << "2. Dequeue an element (delete operation)\n";
  cout << "3. Print the value at the front of the queue\n";
  cout << "4. Print the value at the end of the queue\n";
  cout << "5. Print debug report for the queue\n";
  cout << "\n0. Exit menu\n";
  cout << "============================================\n";
  do
  {
    cout << "\nEnter selection: ";
    cin >> selection;
    cout << endl;
    if(cin.fail())
    {
      cin.clear();
      cin.ignore(50, '\n');
      cout << "Error: You must type an integer.\n";
      continue;  // go to the next iteration and try again
    }
    switch(selection)
    {
      case 0:
        cout << "Goodbye!\n";
        break;

      // The main function does not check for full before calling enqueue
      // You must be sure to handle this case in the enqueue function
      case 1:
        cout << "Enter an element to insert: ";
        cin >> elem;
        if(enqueue(&line, elem))
        {
          cout << elem << " inserted at the back of the queue.\n";
        }
        else
        {
          cout << "Could not enqueue " << elem << endl;
        }
        break;

      // The main function does not check for empty before calling dequeue
      // You must make sure to handle this case
      case 2:
        elem = front(&line);  // Retrieve the value at the front of the queue
        if(dequeue(&line))
        {
          cout << elem << " removed from front of queue.\n";
        }
        else
        {
          cout << "Could not dequeue the front of the queue.\n";
        }
        break;

      case 3:
        if(emptyQueue(&line))
        {
          cout << "The queue is empty.\n";
          break;
        }
        cout << "The front value is " << front(&line) << endl;
        break;

      case 4:
        if(emptyQueue(&line))
        {
          cout << "The queue is empty.\n";
          break;
        }
        cout << "The back value is " << back(&line) << endl;
        break;

      case 5:
        debugReport(&line);
        break;

      default:
        cout << "Invalid selection.\n";
    }
  } while(selection != 0);

  return 0;
}

// Initialize all elements to 0 and the front and back indices to 0
void initQueue(arrayQueue *q)
{
  for(int i = 0; i < MAX_SIZE; i++)
  {
    q->array[i] = ZEROELEM;
  }
  q->backIndex = 0;
  q->frontIndex = 0;
}

// Check if the queue is empty (front and back indices are the same)
bool emptyQueue(arrayQueue *q)
{
  return (q->frontIndex == q->backIndex);
}

// Check if the queue is full (back index is one behind front index)
// Use our advance macro from above to calculate if advancing the back index
// by one would make it equal to the front index. The advance macro only
// temporarily advances the index, which is what we want for this check
bool fullQueue(arrayQueue *q)
{
  return (advance(q->backIndex) == q->frontIndex);
}

// Return the value at the front of the queue
LISTELEM front(arrayQueue *q)
{
  if(emptyQueue(q))
  {
    cout << "Cannot call front() on an empty queue.\n";
    return ZEROELEM;
  }
  return q->array[q->frontIndex];
}

// Return the value at the back of the queue
LISTELEM back(arrayQueue *q)
{
  if(emptyQueue(q))
  {
    cout << "Cannot call back() on an empty queue.\n";
    return ZEROELEM;
  }
  return q->array[decrement(q->backIndex)];
}

// Print debugging information about the queue
void debugReport(arrayQueue *q)
{
  cout << "Front index: " << q->frontIndex << endl;
  cout << "Back index:  " << q->backIndex << endl;

  for(int i = q->frontIndex; i != q->backIndex; i = advance(i))
  {
    cout << q->array[i] << " ";
  }
  cout << endl;
}

bool enqueue(arrayQueue *q, LISTELEM elem)
{
    if(fullQueue(q))
    {
        cout << "Full. Queue Error..." << endl;
        return false;
    }
    q->array[q->backIndex] = elem;
    q->backIndex = ((q->backIndex + 1) % MAX_SIZE);

    return true;
}

bool dequeue(arrayQueue *q)
{
    if(emptyQueue(q))
    {
        cout << "Empty. Queue Error..." << endl;
        return false;
    }
    q->array[q->frontIndex] = 0;
    q->frontIndex = ((q->frontIndex + 1) % MAX_SIZE);

    return true;
}
