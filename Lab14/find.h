#pragma once
#include <iostream>
#include <vector>

namespace find
{
	unsigned long long HashFunc(std::string word);

	std::vector<int> FindRK(std::string text, std::string word);
}