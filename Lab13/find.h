#pragma once
#include <iostream>
#include <vector>

namespace find
{
	struct Symbol
	{
		char symbol;
		int value;
	};

	std::vector<Symbol> PrepareWord(std::string word);

	std::vector<int> FindBM(std::string text, std::string word);
}