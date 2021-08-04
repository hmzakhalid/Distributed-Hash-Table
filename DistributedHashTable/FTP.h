#ifndef FTP_H
#define FTP_H

#include <iostream>
using namespace std;

struct id_node;

struct node {

	int data;
	id_node* val;
	node* next;
	node* previous;
	node();
	node(int value, id_node* v);
};


class FTP {
	node* head;
	int length;
public:
	FTP();
	void insert(int value, id_node* v);	//inserts a node and pointer to the machine
	int getLength() const;				//get length of the linkedlist
	void remove(int value);				//delete a node by value
	int get_at(int index);				//get value at index
	id_node* get_machine(int index);	//get machine pointer at index
	void display();						//displays the list
	void Clear();						//deletes the whole list
	~FTP();
};

#endif // !FTP_H
