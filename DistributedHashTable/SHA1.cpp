#include "SHA1.h"

char toHex(string key) {

	if (key == "0000" || key == "00")
		return '0';
	else if (key == "0001" || key == "01")
		return '1';
	else if (key == "0010" || key == "10")
		return '2';
	else if (key == "0011" || key == "11")
		return '3';
	else if (key == "0100")
		return '4';
	else if (key == "0101")
		return '5';
	else if (key == "0110")
		return '6';
	else if (key == "0111")
		return '7';
	else if (key == "1000")
		return '8';
	else if (key == "1001")
		return '9';
	else if (key == "1010")
		return 'a';
	else if (key == "1011")
		return 'b';
	else if (key == "1100")
		return 'c';
	else if (key == "1101")
		return 'd';
	else if (key == "1110")
		return 'e';
	else if (key == "1111")
		return 'f';
	return '\0';
}

string toBin(int n) {

	string data = "";
	int Bin[8] = { -1 }, i = 7;
	while (n > 0) {
		Bin[i] = n % 2;
		n = n / 2;
		i--;
	}
	for (int j = 0; j < 8; j++) {
		if (Bin[j] == -1) {
			data += "0";
		}
		else {

			data += to_string(Bin[j]);
		}
	}
	//cout << data << endl;
	return data;

}
string LengthtoBin(int n) {

	string data = "";
	int Bin[64] = { -1 }, i = 63;
	while (n > 0) {
		Bin[i] = n % 2;
		n = n / 2;
		i--;
	}
	for (int j = 0; j < 64; j++) {
		if (Bin[j] == -1) {
			data += "0";
		}
		else {

			data += to_string(Bin[j]);
		}
	}
	//cout << data << endl;
	return data;

}

string ADD(string m, string n) {
	string a = string(m.rbegin(), m.rend());
	string b = string(n.rbegin(), n.rend());
	int len;
	bool flag = false;
	if (a.size() < b.size()) {
		len = a.size();
		flag = true;
	}
	else {
		len = b.size();
		flag = false;
	}
	string data = "";
	char c = '0';
	for (int i = 0; i < len; i++) {
		if (c == '0') {
			if (a[i] == '1' && b[i] == '1') {
				data += '0';
				c = '1';
			}
			else if (a[i] == '0' && b[i] == '0') {
				data += '0';
				c = '0';
			}
			else {
				data += '1';
				c = '0';
			}
		}
		else {
			if (a[i] == '1' && b[i] == '1') {
				data += '1';
				c = '1';
			}
			else if (a[i] == '0' && b[i] == '0') {
				data += '1';
				c = '0';
			}
			else {
				data += '0';
				c = '1';
			}
		}
	}
	int newLen;
	if (flag) {
		newLen = b.size();
		for (int i = len; i < newLen; i++) {
			if (c == '0') {
				data += b[i];
			}
			else {
				if (b[i] == '1') {
					data += '0';
					c = '1';
				}
				else {
					data += '1';
					c = 0;
				}
			}
		}
		if (c == '1') {
			data += '1';
		}
	}
	else {
		newLen = a.size();
		for (int i = len; i < newLen; i++) {
			if (c == '0') {
				data += b[i];
			}
			else {
				if (b[i] == '1') {
					data += '0';
					c = '1';
				}
				else {
					data += '1';
					c = 0;
				}
			}
		}
		if (c == '1') {
			data += '1';
		}
	}
	string newData = string(data.rbegin(), data.rend());
	return newData;

}

string XOR(string a, string b) {
	string data = "";

	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) {
			data += "0";
		}
		else {
			data += "1";
		}
	}

	return data;
}

string OR(string a, string b) {
	string data = "";

	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] == '1' || b[i] == '1') {
			data += "1";
		}
		else {
			data += "0";
		}
	}

	return data;
}
string AND(string a, string b) {
	string data = "";

	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] == '0' || b[i] == '0') {
			data += "0";
		}
		else {
			data += "1";
		}
	}

	return data;
}

string NOT(string a) {
	string data = "";

	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] == '0') {
			data += "1";
		}
		else {
			data += "0";
		}
	}

	return data;
}

string LeftRotate(string a, int s) {
	string data = "", temp = "";

	for (int i = 0; i < s; i++) {
		temp += a[i];
	}
	for (size_t i = s; i < a.size(); i++)
		data += a[i];
	for (int i = 0; i < s; i++) {
		data += temp[i];
	}
	return data;
}

string Make32Bit(string a) {
	string data = "";
	int j = a.size() % 32;
	for (size_t i = j; i < a.size(); i++) {
		data += a[i];
	}
	return data;
}

string SHA1(string myStr) {
	string digest[5];
	digest[0] = "01100111010001010010001100000001";
	digest[1] = "11101111110011011010101110001001";
	digest[2] = "10011000101110101101110011111110";
	digest[3] = "00010000001100100101010001110110";
	digest[4] = "11000011110100101110000111110000";
	// String to store all computations
	string temp = "";
	// Converting the string to Binary
	for (size_t i = 0; i < myStr.size(); i++) {
		temp += toBin((int)myStr[i]);

	}
	// Need this to append at the end
	string OriginalLength = LengthtoBin(temp.size());
	// Appending 1
	temp += "1";
	// Adding rest of the 0's
	int mod = temp.size() % 512;

	for (int i = temp.size(); mod != 448; i++) {
		temp += "0";
		mod = temp.size() % 512;
	}
	//  Adding the Original Length at the end
	temp += OriginalLength;
	int h = 0;
	string OriginalBits = temp;
	int start = 0, end = 512;
	int chunks = 0;
	int sizeTemp = temp.size();
	while (sizeTemp != 0) {
		chunks++;
		sizeTemp -= 512;
	}
	int x = 0;
	for (int p = 0; p < chunks; p++) {
		string Block[80];
		// For 0 to 16
		for (int i = 0; i < 16; i++) {
			Block[i] = "";
			for (int j = 0; j < 32; j++) {
				Block[i] += temp[x];
				x++;
			}
			//cout << i << " " <<Block[i] << endl;
		}
		string a, b, c, d, e;

		for (int i = 16; i < 80; i++) {
			a = Block[i - 3];
			b = Block[i - 8];
			c = Block[i - 14];
			d = Block[i - 16];
			Block[i] = LeftRotate(XOR(XOR(XOR(a, b), c), d), 1);
			//cout << i << " " << Block[i] << endl;
		}
		a = digest[0];
		b = digest[1];
		c = digest[2];
		d = digest[3];
		e = digest[4];
		string f = "", k, temp2;

		//// Main Loop
		for (int i = 0; i < 80; i++) {
			if (i < 20) {
				// Step 1  (B AND C) OR (!B AND D)
				f = OR(AND(b, c), AND(NOT(b), d));
				k = "01011010100000100111100110011001";

			}
			else if (i < 40) {
				f = XOR(XOR(b, c), d);
				k = "01101110110110011110101110100001";
			}
			else if (i < 60) {
				//  (B AND C) OR (B AND D) OR (C AND D)
				f = OR(OR(AND(b, c), AND(b, d)), AND(c, d));
				k = "10001111000110111011110011011100";
			}
			else {
				f = XOR(XOR(b, c), d);
				k = "11001010011000101100000111010110";
			}

			temp2 = ADD(ADD(ADD(ADD(LeftRotate(a, 5), f), e), k), Block[i]);
			string newtemp = Make32Bit(temp2);

			e = d;
			d = c;
			c = LeftRotate(b, 30);
			b = a;
			a = newtemp;
		}
		digest[0] = Make32Bit(ADD(digest[0], a));
		digest[1] = Make32Bit(ADD(digest[1], b));
		digest[2] = Make32Bit(ADD(digest[2], c));
		digest[3] = Make32Bit(ADD(digest[3], d));
		digest[4] = Make32Bit(ADD(digest[4], e));
	}

	string SHA1 = "", temp3 = "";
	int n = 0;
	for (int i = 0; i < 5; i++) {
		//cout << digest[i] << endl;
		n = 0;
		for (int j = 0; j < 8; j++) {
			temp3 = "";
			for (int m = 0; m < 4; m++) {
				temp3 += digest[i][n];
				n++;
			}
			SHA1 += toHex(temp3);
		}
	}
	return SHA1;

}