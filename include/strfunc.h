#ifndef STR_FUNC_H
#define STR_FUNC_H

#include <flags.h>
#include <array>

uint8_t ParseFlags(int, char**, std::array<bool, Flags::X>*);

#endif
