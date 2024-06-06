#include <iostream>
#include "find.h"

using namespace find;

int main()
{
	setlocale(LC_ALL, "rus");

	// Поиск слова
	std::string text = "hello hello hellhello one two three he";
	std::vector<int> res = FindBM(text, "hello");

	// Вывод результата
	std::cout << '\n' << text << '\n';
	std::string signs;
	for (int i = 0; i != text.length(); i++)
		signs.push_back(' ');
	for (int id : res)
		signs[id] = '^';
	std::cout << signs;
}