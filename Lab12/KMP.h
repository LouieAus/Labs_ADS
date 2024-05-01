#pragma once
#include <iostream>
#include <vector>

namespace louie
{
	typedef unsigned int UINT;

	class KMP
	{
	private:
		// Префикс-функция
		UINT PrefixFunc(std::string str) const noexcept;

		// Функция, возвращающая количество совпадений первых символов строк
		UINT FindMatch(std::string str_a, std::string str_b) const noexcept;
	public:
		// Функция поиска по образцу
		std::vector<UINT> Find(std::string text, std::string sample, bool print = false) const noexcept;
	};
}