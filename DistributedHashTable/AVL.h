#pragma once
#include<iostream> 
#include<fstream>
#include<stack>
#include<cstdio>
#include<string>
using namespace std;

struct LinkedList {

    struct Node {
        string value;
        Node* Next;

        Node(string T = "");
    };

    int Length = 0;
    Node* Head = NULL;

    void insert(string val);                    //Insert val in the LinkedList
    string& insertAt(int Index, string newVal); //insert val at specified index 
    void Delete(int Index);                     //deletes value at specific index   
    string& get(int Index);                     //This function returns value at i'th index
    void display();
    int getLength();                            //Function to return length of LinkedList
    ~LinkedList();
};

int hashNumber(string key, int max);            //converts the hashed key to an integer

struct treeNode
{
    string key;
    int lineNumber;
    int height;
    treeNode* left, * right;
    treeNode(string k, int l);
};

struct AVL {
    treeNode* root;
    int lineCount;
    string filename;
    int count;
    int sum = 0;
    bool Lines[100];
    AVL();
    AVL(string f);
    bool isFilled();                                            //checks if the current file has reached 100 lines or not
    void setFileName(string f);                                 //sets file name
    void renameFile(string f);                                  //renames a file
    string ReadData(int lineNum);                               //reads data from the file into the linkedlist and displays the specified line
    bool WriteData(string key, int LN);                         //writes data to the file at the specified line no
    void DeleteData(int LN);                                    //deletes data at specified line no 
    int search(treeNode* node, string key);                     //searches the data in the tree on the basis of the key                     
    int getHeight(treeNode* node);                              //calculates and returns the height of the specified node
    treeNode* rightRotate(treeNode* RightNode);                 //shifts the left node to the right
    treeNode* leftRotate(treeNode* LeftNode);                   //shifts the right node to the left 
    int height(treeNode* N);                                    //returns the height of the node
    int getBalance(treeNode* node);                             //returns the balancing factor of the node
    treeNode* insert(treeNode* node, string key, string input);
    treeNode* leafNode(treeNode* node);                         //returns the leftmost leaf node of the tree
    treeNode* deleteNode(treeNode* node, string key);           //deletes the node
    void inOrder(treeNode* node);
    void preOrder(treeNode* node);
    LinkedList GetKeysFromFile(int ID, int max);                //reads keys from the file to a linkedlist
    LinkedList GetDataFromFile(int ID, int max);                //reads data from the file to a linkedlist

};