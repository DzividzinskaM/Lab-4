#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int to_integer(char ch) {
	int temporary;
	temporary = (int)ch;
	int pwr;
	pwr = 256;
	if (temporary < 0) {
		temporary += pwr;
	}
	return temporary;
}


void archive(char output[], char input[]) {
	ofstream test_file;
	ifstream final_file;
	final_file.open(input, ios::binary);
	test_file.open(output, ios::binary);
	map<string, int> dct;
	dct = { {"", 0} };
	char ch;
	string str, bin;
	int lth, count;
	lth = 0; count = 0;
	test_file << input;
	cout << endl;
	while (final_file.get(ch)) {
		str += ch;
		if (!dct[sub]) {
			dct[sub] = dct.size() - 1;
			string sum = to_bin(to_integer(ch), 8);
			sub.pop_back();
			bin += to_bin((dct[sub]), lth) + sum;
			while (bin.size() > 8)
				test_file << (char)to_ten(cut_byte(&bin));
			sub.clear();
			new_count(&count, &lth);
		}
	}
	if (str != "")
		bin += to_bin(dct[sub], lth);
	while (bin.size() > 8)
		test_file << (char)to_ten(cut_byte(&bin));
	/*int sz = bin.size();
	test_file << (char)to_ten(bin) << sz;
	final_file.close();
	test_file.close();
	remove(input);*/
}


