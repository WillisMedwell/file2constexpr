#ifndef OUTPUT_H
#define OUTPUT_H

#include <array>
#include <string>

constexpr std::array<bool, 3> BOOL = {
	1,
	0,
	1,
	0,
	1,
	0,
	1,
	0,
	1,
	1,
	0,
	1,
	0,
	1,
	0,
	1,
	0,
	1,
	0,
	1,
	0,
	1,
	0
};
constexpr std::array<float, 4> FLOATS = {
	1.23,
	4.56,
	7.89,
	0.234
};
constexpr std::array<int, 4> INTS = {
	123,
	456,
	789,
	0
};
const std::array<std::string, 6> STRINGS = {
	"jack",
	"jill",
	"joe",
	"jane",
	"john",
	"jim"
};

#endif
