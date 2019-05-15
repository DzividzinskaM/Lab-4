#include "pch.h"
#include "ourlib.h"

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "not enough args" << endl;
		return 0;
	}
	if (!strcmp(argv[1], "--compress")) archive(argv[2], argv[3]);
	else if (!strcmp(argv[1], "--decompress")) decompress(argv[2]);
	else cout << "unknown command" << endl;
	return 0;
}