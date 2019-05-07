
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class megazip
{
public:
	void pack(string name, ofstream &outfile);
	void unpack(ifstream &outfile, string name);
};


void megazip::pack(string name, ofstream &outfile)
{
	outfile << "[" << name << "]<";
	ifstream infile;
	infile.open(name.c_str(), ios::binary);

	char sym;
	int num = 1;
	while (!infile.eof())
	{
		infile.get(sym);
		if (sym != infile.peek())
		{
			outfile << num << sym;
			num = 0;
		}
		num++;

	}
	outfile << ">";
	infile.close();
}

void megazip::unpack(ifstream &outfile, string name)
{
	ofstream infile;
	outfile.open(name.c_str(), ios::binary);
	if (outfile.is_open())
	{
		while (!outfile.eof())
		{
			char sym;
			outfile.get(sym);
			if (sym == '[')
			{
				infile.close();
				string line;
				getline(outfile, line, ']');
				cout << line << endl;
				infile.open(line.c_str(), ios::binary);
				cout << "Getting out file" << line << "... Done" << endl;
			}
			if (sym == '<')
			{
				outfile.get(sym);
				while (sym != '>')
				{
					/*string number;
					if (!isalpha(sym) and ! sym!='>')
					{
						number = sym;
					}
					while (isalpha(sym))
					{
						number = number + sym;
					}
					int num = atoi(number.c_str());*/
					int num = sym - '0';
					outfile.get(sym);
					if (infile.is_open())
					{
						for (int i = 0; i < num; i++)
						{
							infile << sym;
						}
					}
					outfile.get(sym);
				}

			}
		}
	}
}
