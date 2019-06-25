#include "cfg.h"
#include <iostream>

int main(int argc, char* argv[])
{
	cfg c1;
	c1.loadFile(argv[1]);
	c1.dump();
	return 0;
}
