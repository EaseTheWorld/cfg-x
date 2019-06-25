#ifndef _CFG_H_
#define _CFG_H_

#include <string>
#include <netinet/in.h>

#include "overloaded_macro.h"

// this class will parse space-separated key-value format cfg file
// X([keyword, ]fieldname1, type1, defaultvalue1 [, fieldname2, type2, defaultvalue2])
// if keyword is omit, fieldname1 will be used for keyword
// you can use any type as long as it is used with >> operator
// defaultvalue can be any type because it will parsed with stringstream anyway
class cfg
{
#define ITEMS(X) \
	X(i10, int, 10) \
	X(s10, std::string, "Default") \
	X(i20, i21, int, 21) \
	X(i30, int, 30,   i31, int, 31) \
	X(i40, i41, int, 41,   i42, int, 42) \
	X(i50, struct sockaddr_in, "10.20.30.40 50")

	public:
		cfg();
		~cfg();
		bool loadFile(const char* filename);
		void dump();

// generic repeat macro can support more arguments but is it necessary?
#define DECL_X3(n1,t1,v1) t1 n1;
#define DECL_X4(k1, n1,t1,v1) DECL_X3(n1,t1,v1)
#define DECL_X6(n1,t1,v1, n2,t2,v2) DECL_X3(n1,t1,v1) DECL_X3(n2,t2,v2)
#define DECL_X7(k1, n1,t1,v1, n2,t2,v2) DECL_X3(n1,t1,v1) DECL_X3(n2,t2,v2)
#define DECL_X(...) OVERLOADED_MACRO(DECL_X, __VA_ARGS__)
	ITEMS(DECL_X)
#undef DECL_X3
#undef DECL_X4
#undef DECL_X6
#undef DECL_X7
#undef DECL_X

};

#endif
