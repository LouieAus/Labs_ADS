#include <iostream>
#include "find.h"

int main()
{
	std::string text = "Hello my name is Ilya, hello llll";
	std::vector<int> res = find::FindRK(text, "ello");

	std::cout << text << '\n';
	std::string signs;
	for (int i = 0; i != text.length(); i++)
		signs.push_back(' ');
	for (int id : res)
		signs[id] = '^';
	std::cout << signs;
}