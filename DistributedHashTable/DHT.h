#ifndef DHT_H
#define DHT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include "AVL.h"
#include "FTP.h"
#include "SHA1.h"
using namespace std;


struct NodeAVL {
    string filename;
    treeNode* root;
    AVL tree;
    NodeAVL* next;
    NodeAVL(string filename);
    NodeAVL(string filename, treeNode* root, AVL tree, NodeAVL* next);
    void renameFile(string f);  //renames the file
};

struct LinkedAVL {
    NodeAVL* Head;
    int Length;
    LinkedAVL();
    void insert(string filename);
    void insert(NodeAVL* filename, int filecount);
    bool isFilled(int Index);                       //checking if the tree is filled of the specified machine
    NodeAVL* getTree(int Index);                    //get tree of the specified index
    treeNode* getRoot(int Index);                   //get root of the specified index
    void setRoot(int Index, treeNode* newRoot);     //set the root of the specified index
    bool Delete(string filename);                   //deletes the file
    ~LinkedAVL();
};


// Machine Nodes
struct id_node {
    int id;
    LinkedAVL file;
    FTP routing_table;
    int filecount;
    id_node* next;
    id_node* prev;
    id_node(int i = -1);
};


// Dht Node where you have to change the data members
struct dht_node {
    int id;
    id_node* successor;
    dht_node* next;
    dht_node(int i);
};


// Inseting IDS
void id_insert(id_node*& head, int id);

// Displaying ids
void id_display(id_node* head);


//Geing ids at particular position
id_node* get_id(id_node* head, int i);

//get machine id at specified index
int get_machine_id(id_node* head, int i);

// getting position of the ids
int get_id_pos(id_node* head, int ids);

// Deleting ids 
void delete_id(id_node*& head, int ids);

// DHT Class 
class DHT {
    dht_node* head;
    id_node* id_head;
    int bits;
    int max;
    int machines;
    int ids_length;

public:
    DHT();
    DHT(int BITS, int MACHINES);
    void insert(int ID, string key, string input);
    void deleteData(int ID, string key);
    void search(int ID, string key);    //searches the key in the machines
    void distributeData(int choice);
    void PrintAVL(int no);              //prints avl of the specified machine no
    // assigning ids and it takes a boolean as a paramete as we want to automatically assign ids or enter from use
    void assign_ids(bool automatic);
    // Now creatin nodes of the dht which is circular and here you have to enter the input from the user and add it in dht
    void create_nodes();
    // adding successors of the assigned nodes above
    void add_successors();
    // Displaying ids which are assigned
    void display_ids();
    // Displays the dht with each nodes successor
    void display_dht();
    //adds a machine to the dht
    void add_machine();
    //display ids of the dht nodes
    void Display_Node_ID();
    //deletes the machine of the dht
    void delete_machine(int id);
    void createfingertables();  //creates finger tables for every machine
    void displayFTP(int M_no);  //displays finger table of the machine no
    ~DHT();
};

void Start(); // Start DHT


#endif // !DHT_H