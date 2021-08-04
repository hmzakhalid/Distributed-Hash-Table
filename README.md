# Distributed-Hash-Table
A Simulation of Distributed Hash table coded in C++ that includes
1. Option to specify the number of machines.
2. Option to specify the size of identifier space in bits, i.e., 160 bits, 4 bits etc.
3. Option to manually assign Id to each machine. If manual Ids are not assigned by the user, the
system must automatically assign Ids.
4. Option to insert data in the form of key, value pairs from any machine. The insertion must show the
complete path taken by the request to arrive at the correct machine. Additionally, the option to print
AVL tree.
5. Option to remove data by specifying the key from any machine. The output must show the
complete path taken by the request to arrive at the correct machine and corresponding value that is
removed from the AVL tree. The updated AVL tree must be printed.
6. Option to print the routing table of any machine.
7. Option to print the AVL tree maintain on any machine along with the location of files (and line
numbers) on which the corresponding values are stored.
8. Option to add new machines on the fly without disrupting the functionality of Ring DHT.
9. Option to remove any machine on the fly without disrupting the functionality of Ring DHT.

# Execution
Run `main.cpp` to start
