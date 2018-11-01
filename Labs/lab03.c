/* Juan Garcia
 * CMPS 223
 * Lab3
 * April 16, 2013
 */

#include <stdio.h>

#ifndef MAX_CAPACITY
#define MAX_CAPACITY  20   /* Maximum number of elements in the list */
#endif

#define NIL_VALUE     -1   /* An invalid index number. Marks end of list */
#define DATA_COL       0   /* Column that stores the data. */
#define NEXT_COL       1   /* Column that stores the pointer to next */
#define USE_COL        2   /* Column that stores 'in use' flag */

#define TRUE           1   /* TRUE value. C doesn't have bool, so we use int */
#define FALSE          0   /* FALSE value. C doesn't have bool, so we use int */


/* Variables for our list */

typedef struct __arrayLinked__
{
  int array[MAX_CAPACITY][3];  /* The 2D array to store the list */
  int free_ptr;            /* The index of the first empty slot in the list */
  int head;                /* The index of the first element in the list */
} arrayLinkedList;

/* Functions for our list */

void init_list(arrayLinkedList *);    /* Create an empty list */
int empty_list(arrayLinkedList *);    /* Check if the list is empty */
int full_list(arrayLinkedList *);     /* Check is the list is full */
void print_list(arrayLinkedList *);   /* Output the list to stdout */
void dump_list(arrayLinkedList *);    /* Output debugging info about the list */

/* Search the list for an element */
int search_list(arrayLinkedList *, int elem);

/* Insert the element after a given position */
int insert_list(arrayLinkedList *, int elem, int pos);

/* Delete an element in a given spot */
int delete_list(arrayLinkedList *, int pos);

/* Our main function */

int main() {
  arrayLinkedList list;
  int index, elem;

  init_list(&list);  /* Note that we use &list to convert the list from an */
                     /* object to an address, so we can pass it to a pointer */

  while(1)
  {
    printf("Enter an index number to insert at (-1 for head insert, -2 to exit loop): ");
    /* scanf uses format strings like printf to indicate the desired type of
     * input. Like printf, you can have multiple format tokens in the format
     * string and each token will be matched with the address of the variable
     * in the arg list */
    scanf("%d", &index);
    if(index == -2) break;  /* Exit loop when user types -2 */

    printf("Enter element to insert at index %d: ", index);
    scanf("%d", &elem);

    if(insert_list(&list, elem, index))
    {
      printf("Element inserted at index %d.\nList now contains:\n", index);
      print_list(&list);
    }
    else
    {
      printf("Could not insert element at index %d.\n", index);
    }
  }

  printf("After insert loop, the debug dump of the list is:\n");
  dump_list(&list);

  /****************************************************************************
   *
   * You will need to add the code similar to what staticlist.cpp from Lab 2's
   * solutions does:
   *
   *   - A call to the search_list function
   *   - If the search succeeds, call the delete_list function
   *
   ***************************************************************************/

  printf("Insert an element to search for: ");
  scanf("%d", &elem);

  index = search_list(&list, elem);

  if(index == -1)
  {
      printf("Element not found \n");
  }
  else
  {
      if(delete_list(&list, index) == 1)
      {
          print_list(&list);
      }
      else
      {
          printf("Cannot delete \n");
      }
  }

  return 0;
}

/* To create the empty list we need to first set head to the NIL_VALUE.
   We also have to organize the empty slots into a free list by setting each
   "next" to point to the next slot */
void init_list(arrayLinkedList *list) {
  int i;

  list->head = NIL_VALUE;   /* creates the empty list */
  list->free_ptr = 0;       /* make the first slot the start of the free list */

  /* now loop through the slots from the first slot to the next to last slot.
     for each slot, set their next column to the EMPTY value */
  for(i = 0; i < MAX_CAPACITY; i++) {
    list->array[i][DATA_COL] = 0;
    list->array[i][NEXT_COL] = (i+1);  /* Points to next slot */
    list->array[i][USE_COL] = FALSE;   /* Not in use right now */
  }
  /* The last slot needs to indicate the end of the free list by setting the
   * next column to the NIL_VALUE */
  list->array[MAX_CAPACITY-1][NEXT_COL] = NIL_VALUE;
}

/* The list is empty if the head is NIL_VALUE */
int empty_list(arrayLinkedList *list) {
  return (list->head == NIL_VALUE);
}

/* The list is full if the free list is empty, so if free_ptr is NIL_VALUE */
int full_list(arrayLinkedList *list) {
  return (list->free_ptr == NIL_VALUE);
}

/* Iterate the list printing all of the elements to stdout */
void print_list(arrayLinkedList *list) {
  int ptr;

  ptr = list->head;
  while(ptr != NIL_VALUE) {
    printf("%5d", list->array[ptr][DATA_COL]);
    ptr = list->array[ptr][NEXT_COL];              /* increment ptr to next */
  }
  printf("\n");
}

/* Iterate the list printing debugging info on the position and next */
void dump_list(arrayLinkedList *list) {
  int i;

  printf("The head index is %d. The free index is %d.\n",
         list->head, list->free_ptr);
  printf("%-10s %-13s %-10s %-10s\n", "Slot", "Element", "Next", "Use");
  for(i = 0; i < MAX_CAPACITY; i++) {
    printf("slot = %-2d  elem = %-5d  next = %-2d  use=%d\n", i,
           list->array[i][DATA_COL], list->array[i][NEXT_COL],
           list->array[i][USE_COL]);
  }
}

/* Search the list for the given element. If the element is found, return
   the slot where it was found. If the element is not found, return NIL_VALUE */
int search_list(arrayLinkedList *list, int elem) {
  int ptr;

  ptr = list->head;
  while(ptr != NIL_VALUE) {
    if(list->array[ptr][DATA_COL] == elem) {       /* Found! */
      return ptr;
    }
    ptr = list->array[ptr][NEXT_COL];              /* increment ptr to next */
  }
  return NIL_VALUE;
}

/* To insert an element at a given position, you have to get a free node,
   put the element in the data portion of the new node, set the next portion
   of the given position's node to the index of the new node and set the
   new node's next to NIL_VALUE. You also have to check if the list is
   currently empty and if so, set the head */
int insert_list(arrayLinkedList *list, int elem, int pos) {
  int new_node;

  if(pos < NIL_VALUE || pos >= MAX_CAPACITY) {
    printf("Error: Invalid slot number %d.\n", pos);
    return FALSE;
  }

  if(list->array[pos][USE_COL] == FALSE) {
    printf("Error: Slot number %d is not part of the list.\n", pos);
    return FALSE;
  }

  /* Get a new node and update the free pointer to be the next element */
  new_node = list->free_ptr;
  if(new_node == NIL_VALUE) {   /* Allocation failed. Print error and exit */
    printf("Error: The list is full. Cannot insert %d.\n", elem);
    return FALSE;
  }
  list->free_ptr = list->array[new_node][NEXT_COL];

  /* Set the element to the given value */
  list->array[new_node][DATA_COL] = elem;
  list->array[new_node][USE_COL] = TRUE;

  if(pos == NIL_VALUE) { /* inserting at the head, no previous element */
    list->array[new_node][NEXT_COL] = list->head;
    list->head = new_node;
  }
  else {  /* Inserting after element at pos, update pos's next pointer */
    /* copy previous's next index to the new node */
    list->array[new_node][NEXT_COL] = list->array[pos][NEXT_COL];
    /* update previous to point to new node */
    list->array[pos][NEXT_COL] = new_node;
  }

  return TRUE;
}

/* To delete a node, we need to update the previous node to skip over the
   current node. We'll do a find_previous operation in-line in the delete.
   Once deleted, we'll add it to the free node list */
int delete_list(arrayLinkedList *list, int pos) {
  int prev, ptr;

  if(pos < 0 || pos >= MAX_CAPACITY) {
    printf("Error: Invalid slot number %d.\n", pos);
    return FALSE;
  }

  prev = NIL_VALUE; /* Initialize prev to the NIL_VALUE */

  if(list->head == pos) {
    /* For head deletion, set head to next element in list */
    list->head = list->array[pos][NEXT_COL];
  }
  else {
    /* Find the slot that points to pos in its NEXT_COL */
    ptr = list->head;
    while(ptr != NIL_VALUE) {
      if(list->array[ptr][NEXT_COL] == pos) {   /* Found it! */
        prev = ptr;
        break;
      }
      ptr = list->array[ptr][NEXT_COL];
    }

    if(prev == NIL_VALUE) {  /* Slot not in list. Print error and exit */
      printf("Error: Slot %d is not in list. Cannot delete.\n", pos);
      return FALSE;
    }

    /* Now we know the index of the previous element, so we can update the
       next columns to skip over the node being deleted */
    list->array[prev][NEXT_COL] = list->array[pos][NEXT_COL];
  }

  /* Now add this slot to the free node list. This node will be added to the
   * head of the free list, so set its next index to the current head of the
   * free list and then update the free index to it */
  list->array[pos][NEXT_COL] = list->free_ptr;
  list->array[pos][USE_COL] = FALSE;
  list->free_ptr = pos;

  return TRUE;
}
