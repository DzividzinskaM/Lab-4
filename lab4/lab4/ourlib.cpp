#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

void new_count(int* counter, int* lth)
{
	if (*counter == (int)pow(2, *lth - 1))
	{
		(*lth)++;
		*counter = 0;
	}
	(*counter)++;
}

string cut_byte(string *str)
{
	string tmp = (*str).substr(0, 8);
	(*str).erase(0, 8);
	return tmp;
}
string to_bin(int val, int lth)
{
	if (lth == 0) return "";
	string tmp = "00000000";
	while (tmp.size() < lth) tmp += tmp;
	int i = lth - 1;
	while (val > 0)
	{
		if (val % 2) tmp[i] = '1';
		else tmp[i] = '0';
		val /= 2;
		i--;
	}
	return tmp.substr(0, lth);
}
int to_ten(string bin)
{
	string tmp;
	int val = 0;
	for (int i = 0; i <= bin.size(); i++)
	{
		if (bin[i] != '0')
			val += (int)pow(2, (int)bin.size() - i - 1);
	}
	return val;
}


void archive(char output[], char input[]) {
	ofstream final_file;
	ifstream test_file;
	test_file.open(input, ios::binary);
	final_file.open(output, ios::binary);
	map<string, int> dct = { {"", 0} };
	char ch;
	string str, bin;
	int lth, count;
	lth = 0; count = 0;
	final_file << input << "\r\n";
	while (test_file.get(ch)) {
		str += ch;
		if (!dct[str]) {
			dct[str] = dct.size() - 1;
			string sum = to_bin(to_integer(ch), 8);
			str.pop_back();
			bin += to_bin((dct[str]), lth) + sum;
			while (bin.size() > 8)
				final_file << (char)to_ten(cut_byte(&bin));
			str.clear();
			new_count(&count, &lth);
		}
	}
	if (str != "")
		bin += to_bin(dct[str], lth);
	while (bin.size() > 8)
		final_file << (char)to_ten(cut_byte(&bin));
	int sz = bin.size();
	final_file << (char)to_ten(bin) << sz;
	final_file.close();
	test_file.close();
	remove(input);
}


void decompress(char out[])
{
	ofstream new_file;
	ifstream out_file;
	out_file.open(out, ios::binary);
	string name;
	int pos = 0;
	char ch;
	while (out_file.get(ch))
	{
		if (out_file.peek() == '\n')
		{
			pos = (int)out_file.tellg() + 1;
			break;
		}
		name += ch;
	}
	new_file.open(name, ios::binary);
	vector<string> dct = { "" };
	int counter = 0;
	int lth = 0;
	string bin;
	out_file.seekg(0);
	out_file.seekg(-1, out_file.end);
	out_file.get(ch);
	int val = ch - '0';
	int last = (int)(out_file.tellg()) - 1;
	out_file.seekg(pos);
	while (out_file.get(ch))
	{
		if ((int)out_file.tellg() != last)
		{
			bin += to_bin(to_integer(ch), 8);
		}
		else
		{
			bin += to_bin(to_integer(ch), 8).erase(0, 8 - val);
			break;
		}
		if (bin.size() >= 8 + lth)
		{
			string num = bin.substr(0, lth);
			bin.erase(0, lth);
			string sym = cut_byte(&bin);
			string res = dct[to_ten(num)] + (char)to_ten(sym);
			dct.push_back(res);
			new_file << res;
			new_count(&counter, &lth);
		}
	}
	if (bin.size() >= 8 + lth)
	{
		string num = bin.substr(0, lth);
		bin.erase(0, lth);
		string sym = cut_byte(&bin);
		string res = dct[to_ten(num)] + (char)to_ten(sym);
		dct.push_back(res);
		new_file << res;
	}
	if (bin != "")
		new_file << dct[to_ten(bin)];
	out_file.close();
	new_file.close();
	remove(out);
}