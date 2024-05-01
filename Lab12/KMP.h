#pragma once
#include <iostream>
#include <vector>

namespace louie
{
	typedef unsigned int UINT;

	class KMP
	{
	private:
		// �������-�������
		UINT PrefixFunc(std::string str) const noexcept;

		// �������, ������������ ���������� ���������� ������ �������� �����
		UINT FindMatch(std::string str_a, std::string str_b) const noexcept;
	public:
		// ������� ������ �� �������
		std::vector<UINT> Find(std::string text, std::string sample, bool print = false) const noexcept;
	};
}