
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void archive(char output[], char input[]);
void new_count(int* counter, int* lth);
string cut_byte(string *str);
string to_bin(int val, int lth);
int to_integer(char ch);
int to_ten(string bin);
void decompress(char out[]);
