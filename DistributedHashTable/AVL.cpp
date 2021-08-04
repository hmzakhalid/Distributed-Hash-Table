#include "AVL.h"

LinkedList::Node::Node(string T) {
    value = T;
    Next = NULL;
}

//Insert val in the LinkedList
void LinkedList::insert(string val) {
    Node* temp = new Node(val);
    if (Head == NULL) {
        Head = temp;
        Length++;
    }
    else {
        Node* cur = Head;
        while (cur->Next != NULL) {
            cur = cur->Next;
        }
        cur->Next = temp;
        Length++;
    }

}

string& LinkedList::insertAt(int Index, string newVal) {
    Node* cur = Head;
    for (int i = 0; i < Index; i++) {
        cur = cur->Next;
    }
    cur->value = newVal;
    return cur->value;
}

void LinkedList::Delete(int Index) {
    if (Index == 0) {
        Head = Head->Next;
        return;
    }
    Node* cur = Head;
    Node* prev = Head;
    for (int i = 0; i < Index; i++) {
        prev = cur;
        cur = cur->Next;
    }
    prev->Next = cur->Next;
    Length--;
    delete cur;
}

//This function returns value at i'th index
string& LinkedList::get(int Index) {
    Node* cur = Head;
    for (int i = 0; i < Index; i++) {
        cur = cur->Next;
    }
    return cur->value;
}

void LinkedList::display() {
    Node* cur = Head;
    int i = 1;
    while (cur != NULL) {
        cout << "Value of Node " << i << ": " << cur->value << endl;
        cur = cur->Next;
        i++;
    }
}
//Function to return length of LinkedList
int LinkedList::getLength() {
    return Length;
}

LinkedList::~LinkedList()
{
    /*Node* cur = Head;
    Node* next;
    while (cur) {
        next = cur->Next;
        delete cur;
        cur = next;
    }
    Head = NULL;*/
}

int hashNumber(string key, int max) {
    int hashs = 0;
    for (size_t i = 0; i < key.size(); i++) {
        hashs += key[i];
    }
    return hashs % max;
}


treeNode::treeNode(string k, int l) {
    key = k;
    lineNumber = l;
    height = 1;
    left = right = NULL;
}

AVL::AVL() {
    for (int i = 0; i < 100; i++) {
        Lines[i] = false;
    }
    root = NULL;
    lineCount = 0;
    filename = "";
    count = 0;
    sum = 0;
}

AVL::AVL(string f) {
    for (int i = 0; i < 100; i++) {
        Lines[i] = false;
    }
    root = NULL;
    lineCount = 0;
    filename = f;
    count = 0;
    sum = 0;
    ofstream myfile(f);
    myfile.close();
}

bool AVL::isFilled() {
    for (int i = 0; i < 100; i++) {
        if (Lines[i] == false) {
            return false;
        }
    }
    return true;
}

void AVL::setFileName(string f) {
    filename = f;
    ofstream myfile(f);
    myfile.close();
}

void AVL::renameFile(string f) {
    rename(filename.c_str(), f.c_str());
    filename = f;
}

string AVL::ReadData(int lineNum) {
    LinkedList List;
    string line;
    ifstream readFile(filename);
    if (readFile.is_open())
    {
        while (getline(readFile, line))
        {
            List.insert(line);
        }
        readFile.close();
    }
    else {
        cout << "Unable to open file";
    }
    if (lineNum == 1)
        List.display();
    line = List.get(lineNum);
    if (line != "#Empty") {
        cout << "Data Found: ";
        cout << line << endl;
        return line;
    }
    else {
        cout << "Data does not Exist!" << endl;
    }
    return line;
}

bool AVL::WriteData(string key, int LN) {
    // Linked List to Store the Data from textfile
    LinkedList List;
    // Reading the file
    string line;
    ifstream readFile(filename);
    if (readFile.is_open())
    {
        while (getline(readFile, line))
        {
            List.insert(line);
        }
        readFile.close();
    }
    else {
        cout << "Unable to open file";
        return false;
    }

    // if Max Length Reached
    if (List.getLength() == 100) return false;
    // 
    if (LN >= List.getLength()) {
        List.insert(key);
    }
    else if (List.get(LN) == "#Empty") {
        List.insertAt(LN, key);
    }
    else {
        List.insert(key);
    }
    ofstream writeFile(filename);
    if (writeFile.is_open())
    {
        for (int i = 0; i < List.getLength(); i++) {
            writeFile << List.get(i) << endl;
        }
        writeFile.close();
        return true;
    }
    else cout << "Unable to open file";
    return false;
}

void AVL::DeleteData(int LN) {
    //cout << LN << endl;
    LinkedList List;
    string line;
    ifstream readFile(filename);
    if (readFile.is_open())
    {
        while (getline(readFile, line))
        {
            List.insert(line);
        }
        readFile.close();
    }
    else {
        cout << "Unable to open file";
    }

    List.insertAt(LN, "#Empty");
    ofstream writeFile(filename);
    if (writeFile.is_open())
    {
        for (int i = 0; i < List.getLength(); i++) {
            line = List.get(i);
            if (line != "")
                writeFile << line << endl;
        }
        writeFile.close();
    }
    else cout << "Unable to open file";
}

int AVL::search(treeNode* node, string key) {
    static int LN = -1;
    if (node == NULL)
        return -1;

    if (node->key == key) {
        LN = node->lineNumber;
        //ReadData(LN);
    }

    if (key < node->key)
        search(node->left, key);
    else
        search(node->right, key);

    return LN;
}

int AVL::getHeight(treeNode* node) {
    int a = 0, b = 0;
    if (node->left) {
        a = node->left->height;
    }
    if (node->right) {
        b = node->right->height;
    }
    if (a < b) return b + 1;
    return a + 1;

}

treeNode* AVL::rightRotate(treeNode* RightNode)
{
    treeNode* LeftNode = RightNode->left;
    RightNode->left = LeftNode->right;
    LeftNode->right = RightNode;
    RightNode->height = getHeight(RightNode);
    LeftNode->height = getHeight(LeftNode);
    return LeftNode;
}

treeNode* AVL::leftRotate(treeNode* LeftNode)
{
    treeNode* RightNode = LeftNode->right;
    LeftNode->right = RightNode->left;
    RightNode->left = LeftNode;
    LeftNode->height = getHeight(LeftNode);
    RightNode->height = getHeight(RightNode);
    return RightNode;
}

int AVL::height(treeNode* N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int AVL::getBalance(treeNode* node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

treeNode* AVL::insert(treeNode* node, string key, string input)
{
    if (root == NULL) {
        ofstream writeFile(filename);
        if (writeFile.is_open())
        {
            writeFile << input << endl;
            writeFile.close();
        }
        else cout << "Unable to open file";

        for (int i = 0; i < 100; i++) {
            if (Lines[i] == false) {
                Lines[i] = true;
                lineCount = i;
                break;
            }
        }
        root = new treeNode(key, lineCount);
        return root;
    }
    if (node == NULL) {
        for (int i = 0; i < 100; i++) {
            if (Lines[i] == false) {
                Lines[i] = true;
                lineCount = i;
                break;
            }
        }
        WriteData(input, lineCount);
        treeNode* temp = new treeNode(key, lineCount);
        return temp;
    }

    if (key < node->key) node->left = insert(node->left, key, input);
    else if (key > node->key) node->right = insert(node->right, key, input);
    else return node;


    node->height = getHeight(node);
    int balance = getBalance(node);


    // LLC
    if (balance > 1 && key < node->left->key) return rightRotate(node);
    // RRC
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    // LRC
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RLC  
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    root = node;
    return node;
}

treeNode* AVL::leafNode(treeNode* node)
{
    treeNode* temp = node;
    while (temp && temp->left)
        temp = temp->left;

    return temp;
}

treeNode* AVL::deleteNode(treeNode* node, string key)
{

    if (node == NULL) return node;

    // Search the Value
    if (key == node->key) // After Value Found
    {
        /*cout << node->key << endl;
        cout << key << endl;*/

        if (node->left == NULL) // With 1 Node
        {
            Lines[node->lineNumber] = false;
            DeleteData(node->lineNumber);
            treeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL) // Leaf Node
        {
            Lines[node->lineNumber] = false;
            DeleteData(node->lineNumber);
            treeNode* temp = node->left;
            delete node;
            return temp;
        }
        treeNode* temp = leafNode(node->right); // With 2 Nodes
        int ln = node->lineNumber;
        string k = node->key;
        node->key = temp->key;
        node->lineNumber = temp->lineNumber;
        temp->key = k;
        temp->lineNumber = ln;
        node->right = deleteNode(node->right, temp->key);
    }
    else if (key < node->key) node->left = deleteNode(node->left, key);
    else if (key > node->key)node->right = deleteNode(node->right, key);
    return node;
}

void AVL::inOrder(treeNode* node)
{
    if (node != NULL)
    {
        inOrder(node->left);
        cout << "key: " << node->key << " Line: " << node->lineNumber << endl;
        inOrder(node->right);
    }
}

void AVL::preOrder(treeNode* node)
{
    if (node != NULL)
    {
        cout << "key: " << node->key << " Line: " << node->lineNumber << endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

LinkedList AVL::GetKeysFromFile(int ID, int max) {
    LinkedList List;
    stack<treeNode*> s;
    treeNode* curr = root;
    while (curr != NULL || s.empty() == false)
    {
        while (curr != NULL)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();

        if (hashNumber(curr->key, max) == ID) {
            List.insert(curr->key);
        }

        curr = curr->right;

    }
    return List;
}

LinkedList AVL::GetDataFromFile(int ID, int max) {
    LinkedList List;
    stack<treeNode*> s;
    treeNode* curr = root;
    int LN;
    string temp;
    while (curr != NULL || s.empty() == false)
    {
        while (curr != NULL)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();

        if (hashNumber(curr->key, max) == ID) {
            LN = search(root, curr->key);
            temp = ReadData(LN);
            List.insert(temp);
        }

        curr = curr->right;

    }
    //List.display();
    return List;
}