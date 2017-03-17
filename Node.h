#ifndef _TREE_NODE
#define _TREE_NODE

#include <iostream>
#include <string>

///////////////////////////////////////////////////////////
//  Tree Node
//  Created on:  11/15/2016
//  Author: Robert T
//  IDE Used: Microsoft Visual Studio 2013
///////////////////////////////////////////////////////////
using namespace std;

// Node class
template <class T>
class Node
{

public:
    T key;
    string val;
    int freq = 0;
    string code;

    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    

    // Constructors
    Node()
    {
    }

    Node(T akey)
    {
        key = akey;
        freq = 1;
    }

    Node(T akey, T aVal)
    {
        key = akey;
        val = aVal;
        freq = 1;
    }

    Node(Node* n1) : left(n1) {
        key = left->getSymbol();
        freq = left->freq;
    };

    Node(Node* n0, Node* n1) : left(n0), right(n1)
    {
        key = left->getSymbol() + right->getSymbol();
        freq = left->freq + right->freq;
    };

    int getFreq()
    {
        return freq;
    }

    T getSymbol()
    {
        return key;
    }

};

#endif;