#ifndef _CFG_H_
#define _CFG_H_

#include <string>
#include <netinet/in.h>

class cfg
{
#define ITEMS(X) \
	X(int, i1, 10) \
	X(std::string, s2, "Default") \
	X(struct sockaddr_in, a3, "10.20.30.40", 5000) \
	X(int, i4, 40)

	public:
		cfg();
		~cfg();
		bool loadFile(const char* filename);

#define DECL_X(type, name, ...) type name;
	ITEMS(DECL_X)
#undef DECL_X
};

#endif
