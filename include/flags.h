#ifndef FLAGS_H
#define FLAGS_H

#include <string>

namespace Flags{
	enum Flag {
		MEMORY = 0,
		CPU = 1,
		FILES = 2,
		PORTS = 3,
		HELP = 4
	};
	constexpr unsigned int X = 5;
	constexpr unsigned int num_attribs = X-1;
	const std::string table[X] = {"m", "c", "f", "p", "h"};
};

#endif
