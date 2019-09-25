#ifndef ATTRIBS_H
#define ATTRIBS_H

#include <string>

namespace Input{
namespace Attribs{


enum Attrib {
	MEMORY = 0,
	CPU = 1,
	FILES = 2,
	PORTS = 3,
	TIME = 4
};

constexpr unsigned int num_attribs = 5;

const std::string table[num_attribs] = {"m", "c", "f", "p", "t"};

uint8_t ParseAttribs(int, char**, std::array<bool, num_attribs>*);


}
}

#endif
