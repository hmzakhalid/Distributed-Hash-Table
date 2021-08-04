#include "FTP.h"

node::node() {

	data = 0;
	val = NULL;
	next = previous = NULL;
}

node::node(int value, id_node* v) {

	val = v;
	data = value;
	next = previous = NULL;
}

FTP::FTP() {

	head = NULL;
	length = 0;
}

void FTP::insert(int value, id_node* v) {

	if (head == NULL) {

		head = new node(value, v);
		length++;
	}
	else {

		node* temp = head;
		while (temp->next != NULL) {

			temp = temp->next;
		}
		temp->next = new node(value, v);
		temp->next->previous = temp;
		length++;
	}
}

int FTP::getLength() const {

	return length;
}

void FTP::remove(int value) {

	if (head == NULL) {

		cout << "List is already empty" << endl;
	}
	else {

		node* temp = head;
		while (temp->data != value) {

			temp = temp->next;
			if (temp == NULL)
				break;
		}
		if (temp == NULL) {

			cout << value << " didn't match with any node" << endl;
			return;
		}
		if (temp == head) {

			head = head->next;
			temp->next->previous = temp->previous;
			delete temp;
		}
		else if (temp->next == NULL) {

			temp->previous->next = temp->next;
			delete temp;
		}
		else {

			temp->next->previous = temp->previous;
			temp->previous->next = temp->next;
			delete temp;
		}
	}
}

int FTP::get_at(int index) {

	node* temp = head;
	for (int i = 1; i <= index; i++) {

		temp = temp->next;
	}
	return temp->data;
}

id_node* FTP::get_machine(int index) {

	node* temp = head;
	for (int i = 1; i <= index; i++) {

		temp = temp->next;
	}
	return temp->val;
}

void FTP::display() {

	cout << "Table:" << endl;
	node* temp = head;
	int i = 1;
	while (temp != NULL) {

		cout << i << "\t" << temp->data << endl;
		temp = temp->next;
		i++;
	}
}

void FTP::Clear() {

	node* temp = head;
	while (temp != NULL) {

		node* del = temp;
		temp = temp->next;
		delete del;
	}
	head = NULL;
}

FTP::~FTP() {
	Clear();
}