/* Juan Garcia
 * CMPS223
 * Homework 2
 * April 12, 2013
 */

#include <iostream>
using namespace std;

struct ListNode
{
    int num;
    ListNode *next;
    ListNode *head;
};

ListNode *createNode(int);
ListNode *listInsert(ListNode*, ListNode*, int);
ListNode *listDelete(ListNode*, int);
ListNode *listSearch(ListNode*, int);
void listPrint(ListNode*);
void listDeallocate(ListNode*);

int main()
{
    ListNode *head = NULL;
    ListNode *result = NULL;
    ListNode *ptr = NULL;
    int choice;
    int element;

    do
    {
        cout << "    Welcome to the Linked List Menu" << endl;
        cout << "=======================================" << endl;
        cout << "1. Search for an element in the list" << endl;
        cout << "2. Add an element to the list" << endl;
        cout << "3. Delete an element from the list" << endl;
        cout << "4. Print the list" << endl;
        cout << endl;
        cout << "0. Exit" << endl;
        cout << "=======================================" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: if(head == NULL)
                    {
                        cout << "List is empty." << endl;
                        cout << endl;
                    }
                    else
                    {
                        cout << "Enter an element: ";
                        cin >> element;

                        result = listSearch(head, element);
                    }
                    break;
            case 2: cout << "Enter an element: ";
                    cin >> element;

                    head = listInsert(head, result, element);
                    break;
            case 3: if(head == NULL)
                    {
                        cout << "List is empty." << endl;
                        cout << endl;
                    }
                    else
                    {
                        cout << "Enter an element: ";
                        cin >> element;

                        head = listDelete(head, element);
                    }
                    break;
            case 4: if(head == NULL)
                    {
                        cout << "List is empty." << endl;
        createNode() = newnode;
                        cout << endl;
                    }
                    else
                    {
                        listPrint(head);
                    }
                    break;
            case 0: listDeallocate(head);
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
    return node;
}
ListNode *listInsert(ListNode *head, ListNode *prev, int elem)
{
    ListNode *newnode = createNode(elem);
    ListNode *tmp = head;

    if(prev != NULL)
    {
        bool inList = false;

        while(tmp != NULL)
        {
            if(prev = tmp)
            {
                inList = true;
                break;
            }
            tmp = tmp->next;
        }

        if(inList = false)
        {
            cout << "Invalid previous address." << endl;
        }
    }

    if(prev == NULL)
    {

        if(newnode == NULL)
        {
            return head;
        }
        newnode->next = head;
        return newnode;
    }
    else
    {

        if(newnode == NULL)
        {
            return head;
        }
        newnode->next = prev->next;
        prev->next = newnode;
        return head;
    }
}
ListNode *listDelete(ListNode *head, int elem)
{
    if(head == NULL)
    {
        return NULL;
    }

    ListNode *tmp = head;
    ListNode *prev = NULL;

    while(tmp != NULL)
    {
        if(tmp->num == elem)
        {
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL)
    {
        return head;
    }

    if(prev == NULL)
    {
        ListNode *nextnode = tmp->next;
        delete tmp;
        return nextnode;
    }
    else
    {
        prev->next = tmp->next;
        delete tmp;
        return head;
    }

}
ListNode *listSearch(ListNode *head, int elem)
{
    ListNode *ptr = NULL;
    ptr = head;

    while(ptr)
    {
        if(ptr->num == elem)
        {
            cout << elem << " was found!" << endl;
            cout << endl;
            return ptr;
        }
        ptr = ptr->next;
    }
    cout << elem << " was not found." << endl;
    cout << endl;
    return NULL;
}
void listPrint(ListNode *head)
{
    ListNode *ptr = head;
    while(ptr)
    {
        cout << ptr->num << " ";
        ptr = ptr->next;
    }
    cout << endl << endl;
}
void listDeallocate(ListNode *head)
{
    ListNode *node = NULL;
    ListNode *ptr = head;

    if(!head)
    {
        return;
    }
    while(ptr != NULL)
    {
        node = ptr;
        ptr = ptr->next;
        delete node;
    }
}
