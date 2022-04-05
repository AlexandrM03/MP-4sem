#include "libs.hpp"

std::string random_string(size_t length)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(97, 122);
	std::string str(length, '\0');
	for (size_t i = 0; i < length; ++i)
		str[i] = static_cast<char>(dist(mt));
	
	return str;
}