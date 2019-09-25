#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <string>

namespace Input{
namespace Orientation{


enum Orientation{
	CPU_USAGE = 0,
	PAGE_FAULT_COUNT = 1,
	WORKING_SET = 2,
	COMMITED_MEM = 3,
	OPEN_FILE_COUNT = 4,
	PORT_CNUMBER = 5,
	UP_TIME = 6
};
constexpr unsigned int num_orientations = 7;
const std::string table[num_orientations] = {"cpu", "pfc", "ws", "cm", "opc", "pn", "ut"};
unsigned int ParseOrientation(int, char**);


}
}

#endif
