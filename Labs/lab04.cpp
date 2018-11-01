/* Juan Garcia
 * CMPS 223
 * Lab 4
 * April 24, 2013
 */

//          This creates an object-oriented version of the linked list

#include <iostream>
using namespace std;

class ListNode
{
  private:
    int element;                           // data being stored
    ListNode *next;                        // pointer to next element

  public:
    ListNode();                              // default constructor
    ListNode(int elem);                      // creates node to store elem
    ListNode(int elem, ListNode *n);         // specific data and next

    void setData(int elem) { element = elem; }  // set the element
    int getData() { return element; }           // retrieve the element
    void setNext(ListNode *n) { next = n;}      // set the next pointer
    ListNode *getNext() { return next; }        // retrieve the next pointer

    // Test for equality. Return true if right's element equals this element
    bool operator ==(const ListNode &right) { return (element == right.element); }

    // Output the element
    friend ostream & operator << (ostream &o, const ListNode &right);
};

ListNode::ListNode()
{
  next = NULL;
}

ListNode::ListNode(int elem)
{
  element = elem;
  next = NULL;
}

ListNode::ListNode(int elem, ListNode *n)
{
  element = elem;
  next = n;
}

ostream & operator <<(ostream &o, const ListNode &right)
{
  o << right.element;
  return o;
}

class LinkedList
{
  private:
    ListNode *head;                        // head pointer

    // Helper function for delete operation. Finds the previous element
    // in the list to the given element
    ListNode *find_previous(ListNode *ptr);

  public:
    LinkedList();                          // default constructor
    LinkedList(const LinkedList &right);   // copy constructor
    ~LinkedList();                         // destructor, deallocate list

    // Assignment operator, this is actually a member function
    void operator =(const LinkedList &right);

    bool empty();                          // is there a list?
    ListNode *search(int elem);            // find elem in list
    void insert(int elem, ListNode *prev); // insert element after prev
    void remove(ListNode *ptr);            // delete a specific node
    void remove(int elem);                 // find elem and delete if found

    // Operator for outputing the whole list
    friend ostream & operator << (ostream &o, const LinkedList &right);
};

ListNode *LinkedList::find_previous(ListNode *ptr)
{
  ListNode *node = head;  // current node we're searching, start at head

  while(node != NULL)
  {
    // Check if the next node (one following "node") is ptr
    if(node->getNext() == ptr)
      return node;
    // Increment the node pointer
    node = node->getNext();
  }
  return NULL;  // not found
}

LinkedList::LinkedList()
{
  head = NULL;
}

LinkedList::~LinkedList()
{
  // tmp is one to delete, node is current node
  ListNode  *tmp = NULL, *node = head;

  while(node != NULL)
  {
    tmp = node;  // Delete the current node
    node = node->getNext();  // Increment node pointer
    delete tmp;
  }
}

LinkedList::LinkedList(const LinkedList &right)
{
  // node is the current node in the source list, new_node is the newly
  // allocated node for this list (copy of node), prev is the previously
  // allocated node for this list
  ListNode *node = right.head, *new_node = NULL, *prev = NULL;

  if(node == NULL)  // empty source list
  {
    head = NULL;
    return;
  }

  // Copy the head node
  try
  {
    new_node = new ListNode;
  }
  catch(bad_alloc)
  {
    new_node = NULL;
  }
  if(new_node == NULL)
  {
    cout << "Allocation failed.\n";
    head = NULL;
    return;
  }
  new_node->setData(node->getData());  // copy data
  head = new_node;
  prev = new_node;
  node = node->getNext();

  // Copy the rest of the list
  while(node != NULL)
  {
    try
    {
      new_node = new ListNode;
    }
    catch(bad_alloc)
    {
      new_node = NULL;
    }
    if(new_node == NULL)
    {
      cout << "Allocation failed.\n";
      prev->setNext(NULL);
      return;
    }
    new_node->setData(node->getData());  // copy data
    prev->setNext(new_node); // Make previous node point to us
    prev = new_node;
    node = node->getNext();
  }
  prev->setNext(NULL);  // mark end of list
}

void LinkedList::operator =(const LinkedList &right)
{
  ListNode  *tmp = NULL, *node = NULL, *new_node = NULL, *prev = NULL;

  // Check for a = a syntax and exit function
  if(this == &right) return;

  // Delete the previous list
  node = head;
  while(node != NULL)
  {
    tmp = node;  // Delete the current node
    node = node->getNext();  // Increment node pointer
    delete tmp;
  }

  // Copy the new list
  node = right.head;
  if(node == NULL)  // empty source list
  {
    head = NULL;
    return;
  }

  // Copy the head node
  try
  {
    new_node = new ListNode;
  }
  catch(bad_alloc)
  {
    new_node = NULL;
  }
  if(new_node == NULL)
  {
    cout << "Allocation failed.\n";
    head = NULL;
    return;
  }
  new_node->setData(node->getData());  // copy data
  head = new_node;
  prev = new_node;
  node = node->getNext();

  // Copy the rest of the list
  while(node != NULL)
  {
    try
    {
      new_node = new ListNode;
    }
    catch(bad_alloc)
    {
      new_node = NULL;
    }
    if(new_node == NULL)
    {
      cout << "Allocation failed.\n";
      prev->setNext(NULL);
      return;
    }
    new_node->setData(node->getData());  // copy data
    prev->setNext(new_node); // Make previous node point to us
    prev = new_node;
    node = node->getNext();
  }
  prev->setNext(NULL);  // mark end of list
}

bool LinkedList::empty()
{
  return (head == NULL);
}

ListNode *LinkedList::search(int elem)
{
  ListNode *node = head;

  while(node != NULL)
  {
    if( *node == elem ) // This will use the == operator in ListNode
      return node;
    node = node->getNext();
  }
  return NULL;  // not found
}

void LinkedList::insert(int elem, ListNode *prev)
{
    if(prev != NULL)
    {
        bool inList = false;
        ListNode *ptr = head;

        while(ptr != NULL)
        {
            if(ptr == prev)
            {
                inList = true;
                break;
            }

            ptr = ptr->getNext();
        }

        if(!inList)
        {
            cout << "Error..." << endl;
            return;
        }
    }

    ListNode *newNode;
    newNode = new ListNode(elem);

    if(!newNode)
    {
        cout << "Error...." << endl;
        return;
    }

    if(prev == NULL)
    {
        newNode->setNext(head);
        head = newNode;
    }
    else
    {
        newNode->setNext(prev->getNext());
        prev->setNext(newNode);
    }
}

void LinkedList::remove(ListNode *ptr)
{
  ListNode *prev = NULL;

  // head delete
  if(ptr == head)
  {
    head = head->getNext();  // increment head to 2nd element
    delete ptr;
  }
  else
  {
    prev = find_previous(ptr);
    if(prev == NULL)
    {
      cout << "Error: Cannot delete. Node not in list.\n";
      return;
    }
    prev->setNext( ptr->getNext() );
    delete ptr;
  }
}

void LinkedList::remove(int elem)
{
  ListNode *ptr = NULL;

  ptr = search(elem);
  if(ptr == NULL)
  {
    cout << "Error: Cannot delete. Node not in list.\n";
    return;
  }
  remove(ptr);
  cout << elem << " deleted from list.\n";
}

ostream & operator <<(ostream &o, const LinkedList &right)
{
  ListNode *node = right.head;

  while(node != NULL)
  {
    o << *node << " ";  // Will use the output operator in ListNode
    node = node->getNext();
  }
  return o;
}

int menu();

int main()
{
  int selection;
  LinkedList cList;
  ListNode *result = NULL; // Result of last search
  int c;

  do
  {
    selection = menu();
    cout << endl;
    switch(selection)
    {
      case 0:
        cout << "Good-bye!\n";
        break;

      case 1:
        if(cList.empty())
        {
          cout << "The list is empty. Add an item before searching.\n";
          break;
        }
        cout << "Enter an integer: ";
        cin >> c;
        while(cin.fail())
        {
          cin.clear();
          cin.ignore(20, '\n');
          cout << "Error: Must enter an integer.\n";
          cout << "Enter an integer: ";
          cin >> c;
        }
        result = cList.search(c);
        if(result == NULL)
        {
          cout << "Integer not found in list.\n";
        }
        else
        {
          cout << "Integer found in list at address " << result << ".\n";
        }
        break;

      case 2:
        cout << "Enter an integer: ";
        cin >> c;
        while(cin.fail())
        {
          cin.clear();
          cin.ignore(20, '\n');
          cout << "Error: Must enter an integer.\n";
          cout << "Enter an integer: ";
          cin >> c;
        }
        cList.insert(c, result); // Insert after last search (or head if no search)
        result = NULL;  // Reset result
        cout << "Integer inserted into list.\n";
        break;

      case 3:
        if(cList.empty())
        {
          cout << "The list is empty. Add an item before deleting.\n";
          break;
        }
        cout << "Enter an integer: ";
        cin >> c;
        while(cin.fail())
        {
          cin.clear();
          cin.ignore(20, '\n');
          cout << "Error: Must enter an integer.\n";
          cout << "Enter an integer: ";
          cin >> c;
        }
        cList.remove(c);
        break;

      case 4:
        if(cList.empty())
        {
          cout << "The list is empty. Add an item before printing.\n";
        }
        else
        {
          cout << "The list contents are:\n" << cList << endl;
        }
        break;

      default:
        cout << "Error: Invalid menu selection.\n";
    }
    cout << endl;
  } while(selection != 0);

  return 0;
}

int menu()
{
  int sel;

  cout << "      Welcome to the Linked List Menu\n";
  cout << "  =======================================\n";
  cout << "  1.  Search for an element in the list\n";
  cout << "  2.  Add an element to the list\n";
  cout << "  3.  Delete an element from the list\n";
  cout << "  4.  Print the list\n";
  cout << endl;
  cout << "  0.  Exit\n";
  cout << "  =======================================\n";
  cout << "  Enter selection: ";

  cin >> sel;
  while(cin.fail())
  {
    cin.clear();
    cin.ignore(20, '\n');
    cout << "  Error: Selection must be an integer.\n";
    cout << "  Enter selection: ";
    cin >> sel;
  }

  return sel;
}
