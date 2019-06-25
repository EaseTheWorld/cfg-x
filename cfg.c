#include "cfg.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <arpa/inet.h>

#define MAP3(F, a, b, c) F(a) F(b) F(c)

static std::istream& operator >> (std::istream& is, struct sockaddr_in& saddr) {
	std::string ip;
	int port = ntohs(saddr.sin_port); // if not given, use default
	is>>ip>>port;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr(ip.c_str());
	saddr.sin_port = htons(port);
}

static std::ostream& operator << (std::ostream& os, const struct sockaddr_in& saddr) {
	os<<"ip "<<inet_ntoa(saddr.sin_addr)<<" port "<<ntohs(saddr.sin_port);
}

cfg::cfg() {
#define INIT_X3(n1,t1,v1) {std::stringstream ss; ss<<v1; ss>>n1;}
#define INIT_X4(k1, n1,t1,v1) INIT_X3(n1,t1,v1)
#define INIT_X6(n1,t1,v1, n2,t2,v2) INIT_X3(n1,t1,v1) INIT_X3(n2,t2,v2)
#define INIT_X7(k1, n1,t1,v1, n2,t2,v2) INIT_X3(n1,t1,v1) INIT_X3(n2,t2,v2)
#define INIT_X(...) OVERLOADED_MACRO(INIT_X, __VA_ARGS__)
	ITEMS(INIT_X)
}

cfg::~cfg() {}

bool cfg::loadFile(const char* filename) {
	std::string line;
	std::string key;
	std::ifstream is(filename);
	while(std::getline(is, line)) {
		if (line.empty() || line[0] == '#')
			continue;
		// C++11 doesn't have string trim T.T
		std::stringstream ss(line);
		ss>>key;
#define SET_X4(k1, n1,t1,v1) \
		if (!key.compare(#k1)) { \
			ss>>n1; \
			continue; \
		}
#define SET_X3(n1,t1,v1) SET_X4(n1, n1,t1,v1)
#define SET_X7(k1, n1,t1,v1, n2,t2,v2) \
		if (!key.compare(#k1)) { \
			ss>>n1>>n2; \
			continue; \
		}
#define SET_X6(n1,t1,v1, n2,t2,v2) SET_X7(n1, n1,t1,v1, n2,t2,v2)
#define SET_X(...) OVERLOADED_MACRO(SET_X, __VA_ARGS__)
		ITEMS(SET_X)
	}
	is.close();
	return true;
}

void cfg::dump() {
#define DUMP_X3(n1,t1,v1) std::cout<<#n1<<"="<<n1<<std::endl;
#define DUMP_X4(k1, n1,t1,v1) DUMP_X3(n1,t1,v1)
#define DUMP_X6(n1,t1,v1, n2,t2,v2) DUMP_X3(n1,t1,v1) DUMP_X3(n2,t2,v2)
#define DUMP_X7(k1, n1,t1,v1, n2,t2,v2) DUMP_X3(n1,t1,v1) DUMP_X3(n2,t2,v2)
#define DUMP_X(...) OVERLOADED_MACRO(DUMP_X, __VA_ARGS__)
	ITEMS(DUMP_X)
}
