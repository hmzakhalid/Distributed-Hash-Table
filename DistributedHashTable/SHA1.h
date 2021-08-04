#ifndef SHA_1
#define SHA_1

#include <iostream>
#include <string>

using namespace std;

char toHex(string key);			//gives hexa value of the binary
string toBin(int n);			//converts integer to binary
string LengthtoBin(int n);		//converts the length to binary
string ADD(string m, string n);	//adds two binary strings
string XOR(string a, string b); //xors two binary strings
string OR(string a, string b);	//ors two binary strings
string AND(string a, string b);	//ands two binary strings
string NOT(string a);			//nots two binary strings
string LeftRotate(string a, int s);	//rotates a string to the left by s
string Make32Bit(string a);			//divides the string into a 32 bit portion
string SHA1(string myStr);			//applies sha1 hashing on string s

#endif // !SHA_1