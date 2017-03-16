
#ifndef _CIS22C_DOUBLY_PRIORITYQUEUE
#define _CIS22C_DOUBLY_PRIORITYQUEUE

#include <iostream>
#include <typeinfo>

#include "Node.h"
// definition begin **********************************************************************************

// Interface of PriorityQueue
template <class T>
class PriorityQueue
{
private:
    int count = 0;          // To track number of entries in the list
    int size = 0;           // To track the total size of characters
    bool sorted = false;
    Node<T> *front;
    Node<T> *rear;

public:
    PriorityQueue();  // Constructor
    ~PriorityQueue(); // Destructor

    // Functions
    int getCurrentSize();   // Gets the current number of entries in the list
    int getCharSize();      // Gets the total size of characters
    bool isEmpty();         // Sees whether the list is empty
    void enqueue(T);        // Adds a new entry to the list
    bool dequeue(T);        // Removes one occurrence of a given entry fro m the list
    void clear();           // Removes all entries from the list
    Node<T> * find(T);      // Tests whether the list contains the entry
    void moveBefore(Node<T> *, Node<T> *);  // Move node before another node

    Node<T> * min();        // Get minimum node
    void removeMin();       // Remove minimum node

    void importDataFile(string );  // Import data file
    void showList(bool, Node<T> *, int);        // Print all nodes

    // Sorting
    void swap(Node<T> *, Node<T> *);
    int bubbleSort();
    int selectionSort();
    int mergeSort(PriorityQueue<T>& S, int);
    void merge(PriorityQueue<T>& S1, PriorityQueue<T>& S2, PriorityQueue<T>& S);
    int quickSort(PriorityQueue<T>& S, int);

    friend int main();

    template <class T>
    friend class HuffmanTree;
};
#endif
// definition end **********************************************************************************

