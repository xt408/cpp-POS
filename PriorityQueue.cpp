 

#include "PriorityQueue.h"

using namespace std;

// Implementation begin **********************************************************************************

// Constructor
template <class T>
PriorityQueue<T>::PriorityQueue()// Constructor inline
{
    front = nullptr;
    rear = nullptr;
}


// Destructor
template <class T>
PriorityQueue<T>::~PriorityQueue()
{
    clear(); // Removes all entries from the list
}


// Gets the current number of entries in the list
template <class T>
int PriorityQueue<T>::getCurrentSize()
{
    return count;
}

template <class T>
int PriorityQueue<T>::getCharSize()
{
    return size;
}


// Sees whether the list is empty
template <class T>
bool PriorityQueue<T>::isEmpty()
{
    return getCurrentSize() == 0;
}

// Move node to place before another node
template <class T>
void PriorityQueue<T>::moveBefore(Node<T> * nodePtr, Node<T> *targetPtr)
{
    // Handle node links      
    //if (nodePtr->right)
    //{
    //    nodePtr->right->left = nodePtr->left;
    //}

    //if (nodePtr->left)
    //{
    //    nodePtr->left->right = nodePtr->right;
    //    cout << "move: n->l->r = n->r " << endl; system("pause");
    //}

    // Handle target node
    if (targetPtr->left) // not null
    {
        targetPtr->left->right = nodePtr;   
        nodePtr->left = targetPtr->left;
    }

    nodePtr->left->right = nodePtr->right;
    if (nodePtr->right)
    {
        nodePtr->right->left = nodePtr->left;
    }

    targetPtr->left = nodePtr;
    nodePtr->right = targetPtr;




    system("pause");

    //if (targetPtr == front) // is front
    //{
    //    //cout << "target is front " << endl;

    //    targetPtr->left = nodePtr;
    //    nodePtr->right = targetPtr;
    //    front = nodePtr;
    //}
    //else if (targetPtr == rear) // is rear
    //{
    //    //cout << "target is rear " << endl; 
    //    targetPtr->right = nodePtr;
    //    nodePtr->left = targetPtr;
    //    rear = nodePtr;
    //}
    //else
    //{
    //    if (targetPtr->left) // not null
    //    {
    //        targetPtr->left->right = nodePtr;
    //        nodePtr->left = targetPtr->left;
    //    }

    //    targetPtr->left = nodePtr;
    //    nodePtr->right = targetPtr;        
    //}
}
// Get minimum node
template <class T>
Node<T> * PriorityQueue<T>::min()
{
    if (rear != NULL)
    {
        return rear;
    }

    return false;
}

// Remove minimum node
template <class T>
void PriorityQueue<T>::removeMin()
{
    Node<T>* nodePtr = rear;
    
    if (rear)
    {        
        rear = nodePtr->left;
        delete nodePtr;
        count--;
    }

    if (rear == nullptr)
    {
        front = nullptr;
    }
}


// Adds a new entry to the list
template <class T>
void PriorityQueue<T>::enqueue(T akey)
{
    Node<T> *newNode;
    Node<T> *nodePtr;

    //cout << "(" << count << ") " << akey << endl;

    if (!front)// If front is unused then hold newNode in front
    {
        newNode = new Node<T>(akey);// allocate a new node to hold aValue

        //cout << newNode->freq; system("pause");
        front = newNode;
        rear = newNode;
        count++;
    }
    else
    {
        // Check weaher new item already existed?
        if (nodePtr = find(akey))// if new node already existed
        {
            // then, increase its frequency

            nodePtr->freq++;
        }
        else// otherwise
        {
            newNode = new Node<T>(akey);// allocate a new node to hold aValue           

            rear->right = newNode;
            newNode->left = rear;
            rear = newNode;
            count++;
        }

    }

    //front->left = nullptr;
    //rear->right = nullptr;
}

// Removes one occurrence of a given entry fro m the list
template <class T>
bool PriorityQueue<T>::dequeue(T akey)
{
    // Instantiate node pointers
    Node<T> *nodePtr;
    Node<T> *leftiousNode;

    leftiousNode = new Node<T>;

    //cout << "remove: " << akey << endl;

    // If list is empty do nothing and return
    if (isEmpty())
    {
        //cout << "List is empty." << endl;
        return false;
    }

    if (front->key == akey)
    {
        nodePtr = front->right;   // if delete 1, then here is 2
        delete front;            // delete 1
        nodePtr->left = front;
        front = nodePtr;         // assign new front as 2
        count--;

        //cout << " found at front and deleted " << endl;
        return true;
    }
    else
    {
        // Initialize nodePtr to front
        nodePtr = front;

        // Looping to find value till end of nodes
        while (nodePtr != nullptr && nodePtr->key != akey)
        {
            leftiousNode = nodePtr;
            nodePtr = nodePtr->right;
        }

        //cout << "node: " << nodePtr->key << ": "<< nodePtr->right << endl;  system("pause");
        //nodePtr = nodePtr->right;
        //cout << "right node: " << nodePtr->key << ": " << nodePtr->right << endl;  system("pause");

        // If value found, then delete it
        if (nodePtr != nullptr)
        {

            //cout << " is not nullptr " << endl; system("pause");
            //cout << nodePtr->key << endl;
            //cout << nodePtr->right << endl;

            if (nodePtr->right == nullptr)
            {
                //cout << "is nullptr" << endl;

                //cout << "going to link leftiousnode to nullptr" << endl; system("pause");
                leftiousNode->right = nullptr;

                //cout << "going to delete node" << endl; system("pause");
                //delete[] nodePtr;


                count--;
                return true;
            }
            else
            {
                //cout << "is not nullptr" << endl;

                leftiousNode->right = nodePtr->right;
                delete[] nodePtr;
                count--;
                return true;
            }

            //system("pause");
        }
    }

    return false;
}


// Removes all entries from the list
template <class T>
void PriorityQueue<T>::clear()
{
    // Instantiate pointers
    Node<T> *nodePtr;
    Node<T> *rightNode;

    // Initialize nodepointer to front
    nodePtr = front;

    // Looping to delele all nodes
    while (nodePtr != nullptr)
    {
        rightNode = nodePtr->right;

        //cout << "Going to delete " << nodePtr->key << endl;        
        //cout << "right node:" << rightNode << endl; system("pause");

        if (rightNode)
        {
            delete nodePtr;
            nodePtr = rightNode;
        }
        else
        {
            delete nodePtr;
            nodePtr = nullptr;
        }

    }
    front = nullptr;
    rear = nullptr;

    count = 0;
    size = 0;
}

// Tests whether the list contains the entry
template <class T>
Node<T> * PriorityQueue<T>::find(T akey)
{
    // Instantiate pointers
    Node<T> *nodePtr;

    // Initialize nodepointer to front
    nodePtr = front;

    // Looping to search
    // According to book, the time complexity for searching PriorityQueue is O(n)
    while (nodePtr != nullptr)
    {
        //if (akey =='$')
        //{
        //    cout << ">>> find right: " << nodePtr->key << endl;
        //}
        

        if (nodePtr->key == akey)
        {
            //cout << akey << " found " << endl; system("pause");
            return nodePtr;
        }
        
        nodePtr = nodePtr->right;
    }

    return false;
}



template <class T>
void PriorityQueue<T>::importDataFile(string file)
{
    fstream dataInfile;
    string line, s;
    int key_INDEX = 0, VALUE_INDEX = 1;
    char c;

    dataInfile.open(file);
    if (dataInfile.fail())
    {
        cout << "Error: couldn't open the data file '" << file << "'." << endl;
        system("pause");
        exit(0);
    }
    else
    {
        int row = 0, strlength;

        clear();
        while (getline(dataInfile, line))
        {
            //cout << line.length() << endl;
            line += "\r\n";
            //cout << line.length() << endl; system("pause");


            strlength = line.length();
            for (int i = 0; i < strlength; i++)
            {
                // Only track ASCII between 32-128
                if ((int) line[i] >= 32 || (int) line[i] <= 128)
                {
                    //cout << line[i] << endl;
                    //s = string(1, line[i]);
                    //cout << line[i] << ": " << (int) line[i] << endl;
                    
                    c = line[i];
                    enqueue(c);
                    size++;
                    //system("pause");
                }
            }
            //system("pause");
        }
        //system("pause");
        sorted = false;

        //cout << "\t " << getCurrentSize() << " characters imported." << endl; //system("pause");

        //cout << "Going to sort  "; system("pause");
        //mergeSort(List, 0);
    }
}


// Print all nodes
template <class T>
void PriorityQueue<T>::showList(bool forward, Node<T> *nodePtr, int i = 0)
{
    if (nodePtr)
    {
        i++;
        cout << setw(8) << left << i;
        cout << setw(1) << left << nodePtr->key;
        cout << setw(10) << right << nodePtr->freq << endl;

        if (forward)
        {
            showList(forward, nodePtr->right, i);
        }
        else
        {
            showList(forward, nodePtr->left, i);
        }
    }    
}


template <class T>
void PriorityQueue<T>::swap(Node<T> * u, Node<T> * v)
{
    T key = u->key;
    string val = u->val;
    int freq = u->freq;

    u->key = v->key;
    u->val = v->val;
    u->freq = v->freq;

    v->key = key;
    v->val = val;
    v->freq = freq;

}


// Bubble Sort
// Find the largest, seconde largest..., put them to the end till all ended.
template <class T>
int PriorityQueue<T>::bubbleSort()
{
    int iterator_count = 0;

    Node<T> * nodePtr;
    //Node<T> * rightPtr;

    int todo = getCurrentSize() - 1;
    //cout << "todo:" << todo << endl; system("pause");

    nodePtr = front;
    while (todo > 0)
    {
        iterator_count++;
        //cout << nodePtr->key << endl; system("pause");

        for (int i = 0; i < todo; i++)
        {
            iterator_count++;
            if (nodePtr->freq < nodePtr->right->freq)
            {
                //cout << "swap: " << nodePtr->key << " <-> " << nodePtr->right->key << endl;
                swap(nodePtr, nodePtr->right);
            }

            nodePtr = nodePtr->right;
        }

        nodePtr = front;
        todo--;
    }

    
    return iterator_count;
}


// Selection Sort - n^2
// Find the smallest, seconde smallest..., put them to the begin till all found.
template <class T>
int PriorityQueue<T>::selectionSort()
{
    Node<T> * nodePtr;
    Node<T> * smallest = front;
    int size = 1, j = 0;
    int iterator_count = 0;

    while (smallest)
    {
        iterator_count++;
        //cout << "smallest: " << smallest->key << endl;

        nodePtr = smallest->right;
        while (nodePtr)
        {
            iterator_count++;
            j++;

            //cout << "\t " << j << "/" << todo << " - node: " << nodePtr->key << endl;
            //cout << "\t compare: " << smallest->key << " <-> " << nodePtr->key << endl;
            //cout << "**********************" << endl;

            if (smallest->key > nodePtr->key)
            {
                //cout << "swap: " << smallest->key << " <-> " << nodePtr->key << endl;
                swap(nodePtr, smallest);
            }

            nodePtr = nodePtr->right;
        }

        smallest = smallest->right;
        size++;
        //system("pause");
    }

    return iterator_count;
}

// Merge Sort - O(n long n)
// divide-and-conquer
template <class T>
int PriorityQueue<T>::mergeSort(PriorityQueue<T>& S, int iterator_count)
{
    //typedef typename PriorityQueue<T>::iterator Itor; // sequence of elements
    //cout << "sort list "; system("pause");

    int n = S.count;
    int todo = 0;
    //cout << "n: " << n << endl;
    if (n <= 1)
    {
        return iterator_count; // already sorted or empty
    }

    PriorityQueue<T> S1, S2;
    //Itor p = S.begin();
    Node<T> * nodePtr = S.front;

    todo = n / 2;
    //cout << " S1: 0 - " << todo;  system("pause");
    for (int i = 0; (i < todo && nodePtr != nullptr); i++)
    {
        iterator_count++;
        //S1.push back(*p++); // copy first half to S1
        S1.enqueue(nodePtr->key);
        nodePtr = nodePtr->right;
    }
    //cout << "show S1: ";  S1.showList(true); system("pause");

    //cout << " S2: " << todo << " - " << n ;  system("pause");
    for (int i = todo; (i <= n && nodePtr != nullptr); i++)
    {
        iterator_count++;
        //S2.push back(*p++); // copy second half to S2        
        S2.enqueue(nodePtr->key, nodePtr->freq);
        nodePtr = nodePtr->right;
    }
    //cout << "show S2: ";  S2.showList(true); system("pause");


    iterator_count = mergeSort(S1, iterator_count); // recur on first half

    iterator_count = mergeSort(S2, iterator_count); // recur on second half

    S.clear(); // clear S¡¯s contents
    merge(S1, S2, S); // merge S1 and S2 into S

    //cout << "show result: \n";  S.showList(true); system("pause");
    //cout << "iterator_count: " << iterator_count << " of " << count << "\n";

    return iterator_count;
}

template <typename T>
void PriorityQueue<T>::merge(PriorityQueue<T>& S1, PriorityQueue<T>& S2, PriorityQueue<T>& S)
{

    //typedef typename PriorityQueue<E>::iterator Itor; // sequence of elements
    //Itor p1 = S1.begin();
    //Itor p2 = S2.begin();

    Node<T> * nodePtr1 = S1.front;
    Node<T> * nodePtr2 = S2.front;

    // until either is empty
    while (nodePtr1 != nullptr && nodePtr2 != nullptr)
    {
        //cout << "compare: " << nodePtr1->key << " && " << nodePtr2->key << endl;


        if (nodePtr1->key < nodePtr2->key) // append smaller to S
        {
            //cout << "push: " << nodePtr1->key << endl;
            S.enqueue(nodePtr1->key, nodePtr1->freq);
            nodePtr1 = nodePtr1->right;
        }
        else
        {
            //cout << "push: " << nodePtr2->key << endl;
            S.enqueue(nodePtr2->key, nodePtr2->freq);
            nodePtr2 = nodePtr2->right;
        }
    }

    //cout << "push rest S1 ******************************" << endl;
    while (nodePtr1) // copy rest of S1 to S
    {
        S.enqueue(nodePtr1->key, nodePtr1->freq);
        //cout << "push: " << nodePtr1->key << nodePtr1->freq << endl;
        nodePtr1 = nodePtr1->right;
    }

    //cout << "push rest S2 ******************************" << endl;
    while (nodePtr2) // copy rest of S2 to S
    {
        S.enqueue(nodePtr2->key, nodePtr2->freq);
        //cout << "push: " << nodePtr2->key << nodePtr2->freq << endl;
        nodePtr2 = nodePtr2->right;
    }

    //cout << "end ------------------------ \n\n" << endl;
}

// QuickSort -- divide-and-conquer 
// O(n log n)
template <typename T>
int PriorityQueue<T>::quickSort(PriorityQueue<T>& S, int iterator_count = 0)
{
    int n = S.count;
    int half = n / 2;

    if (n < 2)
    {
        //cout << "n < 2 then return " << endl;
        return iterator_count; // already sorted or empty
    }

    PriorityQueue<T> SL, SE, SG;

    // Delcare pivot
    //Node<T> * nodePtrPivot = S.rear; // Choose the last node to be pivot can increase running times if the linked list already sorted.
    Node<T> * nodePtrPivot = S.front;
    for (int x = 0; x < half; x++)
    {
        nodePtrPivot = nodePtrPivot->right;
    }
    SE.enqueue(nodePtrPivot->key, nodePtrPivot->freq);

    // Divide ********************
    // Separate nodes groups: less than pivot, equal to pivot, greater than pivot
    Node<T> * nodePtr = S.front;
    for (int i = 0; (i < n && nodePtr != nullptr); i++)
    {
        iterator_count++;
        if (i != half)
        {
            //cout << iterator_count << endl;
            //cout << "compare: " << nodePtr->key << " AND " << nodePtrPivot->key << endl;
            if (nodePtr->key < nodePtrPivot->key)
            {
                SL.enqueue(nodePtr->key, nodePtr->freq);
                //cout << "\t push " << nodePtr->key << " to SL" << endl;
            }
            else if (nodePtr->key > nodePtrPivot->key)
            {
                SG.enqueue(nodePtr->key, nodePtr->freq);
                //cout << "\t push " << nodePtr->key << " to SG" << endl;
            }
            else
            {
                SE.enqueue(nodePtr->key, nodePtr->freq);
                //cout << "\t push " << nodePtr->key << " to SE" << endl;
            }
        }

        nodePtr = nodePtr->right;
    }
    //cout << "Divide END ---------------------------" << endl;
    //system("pause");

    // Recur ********************     
    iterator_count = quickSort(SL, iterator_count);
    iterator_count = quickSort(SG, iterator_count);

    // Conquer ********************
    S.clear();
    nodePtr = SL.front;
    while (nodePtr)
    {
        //iterator_count++;
        S.enqueue(nodePtr->key, nodePtr->freq);
        //cout << "\t push SL: " << nodePtr->key << " to S" << endl;
        nodePtr = nodePtr->right;
    }

    nodePtr = SE.front;
    while (nodePtr)
    {
        //iterator_count++;
        S.enqueue(nodePtr->key, nodePtr->freq);
        //cout << "\t push SE: " << nodePtr->key << " to S" << endl;
        nodePtr = nodePtr->right;
    }

    nodePtr = SG.front;
    while (nodePtr)
    {
        //iterator_count++;
        S.enqueue(nodePtr->key, nodePtr->freq);
        //cout << "\t push SG: " << nodePtr->key << " to S" << endl;
        nodePtr = nodePtr->right;
    }

    SL.clear();
    SE.clear();
    SG.clear();
    //cout << "END --------------------------------------------------------\n\n\n" << endl;
    return iterator_count;
}
// Implementation begin **********************************************************************************

