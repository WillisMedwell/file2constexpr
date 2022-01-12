#ifndef OUTPUT_H
#define OUTPUT_H

#include <array>
#include <string>

constexpr std::array<bool, 3> BOOL = {
	101010101,
	10101010,
	101010
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
const std::array<std::string, 2> MAXRESDEFAULT = {
	"���� JFIF      �� � 	",
	"	!"$"$�� � " ��             	�� _ 	 "2BRbr��!#3���1ACQSTaqs����������c���D����$4���Et�5d�%���U���� "
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
