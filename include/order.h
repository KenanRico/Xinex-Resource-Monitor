#ifndef ORDER_H
#define ORDER_H

#include <string>

namespace Input{
namespace Order{


enum Order{
	ASCEND = 0,
	DESCEND = 1
};
constexpr unsigned int num_orders = 7;
const std::string table[num_orders] = {"asc", "dsc"};
unsigned int ParseOrder(int, char**);

}
}

#endif
