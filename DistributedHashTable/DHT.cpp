#include "DHT.h"

NodeAVL::NodeAVL(string filename) {
    this->filename = filename;
    tree.setFileName(filename);
    root = tree.root;
    next = NULL;
}
NodeAVL::NodeAVL(string filename, treeNode* root, AVL tree, NodeAVL* next) {
    this->filename = filename;
    this->root = root;
    this->tree = tree;
    this->next = next;
}
void NodeAVL::renameFile(string f) {
    tree.renameFile(f);
    filename = f;
}

LinkedAVL::LinkedAVL() {
    Head = NULL;
    Length = 0;
}
void LinkedAVL::insert(string filename) {
    if (Head == NULL) {
        Head = new NodeAVL(filename);
        Length++;
        return;
    }
    NodeAVL* temp = Head;
    while (temp->next) {
        temp = temp->next;
    }
    Length++;
    temp->next = new NodeAVL(filename);
}
void LinkedAVL::insert(NodeAVL* filename, int filecount) {
    cout << "Adding File: " << filename->filename << endl;
    if (Head == NULL) {
        Head = filename;
        Length++;
        return;
    }
    NodeAVL* temp = Head;
    while (temp->next) {
        temp = temp->next;
    }
    cout << "To Tree: " << temp->filename << endl;
    int newFile = stoi(temp->filename); // Get the Interger of the File
    filename->renameFile(to_string(newFile) + "_" + to_string(filecount) + ".txt"); // Rename the file
    Length++;

    temp->next = new NodeAVL(filename->filename, filename->root, filename->tree, filename->next);
}

bool LinkedAVL::isFilled(int Index) {
    NodeAVL* temp = Head;
    for (int i = 0; i < Index; i++) {
        temp = temp->next;
    }
    return temp->tree.isFilled();
}

NodeAVL* LinkedAVL::getTree(int Index) {
    NodeAVL* temp = Head;
    for (int i = 0; i < Index; i++) {
        temp = temp->next;
    }
    return temp;
}

treeNode* LinkedAVL::getRoot(int Index) {
    NodeAVL* temp = Head;
    for (int i = 0; i < Index; i++) {
        temp = temp->next;
    }
    return temp->root;
}

void LinkedAVL::setRoot(int Index, treeNode* newRoot) {
    NodeAVL* temp = Head;
    for (int i = 0; i < Index; i++) {
        temp = temp->next;
    }
    temp->root = newRoot;
}

bool LinkedAVL::Delete(string filename) {
    NodeAVL* cur = Head;
    NodeAVL* prev = Head;
    while (cur->filename != filename) {
        prev = cur;
        cur = cur->next;
    }

    prev->next = cur->next;
    Length--;
    delete cur;
    return true;
}

LinkedAVL::~LinkedAVL()
{
    NodeAVL* cur = Head;
    NodeAVL* next = Head;
    while (cur) {
        next = cur->next;
        delete cur;
        cur = next;
    }
    Head = NULL;
}

id_node::id_node(int i) {
    filecount = 1;
    file.insert(to_string(i) + ".txt");
    id = i;
    next = NULL;
    prev = NULL;
}

dht_node::dht_node(int i) {
    id = i;
}

// Inseting IDS
void id_insert(id_node*& head, int id) {
    id_node* newNode = new id_node(id);
    id_node* cur = head;
    id_node* prev = head;
    bool flag = false;
    if (cur == NULL) {
        cur = newNode;
        head = cur;
    }
    else if (id < cur->id) {
        newNode->next = cur;
        newNode->prev = head;
        head = newNode;
    }
    else {
        while (cur->next != NULL) {
            if (id < cur->id) {
                newNode->next = cur;
                cur->prev = newNode;
                newNode->prev = prev;
                prev->next = newNode;
                flag = true;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        if (flag == false) {
            if (id < cur->id) {
                newNode->next = cur;
                cur->prev = newNode;
                newNode->prev = prev;
                prev->next = newNode;

            }
            else {
                cur->next = newNode;
                newNode->prev = cur;
            }

        }
    }

}

// Displaying ids
void id_display(id_node* head) {
    while (head != NULL) {
        cout << "Id is = " << head->id << endl;
        head = head->next;
    }
}


//Geing ids at particular position
id_node* get_id(id_node* head, int i) {
    int j = 0;
    while (j != i) {
        j += 1;
        head = head->next;
    }
    //cout << "head id is = " << head->id << endl;
    return head;

}

int get_machine_id(id_node* head, int i) {
    int j = 0;
    while (j != i) {
        j += 1;
        head = head->next;
    }
    //cout << "head id is = " << head->id << endl;
    return head->id;

}

// getting position of the ids
int get_id_pos(id_node* head, int ids) {
    int j = 0;
    id_node* temp = head;
    while (temp->id != ids) {
        j += 1;
        temp = temp->next;
    }
    return j;
}

// Deleting ids 
void delete_id(id_node*& head, int ids) {
    int pos = get_id_pos(head, ids);
    if (pos == 0) {
        id_node* temp = head;
        head = head->next;
        head->prev = NULL;
        for (int j = 0; j < temp->filecount; j++) {
            head->file.insert(temp->file.getTree(j), head->filecount + (temp->filecount - j));
        }
        head->filecount += temp->filecount;
        cout << "Filecount is: " << head->filecount << endl;
        delete temp;
    }
    else {
        id_node* cur = head;
        id_node* prev = head;
        while (cur->id != ids) {
            prev = cur;
            cur = cur->next;
        }
        if (cur->next == NULL) {
            for (int j = 0; j < cur->filecount; j++) {
                head->file.insert(cur->file.getTree(j), head->filecount + (cur->filecount - j));
            }
            head->filecount += cur->filecount;
            cout << "Filecount is: " << head->filecount << endl;
            prev->next = NULL;
            delete cur;
        }
        else {
            prev->next = cur->next;
            cur->next->prev = cur->prev;
            prev = prev->next;
            for (int j = 0; j < cur->filecount; j++) {
                prev->file.insert(cur->file.getTree(j), head->filecount + (cur->filecount - j));
            }
            prev->filecount += cur->filecount;
            cout << "Filecount is: " << prev->filecount << endl;
            delete cur;
        }
    }
}

DHT::DHT() {
    head = NULL;
    bits = 0;
    max = 0;
    ids_length = 0;
    id_head = NULL;
    machines = 0;
}

DHT::DHT(int BITS, int MACHINES) {
    head = NULL;
    bits = BITS;
    max = (int)pow(2.0, (double)bits) - 1;
    machines = MACHINES;
    ids_length = 0;
    id_head = NULL;
}

void DHT::insert(int ID, string key, string input) {
    dht_node* temp = head;
    //cout << "\nPath for Insert!\n";
    while (temp->id != ID) {
        // cout << "Visiting ID " << temp->id << endl;
        temp = temp->next;
    }

    cout << "ID of Storage Found: " << temp->id << endl;
    id_node* insertNode = temp->successor;
    cout << "Inserting at Machine ID: " << insertNode->id << endl;
    int f = 0; // FileNumber
    for (int i = 0; i < insertNode->filecount; i++) {
        if (insertNode->file.isFilled(i) == false) {
            f = i;
            break;
        }
        else {
            if (i + 1 == insertNode->filecount) {
                insertNode->filecount++;
                insertNode->file.insert(to_string(insertNode->id) + "_" + to_string(i + 1) + ".txt");
                f = i + 1;
                break;
            }
        }
    }
    insertNode->file.setRoot(f, insertNode->file.getTree(f)->tree.insert(insertNode->file.getRoot(f), key, input));
    cout << "Do you want to Print the AVL tree? (y || Any): ";
    char c;
    cin >> c;
    if (c == 'y')
        insertNode->file.getTree(f)->tree.preOrder(insertNode->file.getRoot(f));

}

void DHT::deleteData(int ID, string key) {
    dht_node* temp = head;
    //cout << "\nPath for Insert!\n";
    while (temp->id != ID) {
        // cout << "Visiting ID " << temp->id << endl;
        temp = temp->next;
    }
    id_node* deleteNode = temp->successor;

    for (int i = 0; i < deleteNode->filecount; i++) {
        deleteNode->file.setRoot(i, deleteNode->file.getTree(i)->tree.deleteNode(deleteNode->file.getRoot(i), key));
    }
    cout << "Do you want to Print the AVL tree? (y || Any): ";
    char c;
    cin >> c;
    if (c == 'y') {
        for (int i = 0; i < deleteNode->filecount; i++) {
            deleteNode->file.getTree(i)->tree.preOrder(deleteNode->file.getRoot(i));
        }
    }
}
void DHT::search(int ID, string key) {

    dht_node* temp = head;
    while (temp != NULL) {

        if (temp->id == ID) {

            break;
        }
        temp = temp->next;
    }
    id_node* P = temp->successor;
    int E = ID;
    while (true) {
        dht_node* temp = head;
        bool found_id = false;
        bool found_in_table = false;
        //checking if id exists in the associated nodes of the current machine
        //p=e
        for (int j = 0; j <= max; j++) {

            if (P->id == temp->successor->id) {

                found_id = true;
            }
            temp = temp->next;
        }
        if (found_id)
            break;
        //p<e and e<=ftp[1]
        if (P->id < E && E <= P->routing_table.get_at(0)) {

            P = P->routing_table.get_machine(0);
            found_in_table = true;
        }
        else {

            //ftp[j]<e and e <=ftp[j+1]
            for (int j = 0; j < (P->routing_table.getLength() - 1); j++) {

                if (P->routing_table.get_at(j) < E && E <= P->routing_table.get_at(j + 1)) {

                    P = P->routing_table.get_machine(j);
                    found_in_table = true;
                    break;
                }
            }
        }
        if (found_in_table == false) {

            //moving to the last entry of ftp if neither of the case if true
            P = P->routing_table.get_machine(bits - 1);
        }
    }
    cout << "MACHINE ID:" << P->id << endl;
    id_node* searchNode = P;
    for (int i = 0; i < searchNode->filecount; i++) {
        if (searchNode->file.getTree(i)->tree.search(searchNode->file.getRoot(i), key) != -1) break;
        cout << "Not Found -> Next File " << endl;
    }
}
void DHT::distributeData(int choice) {
    id_node* newMachine = id_head;
    for (int i = 0; i < machines; i++) {
        if (choice == newMachine->id)
            break;
        newMachine = newMachine->next;
    }
    int startNodes = newMachine->prev->id + 1;
    int endNodes = newMachine->id;
    id_node* dataFile;
    if (newMachine->next != NULL)
        dataFile = newMachine->next;
    else
        dataFile = id_head;

    cout << "New Machine: " << newMachine->id << endl;
    cout << "Start Node: " << startNodes << endl;
    cout << "End Node: " << endNodes << endl;
    cout << "Data File : " << dataFile->id << endl;
    cout << "Filecount: " << dataFile->filecount << endl << endl;
    string input, key;
    for (int id = startNodes; id <= endNodes; id++) {
        for (int j = 0; j < dataFile->filecount; j++) {
            NodeAVL* temp = dataFile->file.getTree(j);
            LinkedList Keys = temp->tree.GetKeysFromFile(id, max);
            LinkedList Data = temp->tree.GetDataFromFile(id, max);
            for (int k = 0; k < Keys.getLength(); k++) {
                input = Data.get(k);
                key = Keys.get(k);
                if (input != "#Empty") {
                    insert(newMachine->id, key, input);
                    deleteData(dataFile->id, key);
                }

            }
            cout << "NEXT FILE" << endl;
        }
    }
}
void DHT::PrintAVL(int no) {
    int ID = get_machine_id(id_head, no - 1);
    dht_node* temp = head;
    //cout << "\nPath for Insert!\n";
    while (temp->id != ID) {
        // cout << "Visiting ID " << temp->id << endl;
        temp = temp->next;
    }
    id_node* deleteNode = temp->successor;
    for (int i = 0; i < deleteNode->filecount; i++) {
        deleteNode->file.getTree(i)->tree.preOrder(deleteNode->file.getRoot(i));
    }

}
// assigning ids and it takes a boolean as a paramete as we want to automatically assign ids or enter from use
void DHT::assign_ids(bool automatic) {

    if (automatic == true) {
        for (int i = 1; i <= machines; i++) {
            int num = 0 + (i * max) / (machines + 1);
            id_insert(id_head, num);
            ids_length++;
        }
    }
    else {
        for (int i = 1; i <= machines; i++) {
            int choice = 0;
            cout << "Please assign id to machine no " << i << " : ";
            cin >> choice;

            while (1) {
                bool found = false;
                for (int j = 0; j < ids_length; j++) {
                    if (get_machine_id(id_head, j) == choice) {
                        found = true;
                    }
                }
                if (found == false) {
                    break;
                }
                cout << "Please enter a different choice : ";
                cin >> choice;
            }

            id_insert(id_head, choice);
            ids_length++;

        }
    }
    create_nodes();
}

// Now creatin nodes of the dht which is circular and here you have to enter the input from the user and add it in dht
void DHT::create_nodes() {
    dht_node* temp = head;
    id_node* ntemp = id_head;
    bool flag = false;
    for (int i = 0; i <= max; i++) {
        if (temp == NULL) {
            temp = new dht_node(i);
            temp->next = temp;
            head = temp;

        }
        else
        {
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = new dht_node(i);
            temp->next->next = head;

        }
    }
    add_successors();
}

// adding successors of the assigned nodes above
void DHT::add_successors() {
    dht_node* temp = head;
    int j = 0;
    for (int i = 0; i <= max; i++) {
        if (i > get_machine_id(id_head, j)) {
            j += 1; // Move to next ID
        }
        if (i > get_machine_id(id_head, (machines - 1))) {
            j = 0; // Reset to first ID
        }
        temp->successor = get_id(id_head, j);
        //cout << "temp successor is = " << temp->successor << endl;
        temp = temp->next;
    }
}


// Displaying ids which are assigned
void DHT::display_ids() {
    id_display(id_head);

}

// Displays the dht with each nodes successor
void DHT::display_dht() {

    for (int i = 0; i < machines; i++) {
        cout << "Ids associated to me " << get_machine_id(id_head, i) << " are = ";
        dht_node* temp = head;
        for (int j = 0; j <= max; j++) {
            if (get_machine_id(id_head, i) == temp->successor->id) {
                cout << " ->" << temp->id;
            }
            temp = temp->next;
        }
        cout << endl;
    }


}

void DHT::add_machine() {

    machines++;
    char c;
    cout << "Do you want to assign an ID mannualy? (y || n): ";
    cin >> c;
    int choice = 0;
    if (c == 'y') {
        cout << "Please assign id to machine no " << machines << " : ";
        cin >> choice;
        bool found = false;
        bool OutOfRange = false;
        while (1) {
            found = false;
            OutOfRange = false;
            if (choice <0 || choice > max) OutOfRange = true;
            for (int j = 0; j < ids_length; j++) {
                if (get_machine_id(id_head, j) == choice) {
                    found = true;
                }
            }
            if (found == false && OutOfRange == false) {
                break;
            }
            cout << "Please enter a different choice : ";
            cin >> choice;
        }

        id_insert(id_head, choice);
        add_successors();
        distributeData(choice);
        ids_length++;
        id_node* nodeptr = id_head;
        while (nodeptr != NULL) {

            nodeptr->routing_table.Clear();
            nodeptr = nodeptr->next;
        }
        createfingertables();
    }
    else {
        int i = 0;
        string newStr = SHA1(to_string(i));
        int choice = hashNumber(newStr, max);
        while (1) {
            bool found = false;
            for (int j = 0; j < ids_length; j++) {
                cout << j + 1 << endl;
                if (get_machine_id(id_head, j) == choice) {

                    found = true;
                }
            }
            if (found == false) {
                break;
            }
            i++;
            newStr = SHA1(to_string(i));
            choice = hashNumber(newStr, max);
        }
        id_insert(id_head, choice);
        add_successors();
        distributeData(choice);
        ids_length++;
        id_node* nodeptr = id_head;
        while (nodeptr != NULL) {

            nodeptr->routing_table.Clear();
            nodeptr = nodeptr->next;
        }
        createfingertables();
    }
    Display_Node_ID();
}

void DHT::Display_Node_ID() {
    id_node* nodeptr = id_head;
    int i = 0;
    while (nodeptr != NULL) {
        cout << i + 1 << ". ";
        if (nodeptr->id != -1) {
            cout << nodeptr->id;
        }
        if (nodeptr->prev != NULL) {
            cout << " Not Null " << nodeptr->prev->id;
        }
        else {
            cout << " Null";
        }
        nodeptr = nodeptr->next;
        cout << endl;
        i++;
    }
}

void DHT::delete_machine(int id) {
    bool flag = false;
    id_node* temp = id_head;
    while (temp) {
        if (id == temp->id) {
            flag = true;
            break;
        }
        temp = temp->next;
    }
    if (!flag) {
        cout << "Invalid ID" << endl;
        return;
    }

    id_node* nodeptr = id_head;
    while (nodeptr != NULL) {

        nodeptr->routing_table.Clear();
        nodeptr = nodeptr->next;
    }
    machines--;
    int pos = get_id_pos(id_head, id);
    delete_id(id_head, id);
    ids_length--;
    add_successors();
    createfingertables();
    Display_Node_ID();
}

void DHT::createfingertables() {

    int M_no = 0;
    id_node* Machines = id_head;
    while (Machines != NULL) {

        int P = get_machine_id(id_head, M_no);
        int N = max + 1;
        int lengthoftable = (int)log2((double)N);
        dht_node* temp = head;
        for (int j = 0; j < lengthoftable; j++) {

            int i = (int)pow(2.0, (double)j) + P;
            if (i >= N) {

                i = i % N;
            }
            id_node* temp_P = id_head;
            bool tohead = true;
            while (temp_P != NULL) {

                if (temp_P->id >= i) {

                    tohead = false;
                    Machines->routing_table.insert(temp_P->id, temp_P);
                    break;
                }
                temp_P = temp_P->next;
            }
            if (tohead) {
                Machines->routing_table.insert(id_head->id, id_head);
            }
        }
        Machines = Machines->next;
        M_no++;
    }
}
void DHT::displayFTP(int M_no) {

    id_node* Machines = id_head;
    for (int i = 1; i < M_no; i++) {

        Machines = Machines->next;
    }
    Machines->routing_table.display();
}
DHT::~DHT() {

    //clearing ftp tables
    id_node* nodeptr = id_head;
    while (nodeptr != NULL) {

        nodeptr->routing_table.Clear();
        nodeptr = nodeptr->next;
    }
}


void Start() {
    string input, key;
    int bits = 4, machines = 5, max, ID, a;
    char c = 6;
    cout << "Distributed Hash Table" << endl;
    cout << "Enter the size of Identifier space: ";
    cin >> bits;
    cout << "Enter the number of Machines: ";
    cin >> machines;
    DHT dht(bits, machines);
    max = (int)pow(2.0, (double)bits) - 1;
    cout << "DHT created with " << bits << " bits and " << machines << " machines " << endl;
    cout << "Do you want to assign IDs Manually? (y || n): ";
    cin >> c;
    if (c == 'y') {
        dht.assign_ids(false);
    }
    else {
        cout << "Automatically assigning ids to machines " << endl;
        dht.assign_ids(true);
        cout << "Displaying ids" << endl;
        dht.display_ids();
    }

    dht.createfingertables();
    cout << "Your DHT is Ready!\n" << endl;
    cout << "1. Enter Data.\n";
    cout << "2. Retrive Data.\n";
    cout << "3. Delete Data.\n";
    cout << "4. Delete a Machine.\n";
    cout << "5. Add a Machine.\n";
    cout << "6. Display Machine IDs.\n";
    cout << "7. Display DHT.\n";
    cout << "8. Display Routing table.\n";
    cout << "9. Print AVL Tree.\n";
    cout << "Your Choice: ";
    cin >> a;
    while (a > 0) {
        if (a == 1) {

            cout << "1. Enter by Value.\n";
            cout << "2. Enter by Key & Value.\n";
            cout << "Your Choice: ";
            cin >> a;
            if (a == 1) {
                cout << "\nEnter Value: ";
                cin.ignore();
                getline(cin, input);
                key = SHA1(input);
                cout << "Do you want to select an ID? (y || n):";
                cin >> c;
                if (c == 'y') {
                    cout << "Enter ID: ";
                    cin >> a;
                    while (a < 0 || a > max) {
                        cout << "Invalid ID!\nEnter Again: ";
                        cin >> a;
                    }
                    ID = a;
                }
                else {
                    ID = hashNumber(key, max);
                }
                dht.insert(ID, key, input);

            }
            else if (a == 2) {
                cout << "\nEnter Key: ";
                cin.ignore();
                getline(cin, key);
                cout << "Enter Value: ";
                getline(cin, input);
                cout << "Do you want to select an ID? (y || n):";
                cin >> c;
                if (c == 'y') {
                    cout << "Enter ID: ";
                    cin >> a;
                    while (a < 0 || a > max) {
                        cout << "Invalid ID!\nEnter Again: ";
                        cin >> a;
                    }
                    ID = a;
                }
                else {
                    ID = hashNumber(key, max);
                }
                dht.insert(ID, key, input);

            }
        }
        else if (a == 2) {

            cout << "1. Search by Key.\n";
            cout << "2. Search by Value.\n";
            cout << "Your Choice: ";
            cin >> a;
            if (a == 1) {
                cout << "\nEnter Key: ";
                cin.ignore();
                getline(cin, key);
                ID = hashNumber(key, max);
                dht.search(ID, key);
            }
            else if (a == 2) {
                cout << "\nEnter Value: ";
                cin.ignore();
                getline(cin, input);
                key = SHA1(input);
                ID = hashNumber(key, max);
                cout << "ID is " << ID << endl;
                dht.search(ID, key);

            }

        }
        else if (a == 3) {
            cout << "1. Delete by Key.\n";
            cout << "2. Delete by Value.\n";
            cout << "Your Choice: ";
            cin >> a;
            if (a == 1) {
                cout << endl;
                cout << "Enter Key: ";
                cin.ignore();
                getline(cin, key);
                ID = hashNumber(key, max);
                dht.deleteData(ID, key);
            }
            else if (a == 2) {
                cout << "Enter Value: ";
                cin.ignore();
                getline(cin, input);
                key = SHA1(input);
                ID = hashNumber(key, max);
                dht.deleteData(ID, key);

            }
        }
        else if (a == 4) {
            cout << "Select a Machine ID to Delete: ";
            cin >> ID;
            while (1) {
                if (a > max || a < 0) {
                    cout << "Invalid ID!\n";
                    cout << "Please Enter again: ";
                    cin >> ID;
                }
                else {
                    break;
                }
            }
            dht.delete_machine(ID);
            machines--;
            //dht.display_dht();
        }
        else if (a == 5) {

            dht.add_machine();
            machines++;
            //dht.display_dht();
        }
        else if (a == 6) {
            dht.display_ids();
        }
        else if (a == 7) {
            dht.display_dht();
        }
        else if (a == 8) {

            int Machine_no;
            cout << "Enter Machine no:";
            cin >> Machine_no;
            while (Machine_no < 1 || Machine_no > machines) {

                cout << "Please Enter valid Machine no:";
                cin >> Machine_no;
            }
            dht.displayFTP(Machine_no);
        }
        else if (a == 9) {
            int Machine_no;
            cout << "Enter Machine no: ";
            cin >> Machine_no;
            while (Machine_no < 1 || Machine_no > machines) {

                cout << "Please Enter valid Machine no: ";
                cin >> Machine_no;
            }
            dht.PrintAVL(Machine_no);
        }
        else {
            cout << "Invalid Choice!\nEnter Again( q to exit ): ";
            cin >> a;
        }
        cout << endl;
        cout << "1. Enter Data.\n";
        cout << "2. Retrive Data.\n";
        cout << "3. Delete Data.\n";
        cout << "4. Delete a Machine.\n";
        cout << "5. Add a Machine.\n";
        cout << "6. Display Machine IDs.\n";
        cout << "7. Display DHT.\n";
        cout << "8. Display Routing table.\n";
        cout << "9. Print AVL Tree.\n";
        cout << "Your Choice (-1 to Exit): ";
        cin >> a;

    }
}