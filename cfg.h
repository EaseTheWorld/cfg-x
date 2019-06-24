#ifndef _CFG_H_
#define _CFG_H_

#include <string>
#include <netinet/in.h>

class cfg
{
// X2's 2nd argument is optional
#define ITEMS(X, X2) \
	X(int, i1, 10) \
	X(std::string, s2, "Default") \
	X(struct sockaddr_in, a3, "10.20.30.40", 5000) \
	X2(int, i4, 40, int, i41, 41)

	public:
		cfg();
		~cfg();
		bool loadFile(const char* filename);

#define DECL_X(type, name, ...) type name;
#define DECL_X2(type1, name1, defVal1, type2, name2, defVal2) DECL_X(type1, name1, defVal1) DECL_X(type2, name2, defVal2)
	ITEMS(DECL_X, DECL_X2)
#undef DECL_X
#undef DECL_X2
};

#endif
