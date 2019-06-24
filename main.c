#include <iostream>

int main(int argc, char* argv[])
{
	cfg c1;
	c1.loadFile(argv[1]);
	std::cout<<"cfg i1="<<c1.i1<<" s2="<<c1.s2<<std::endl;
	return 0;
}
