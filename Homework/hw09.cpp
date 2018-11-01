/* Juan Garcia
 * CMPS 223 / Derrick
 * Homework 9 (Extra Credit)
 * June 4, 2013
 */

#include <iostream>
#include <fstream>
using namespace std;

#ifndef ELEMTYPE
#define ELEMTYPE int
#endif

#ifndef HEAPSIZE
#define HEAPSIZE 10
#endif

struct Heap
{
    int *arr;
    int count;
};

int parent(int);
int left_child(int);
int right_child(int);
Heap *createHeap(Heap *, int);
void deallocateHeap(Heap *);
bool empty(Heap *);
bool full(Heap *);
void percolateDown(Heap *, int);
void percolateUp(Heap *, int);
void heapify(Heap *, ELEMTYPE *, int);
void heapsort(ELEMTYPE *, int);

int main(int argc, char *argv[])
{
    Heap h;
    //char iFile[256] = argv[1];
    //char oFile[256] = argv[2];
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    int array[256];
    int count = 0;
    int num;
    int i = 0;

    if(argc < 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    if(inFile.fail() || outFile.fail())
    {
        cout << "Error...Files Don't Work!" << endl;
        inFile.clear();
        inFile.close();
        outFile.clear();
        outFile.close();
    }

    while(inFile >> num)
    {
        array[i++] = num;
        createHeap(&h, count);
        heapify(&h, array, i);
        heapsort(array, count);
    }

    deallocateHeap(&h);
    inFile.close();
    outFile.close();

    return 0;
}

int parent(int i)
{
    if(i <= 2)
    {
        return 0;
    }
    return((i - 1) / 2);
}

int left_child(int i)
{
    return((2 * i) + 1);
}

int right_child(int i)
{
    return((2 * i) + 2);
}

Heap *createHeap(Heap *h, int size)
{
    try
    {
        h->arr = new int [size];
    }
    catch(bad_alloc)
    {
        h->arr = NULL;
    }
    for(int i = 0; i < size; i++)
    {
        h->arr[i] = 0;
    }
    h->count = 0;
    //HEAPSIZE = size;

    return(h);
}

void deallocateHeap(Heap *h)
{
    /*
    if(!h)
    {
        return;
    }
    */

    for(int i = 0; i < HEAPSIZE; i++)
    {
        h->arr[i] = 0;
    }
    delete [] h->arr;
    h->arr = NULL;
    h->count = HEAPSIZE;
    h->count = 0;
}

bool empty(Heap *h)
{
    return(h->count == 0);
}

bool full(Heap *h)
{
    return(h->count == HEAPSIZE);
}

void percolateDown(Heap *h, int position)
{
    int l = left_child(position);
    int r = right_child(position);
    int greater;

    if(h->arr[l] > h->arr[position] && l < HEAPSIZE)
    {
        greater = l;
    }
    else
    {
        greater = position;
    }

    if(h->arr[r] > h->arr[greater] && r < HEAPSIZE)
    {
        greater = r;
    }

    if(greater != position)
    {
        int temp = h->arr[position];
        h->arr[position] = h->arr[greater];
        h->arr[greater] = temp;
        percolateDown(h, greater);
    }
}

void percolateUp(Heap *h, int position)
{
    /*
    int l = left_child(position);
    int r = right_child(position);
    int Parent;

    if(h->arr[l] < h->arr[Parent] && l < HEAPSIZE)
    {
        Parent = l;
    }
    else
    {
        Parent = position;
    }

    if(h->arr[r] < h->arr[Parent] && r < HEAPSIZE)
    {
        Parent = r;
    }
    */

    int i;

    if(position != 0)
    {
        if(h->arr[parent(i)] < h->arr[position])
        {
            int temp = h->arr[position];
            h->arr[position] = h->arr[parent(i)];
            h->arr[parent(i)] = temp;
            percolateUp(h, parent(i));
        }
    }

}

void heapify(Heap *h, ELEMTYPE *array, int size)
{
    h = createHeap(h, size);

    for(int i = 0; i < size; i++)
    {
        h->arr[i] = array[i];
        percolateUp(h, i);
    }
}

void heapsort(ELEMTYPE *array, int size)
{
    Heap *h;

    heapify(h, array, size);

    while(h->count--)
    {
        int temp = h->arr[0];
        h->arr[0] = h->arr[h->count];
        h->arr[h->count] = temp;

        if(h->count == 2)
        {
            break;
        }
        percolateDown(h, 0);
    }
}
