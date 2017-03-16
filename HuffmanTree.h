///////////////////////////////////////////////////////////
//  Huffman
//  Created on:  11/15/2016
//  Author: Robert T
//  IDE Used: Microsoft Visual Studio 2013
///////////////////////////////////////////////////////////
#ifndef _HUFFMAN_TREE
#define _HUFFMAN_TREE

#include <iostream>
#include <math.h>


#include "PriorityQueue.h"
#include "Hashing.h"

// definition begin ********************************************************************************

template <class T>
class HuffmanTree
{

private:
    int size = 0;               // the tree size, that is, the number of nodes in the tree
    int encodeStrLength, decodeStrLength;
    HashMap<char, string, int> * Hash = nullptr;

public:
    Node<T> * root = nullptr;   // a pointer to the root of the tree.

    HuffmanTree()
    {
        root = nullptr;        
    }

    Node<T> * getRoot()
    {
        return root;
    }

    int getSize()
    {
        return size;
    }

    void buildTreeFromHeap(PriorityQueue<T> & heap)
    {               
        Hash = new HashMap<char, string, int>(heap.count);

        //cout << heap.count << endl; system("pause");
        buildTree(heap, heap.count);

        //cout << "-------------------------------------------" << endl;
        assignCode(root);
        //inOrder(root, 0);

        
        add2Hash(root);
        //system("pause");
    }

    void buildTree(PriorityQueue<T> & heap, int treeCount)
    {
        
        Node<T> *nodePtr = heap.front;
        Node<T> *newNodeR, *newNodeL;
        Node<T> *newBranch, *rootBranch;

        while (heap.count && treeCount > 0)
        {
            nodePtr = heap.min();
            newNodeR = new Node<T>(nodePtr->key);
            size++;
            treeCount--;
            //cout << nodePtr->key << " = " << newNodeR->getSymbol() << endl;
            heap.removeMin();


            // create branch
            if (heap.count)
            {
                nodePtr = heap.min();
                newNodeL = new Node<T>(nodePtr->key);
                size++;
                treeCount--;
                //cout << nodePtr->key << " = " << newNodeL->getSymbol() << endl;
                heap.removeMin();

                // two nodes
                newBranch = new Node<T>(newNodeL, newNodeR);
                //cout << "Branch1: " << newBranch->getSymbol() << endl;
            }
            else // one node
            {
                newBranch = new Node<T>(newNodeR);
                //newBranch = newNodeR;
                //cout << "Branch2: " << newBranch->getSymbol() << endl;
            }

            // creat root branch
            if (root == nullptr)
            {
                root = newBranch;
                //cout << "root1: " << root->getSymbol() << endl;
                //cout << "left: " << root->left->getSymbol() << endl;
                //cout << "right: " << root->right->getSymbol() << endl;
            }
            else
            {
                //cout << "root2: " << newBranch->getSymbol() << endl;
                //cout << "left: " << newBranch->left->getSymbol() << endl;
                //cout << "right: " << newBranch->right->getSymbol() << endl;

                //cout << "inorder" << endl;
                //inOrder(newBranch, 0);

                //cout << "inorder" << endl;
                //inOrder(root, 0);

                rootBranch = new Node<T>(newBranch, root);
                root = rootBranch;

                //inOrder(root, 0);
                //system("pause");

            }


            //cout << "size: "<< heap.getCurrentSize() << endl;
            //system("pause");

        }       
        

        adjustTree(heap, treeCount);
        //system("pause");
    }

    void adjustTree(PriorityQueue<T> & heap, int treeCount)
    {
        Node<T> *nodePtr = heap.front;
        Node<T> *newNodeL;
        Node<T> *newBranch;

        // Adjust tree ------------------------------------------------
        int totalRightCount = 0;
        nodePtr = root;
        while (nodePtr)
        {
            nodePtr = nodePtr->right;
            totalRightCount++;
        }

        //cout << "root:" << root->key << endl;

        int adjustAt = totalRightCount /2;
        int beforeAdjustNode = adjustAt-1;
        //cout << adjustAt << "/" << totalRightCount << endl;

        nodePtr = root;
        while (adjustAt > 0)
        {
            nodePtr = nodePtr->right;
            adjustAt--;
        }
        //cout << "adjust at: " << nodePtr->key << endl;

        // find left node leaf
        newNodeL = root->left;
        //cout << "move under: " << newNodeL->key << endl;
        newBranch = new Node<T>(newNodeL, nodePtr);
        root->left = newBranch;

        // remove moved right node
        nodePtr = root;
        while (beforeAdjustNode > 0)
        {
            nodePtr = nodePtr->right;
            beforeAdjustNode--;
        }
        nodePtr->right = nullptr;
        //cout << "remove: " << nodePtr->key << endl;
    }
    
    void add2Hash(Node<T> * nodePtr)
    {
        if (nodePtr != NULL)
        {
            add2Hash(nodePtr->right);

            if (nodePtr->left == nullptr && nodePtr->right == nullptr)
            {
                //cout << nodePtr->getSymbol() << " = ascii: " << (int) nodePtr->getSymbol() << " (" << nodePtr->code << ") " << endl;
                Hash->put(nodePtr->getSymbol(), nodePtr->code);
            }

            add2Hash(nodePtr->left);
        }
    }

    void insert(T x)
    {
        Node<T> * newNode = new Node<T>(x);
        Node<T> * nodePtr;
        size++;

        cout << "insert: " << x;

        nodePtr = root;
        if (nodePtr == NULL)
        {
            root = newNode;
            cout << " in Root " << endl;
        }
        else
        {
            bool exit = false;
            do
            {
                if (x < nodePtr->data) // Goes to left
                {
                    cout << " <<< Left ";
                    if (nodePtr->right == NULL)
                    {
                        nodePtr->right = newNode;
                        exit = true;
                        cout << endl;
                    }
                    else
                    {
                        nodePtr = nodePtr->right;
                    }
                }
                else // Goes to right
                {
                    cout << " Right >>> ";
                    if (nodePtr->right == NULL)
                    {
                        nodePtr->right = newNode;
                        exit = true;
                        cout << endl;
                    }
                    else
                    {
                        nodePtr = nodePtr->right;
                    }
                }
            } while (exit == false && nodePtr);
        }
    }

    void search(Node<T> * nodePtr, T x, string & code )
    {
        if (nodePtr != NULL)
        {
            search(nodePtr->right, x, code);

            // Is leaf and is found
            if (nodePtr->left == nullptr && nodePtr->right == nullptr && nodePtr->getSymbol() == x)
            {
                //cout << nodePtr->getSymbol() << " (" << nodePtr->code << ") " << endl;
                code = nodePtr->code;
                return;
            }            

            search(nodePtr->left, x, code);
        }
    }

    void parent(int x)
    {
        --x;
        while (x != 0)
        {
            x--;
            cout << "---|";
        }
    }

    void assignCode(Node<T> * nodePtr, string code = "", int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;
            assignCode(nodePtr->right, code + "1", level);

            //parent(level);

            nodePtr->code = code;
            //cout << nodePtr->getSymbol() << " (" << nodePtr->code << ") " << endl;

            assignCode(nodePtr->left, code + "0", level);
        }
    }

    int bits2Int(string str)
    {
        int ch = 0;
        int i = 7;
        for (i = 7; i >= 0; i--)
        {
            if (str[i] == '1')
            {
                ch += pow(2, (double)(7 - i));
            }

        }
        return ch;
    }

    char bits2char(string str)
    {
        char ch = 0;
        int i = 7;
        for (i = 7; i >= 0; i--)
        {
            if (str[i] == '1')
            {
                ch += (int) pow(2, (double)(7 - i));
            }

        }
        return ch;
    }

    string charToBits(char ch)
    {
        int num = static_cast<unsigned char>(ch);
        string bits = "";

        for (int i = 7; i >= 0; i--)
        {
            if (num - pow(2, i) >= 0) 
            {
                num -= (int) pow(2, i);
                bits += "1";
            }
            else bits += "0";
        }
        return bits;
    }

    int getEncodeStringLength()
    {
        return encodeStrLength;
    }

    int getDecodeStringLength()
    {
        return decodeStrLength;
    }

    string dumpTree(Node<T> * nodePtr, string ret) // pre-order
    {

        if (nodePtr)
        {
            if (nodePtr->left == nullptr && nodePtr->right == nullptr) // is leaf
            {
                ret = ret + nodePtr->code +nodePtr->key + "|";
                //cout << ret << endl; system("pause");
            }
            
            if (nodePtr->left)
            {
                ret = dumpTree(nodePtr->left, ret);
            }
            


            if (nodePtr->right)
            {
                ret = dumpTree(nodePtr->right, ret);
            }
            

            return ret;
        }
    }

    void encode(string infile, string outfile)
    {
        fstream dataInfile, dataOutfile;
        string line, code, str, eight;;
        int strlength;
        char c;

        dataInfile.open(infile);
        if (dataInfile.fail())
        {
            cout << "Error: couldn't open the input file '" << infile << "'." << endl;
            return;
        }
        else
        {

            dataOutfile.open(outfile, ios::out);
            if (dataOutfile.fail())
            {
                cout << "Error: couldn't open the output file '" << outfile << "'." << endl;
                return;
            }
            else
            {
                //cout << "Encoding, please wait a moment..." << endl;
            }

            
            // encode each char to bit as string - eg '00100100'            
            while (getline(dataInfile, line))
            {
                line += "\r\n";
                strlength = line.length();
                for (int i = 0; i < strlength; i++)
                {
                    c = line[i];
                    search(root, c, code);
                    //code = Hash->get(c);

                    str = str + code;
                    //cout << c << " = " << code << endl;                
                }
            }
            //cout << str << endl;
            
            // tree length
            int times =0;
            encodeStrLength = str.length();
            // write length
            dataOutfile << encodeStrLength << endl;

            // tree as string
            string treeString = dumpTree(root, "");
            dataOutfile << "<tree>" + treeString + "</tree>" << endl;


            // convert string to bit
            while (str.length() >= 8)
            {
                times++;
                eight = str.substr(0, 8);
                str = str.substr(8, str.length() - 8);
                //cout << eight << "\t" << bits2char(eight) << endl;
                //dataOutfile << (eight) << endl;
                dataOutfile << bits2char(eight);
            }

            // fill trailing zero to make it 8-bit long
            if (str.length()>0)
            {
                //cout << "remain: " << str << endl;
                while (str.length() % 8)
                {
                    str += '0';
                }
                dataOutfile << bits2char(str);
                //cout << "fill as:" << str << endl;
            }
            
            //system("pause");
            
            dataOutfile.close();
            dataInfile.close();
            //cout << "Done. Saved to file \"" << outfile << "\"" << endl;

            
            //inOrder(root);
        }
    }

    void decode(string infile, string outfile)
    {

        fstream dataInfile, dataOutfile;
        string line, code, str;
        int strlength;
        Node<T> * nodePtr = root;
        char c;


        dataInfile.open(infile);
        if (dataInfile.fail())
        {
            cout << "Error: couldn't open the input file '" << infile << "'. Please do encode first." << endl;
            return;
        }
        else
        {
            dataOutfile.open(outfile, ios::out);
            if (dataOutfile.fail())
            {
                cout << "Error: couldn't open the output file '" << outfile << "'. " << endl;
                return;
            }
            else
            {
                cout << "Decoding, please wait a moment..." << endl;
            }
            

            // decode each char to bit string - eg '00100100'
            int rows = 0;
            while (getline(dataInfile, line))
            {
                rows++;
                if (rows==1) // read length
                {
                    encodeStrLength = atoi(line.c_str());
                    continue;
                }

                strlength = line.length();
                for (int i = 0; i < strlength; i++)
                {
                    str += charToBits(line[i]);
                    //cout << line << endl;
                    //system("pause");
                }
            }
                      
            decodeStrLength = str.length();

            /*cout << str << endl;             
            cout << decodeStrLength << endl;
            system("pause");*/


            // convert bit to char
            for (int i = 0; i < getEncodeStringLength(); i++)
            {
                c = str[i];
                code += c;
                //cout << "c: " << c << endl;

                if (c== '1')
                {
                    nodePtr = nodePtr->right;
                    //cout << ">>> 1 to right" << endl;
                }
                else // c==0
                {
                    nodePtr = nodePtr->left;
                    //cout << ">>> 0 to left" << endl;
                }

                // determine, weather is leaf or not
                if (nodePtr->left == nullptr && nodePtr->right == nullptr)
                {
                    dataOutfile << (nodePtr->key);
                    //cout << code << " = " << nodePtr->key << endl; system("pause");

                    nodePtr = root;
                    code = "";
                }
                
            }
            

            //system("pause");
            dataOutfile.close();
            dataInfile.close();
            cout << "Done. Saved to file \"" << outfile << "\"" << endl;
        }
    }

    void inOrder(Node<T> * nodePtr, int level = 0)
    {        
        if (nodePtr != NULL)
        {
            ++level;            
            inOrder(nodePtr->right, level);
            parent(level);
            cout << nodePtr->getSymbol() << " (" << nodePtr->code << ") " << endl;
            inOrder(nodePtr->left, level);
        }
    }

    void preOrder(Node<T> * nodePtr, int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;

            parent(level);
            cout << nodePtr->data << endl;
            preOrder(nodePtr->left, level);
            preOrder(nodePtr->right, level);
        }
    }

    void postOrder(Node<T> * nodePtr, int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;
            postOrder(nodePtr->left, level);
            postOrder(nodePtr->right, level);
            parent(level);
            cout << nodePtr->data << endl;
        }
    }
   
};

#endif
// definition end **********************************************************************************