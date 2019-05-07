#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "ourlib.h"

using namespace std;

int main()
{
	int main(int argc, char *argv[])
	{
		megazip mg_zip;
		if (argc > 1)
		{
			string flag(argv[1]);
			if (flag == "--compress")
			{
				string name(argv[2]);
				ofstream outfile(name.c_str());
				for (int i = 3; i < argc; i++)
				{
					string infile = argv[i];
					mg_zip.pack(infile, outfile);
					cout << "Compressing file " << argv[i] << " ...Done" << endl;
				}
			}
			else if (flag == "--decompress")
			{
				string name(argv[2]);
				ifstream myfile;
				mg_zip.unpack(myfile, name);
			}
		}

	}
}
