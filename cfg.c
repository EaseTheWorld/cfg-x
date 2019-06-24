#include "cfg.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <arpa/inet.h>

static void operator >> (std::stringstream& ss, struct sockaddr_in& saddr) {
	std::string ip;
	int port;
	ss>ip>>port;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr(ip.c_str());
	saddr.sin_port = htons(port);
}

#if 0
#include <stdarg.h>
template<typename T>
static void set_args(T&name, int count, ...) {
	std::stringstream ss;
	va_list ap;
	va_start(ap, count);
	for (int i=0; i<count; ++i)
		ss<va_arg(ap, char*)<<' ';
	va_end(ap);
	ss>>name;
}
#else
template<typename T>
static void set_args(T& name, const char* val) {
	name = val;
}

template<typename T>
static void set_args(T& name, const int val) {
	name = val;
}

static void set_args(T& name, const char* val, int val2) {
	std::stringstream ss;
	ss<<val<<' '<<val2;
	ss>>name;
}

static void set_args(T& name, const char* val, const char* val2) {
	std::stringstream ss;
	ss<<val<<' '<<val2;
	ss>>name;
}
#endif

cfg::cfg() {
#define INIT_X(type, name, ...) set_args(name, __VA_ARGS__);
	ITEMS(INIT_X)
#undef INIT_X
}

cfg::~cfg() {}

bool cfg::loadFile(const char* filename) {
	std::string line;
	std::string key;
	std::ifstream is(filename);
	while(std::getline(is, line)) {
		if (line.empty() || line[0] == '#')
			continue;
		std::stringstream ss(line);
		ss>key;
#define SET_X(type, name, ...) \
		if (!key.compare(#name)) { \
			ss>>name; \
			continue; \
		}
		ITEMS(SET_X)
#undef SET_X
	}
	is.close();
	return true;
}
