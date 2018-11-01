/* Juan Garcia
 * CMPS 223
 * Homework 3
 * April 21, 2013
 */

#include <iostream>
using namespace std;

struct ListNode
{
    int num;
    ListNode *next;
    ListNode *prev;
};

ListNode *createNode(int);
void listInsert(ListNode *, ListNode *, int);
void listDelete(ListNode *, int);
ListNode *listSearch(ListNode *, int);
void listPrint(ListNode *);
void listDeallocate(ListNode *);
ListNode *listInitialize();
ListNode *listReverseSearch(ListNode *, int);
void listReversePrint(ListNode *);

int main()
{
    ListNode *head = NULL;
    ListNode *result = NULL;
    ListNode *ptr = NULL;
    int choice;
    int element;

    head = listInitialize();
    ptr = head;

    do
    {
        cout << "    Welcome to the Linked List Menu" << endl;
        cout << "===============================================" << endl;
        cout << "1. Search forwards for an element in the list" << endl;
        cout << "2. Add an element to the list" << endl;
        cout << "3. Delete an element from the list" << endl;
        cout << "4. Print the list" << endl;
        cout << "5. Search backwards for an element in the list" << endl;
        cout << "6. Print the list in reverse" << endl;
        cout << endl;
        cout << "0. Exit" << endl;
        cout << "===============================================" << endl;
        cout << "Enter Selection: ";
        cin >> choice;

        switch(choice)
        {
            case 1: if(head->next == head)
                    {
                        cout << "List is empty." << endl;
                        cout << endl;
                        break;
                    }
                    cout << "Enter an element: ";
                    cin >> element;
                    ptr = listSearch(head, element);

                    if(ptr == head)
                    {
                        cout << "Element was not found." << endl;
                        cout << endl;
                    }
                    else
                    {
                        cout << "Elemenet was found." << endl;
                        cout << endl;
                    }
                    break;
            case 2: cout << "Enter an element: ";
                    cin >> element;
                    listInsert(head, ptr, element);
                    ptr = head;
                    break;
            case 3: if(head->next == head)
                    {
                        cout << "List is empty." << endl;
                        cout << endl;
                        break;
                    }
                    cout << "Enter an element: ";
                    cin >> element;
                    listDelete(head, element);
                    break;
            case 4: if(head->next == head)
                    {
                        cout << "List is empty." << endl;
                        cout << endl;
                        break;
                    }
                    listPrint(head);
                    break;
            case 5: if(head->next == head)
                    {
                        cout << "List is empty." << endl;
                        cout << endl;
                        break;
                    }
                    cout << "Enter an element: ";
                    cin >> element;
                    ptr = listSearch(head, element);

                    if(ptr == head)
                    {
                        cout << "Element was not found." << endl;
                        cout << endl;
                    }
                    else
                    {
                        cout << "Element was found." << endl;
                        cout << endl;
                    }
                    break;
            case 6: if(head->next == head)
                    {
                        cout << "List is empty." << endl;
                        cout << endl;
                        break;
                    }
                    listReversePrint(head);
                    break;
            case 0: listDeallocate(head);
                    ptr = NULL;
                    cout << "Good-bye!" << endl;
                    break;
            default: cout << "Entered Invalid Choice! Try Again." << endl;
        }
    }while(choice != 0);

    return 0;
}

ListNode *createNode(int elem)
{
    ListNode *node = NULL;
    try
    {
        node = new ListNode;
    }
    catch(bad_alloc)
    {
        node = NULL;
    }
    if(node)
    {
        node->num = elem;
        node->next = NULL;
    }

    return(node);
}

void listInsert(ListNode *head, ListNode *prev, int elem)
{
    if(head == NULL || prev == NULL)
    {
        cout << "error..." << endl;
        return;
    }

    if(prev != head)
    {
        bool inList = false;
        ListNode *tmp = head->next;

        while(tmp != head)
        {
            if(tmp == prev)
            {
                inList = true;
                break;
            }

            tmp = tmp->next;
        }

        if(inList == false)
        {
            return;
        }
    }

    ListNode *newNode = createNode(elem);
    ListNode *nextNode = prev->next;

    newNode->next = nextNode;
    newNode->prev = prev;

    prev->next = newNode;
    nextNode->prev = newNode;
}

void listDelete(ListNode *head, int elem)
{
    ListNode *ptr = listSearch(head, elem);

    if(ptr == head)
    {
        return;
    }

    ListNode *nextNode = ptr->next;
    ListNode *prev = ptr->prev;

    nextNode->prev = prev;
    prev->next = nextNode;

    delete ptr;
}

ListNode *listSearch(ListNode *head, int elem)
{
    ListNode *tmp = head->next;

    while(tmp != head)
    {
        if(tmp->num == elem)
        {
            return tmp;
        }

        tmp = tmp->next;
    }

    return head;
}

void listPrint(ListNode *head)
{
    ListNode *ptr = head;

    ptr = head->next;

    while(ptr !=head)
    {
        cout << ptr->num << " ";
        ptr = ptr->next;
    }

    cout << endl;
    cout << endl;
}

void listDeallocate(ListNode *head)
{
    ListNode *node = NULL;
    ListNode *ptr = head->next;

    while(ptr != head)
    {
        node = ptr;
        ptr = ptr->next;
        delete node;
    }

    delete head;
}

ListNode *listInitialize()
{
    ListNode *ptr;
    try
    {
        ptr = new ListNode;
    }
    catch(bad_alloc)
    {
        ptr = NULL;
    }

    ptr->next = ptr;
    ptr->prev = ptr;

    return(ptr);
}

ListNode *listReverseSearch(ListNode *head, int elem)
{
    ListNode *ptr = head->prev;

    while(ptr != head)
    {
        ptr = ptr->prev;
    }
}

void listReversePrint(ListNode *head)
{
    ListNode *ptr = head->prev;

    ptr = head->prev;

    while(ptr != head)
    {
        cout << ptr->num << " ";
        ptr = ptr->prev;
    }

    cout << endl;
    cout << endl;
}
