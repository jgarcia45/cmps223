/* Juan Garcia
 * CMPS 223 / Derrick
 * Homework 7
 * May 24, 2013
 */

#include <iostream>
#include <cmath>
using namespace std;

#ifndef ELEMTYPE
#define ELEMTYPE int
#endif

#define MAX_CAPACITY 1013
#define EMPTY_VALUE -1
#define DELETED_VALUE -2

struct HashTable
{
    ELEMTYPE array[MAX_CAPACITY];
    int count;
};

void initTable(HashTable *);
bool empty(HashTable *);
bool full(HashTable *);
int hash1(ELEMTYPE);
int hash2(ELEMTYPE);
bool search(HashTable *, ELEMTYPE);
bool insert(HashTable *, ELEMTYPE);
bool remove(HashTable *, ELEMTYPE);

int main()
{
    HashTable Hash;
    int choice;
    int value;

    initTable(&Hash);

    do
    {
        cout << "               Hash Table Menu" << endl;
        cout << "======================================================" << endl;
        cout << "1. Insert an integer into the table" << endl;
        cout << "2. Delete an integer from the table" << endl;
        cout << "3. Search the table for an integer" << endl;
        cout << "4. Print the primary and secondary keys for an integer" << endl;
        cout << endl;
        cout << "0. Exit" << endl;
        cout << "======================================================" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: full(&Hash);

                    if(full(&Hash))
                    {
                        cout << "Table is full." << endl;
                    }
                    else
                    {
                        cout << "Enter a value to insert: ";
                        cin >> value;
                        insert(&Hash, value);
                    }

                    cout << endl;
                    break;
            case 2: empty(&Hash);

                    if(empty(&Hash))
                    {
                        cout << "Table is empty." << endl;
                    }
                    else
                    {
                        cout << "Enter a value to delete: ";
                        cin >> value;
                        remove(&Hash, value);

                        if(remove(&Hash, value) == true)
                        {
                            cout << "The value was removed." << endl;
                        }
                        else
                        {
                            cout << "The value was not removed." << endl;
                        }
                    }

                    cout << endl;
                    break;
            case 3: empty(&Hash);

                    if(empty(&Hash))
                    {
                        cout << "Table is empty." << endl;
                    }
                    else
                    {
                        cout << "Enter a value to search for: ";
                        cin >> value;
                        search(&Hash, value);

                        if(search(&Hash, value) == true)
                        {
                            cout << "The value was found." << endl;
                        }
                        else
                        {
                            cout << "The value was not found." << endl;
                        }
                    }

                    cout << endl;
                    break;
            case 4: cout << "Enter a value: ";
                    cin >> value;

                    hash1(value);
                    hash2(value);

                    cout << "Hash 1: " << hash1(value) << "     " << "Hash 2: " << hash2(value);

                    cout << endl;
                    break;
            case 0: cout << "Good-bye!" << endl;
                    break;
            default: cout << "Entered Invalid Choice! Try Again." << endl;
        }
    }while(choice != 0);

    return 0;
}

void initTable(HashTable *h)
{
    for(int i = 0; i < MAX_CAPACITY; i++)
    {
        h->array[i] = EMPTY_VALUE;
    }
    h->count = 0;
}

bool empty(HashTable *h)
{
    return (h->count == 0);
}

bool full(HashTable *h)
{
    return (h->count == MAX_CAPACITY);
}

int hash1(ELEMTYPE value)
{
    return (value % MAX_CAPACITY);
}

int hash2(ELEMTYPE value)
{
    int R = 5;

    return (R - (value % R));
}

bool search(HashTable *h, ELEMTYPE value)
{
    int key = hash1(value);
    int slot = key;
    int i = 1;

    while(h->array[slot] != value && h->array[slot] != EMPTY_VALUE && i <= MAX_CAPACITY)
    {
        slot = (key + i++) % MAX_CAPACITY;
    }

    return (h->array[slot] == value);
}

bool insert(HashTable *h, ELEMTYPE value)
{
    int key = hash1(value);
    int slot = key;
    int i = 1;

    while(h->array[slot] != EMPTY_VALUE && h->array[slot] != DELETED_VALUE)
    {
        slot = (key + i++) % MAX_CAPACITY;
    }
    h->array[slot] = value;
    h->count++;

    return (true);
}

bool remove(HashTable *h, ELEMTYPE value)
{
    int key = hash1(value);
    int key2 = hash2(value);
    int slot = key;
    int i = 1;

    while(h->array[slot] != value && h->array[slot] != EMPTY_VALUE && i < MAX_CAPACITY)
    {
        slot = (key + i++ * key2) % MAX_CAPACITY;
    }

    if(h->array[slot] == value)
    {
        h->array[slot] = DELETED_VALUE;
        h->count--;
    }

    return (true);
}
