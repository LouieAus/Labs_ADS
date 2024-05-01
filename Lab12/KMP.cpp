#include "KMP.h"

namespace louie
{
	UINT KMP::PrefixFunc(std::string str) const noexcept
	{
		UINT q = str.length();
		UINT max_length = 0;

		for (auto i = 1; i != q; i++)
		{
			std::string prefix = str.substr(0, i);
			std::string suffix = str.substr(q - i, i);
			
			if (prefix == suffix)
			{
				if (prefix.size() > max_length)
					max_length = prefix.size();
			}
		}

		return max_length;
	}

	UINT KMP::FindMatch(std::string str_a, std::string str_b) const noexcept
	{
		UINT q = str_a.length() < str_b.length() ? str_a.length() : str_b.length();
		UINT match = 0;
		
		for (int i = 0; i != q; i++)
		{
			if (str_a[i] == str_b[i])
				match++;
			else
				break;
		}

		return match;
	}

	std::vector<UINT> KMP::Find(std::string text, std::string sample, bool print) const noexcept
	{
		std::vector<UINT> result;

		UINT offset = 0;
		while (offset < text.length())
		{
			UINT q = FindMatch(text.substr(offset), sample);

			if (q != 0)
			{
				if (q == sample.size())
					result.push_back(offset);

				UINT k = PrefixFunc(sample.substr(0, q));
				offset = offset + (q - k);
			}
			else
				offset++;
		}

		if (print)
		{
			std::cout << text << '\n';
			for (auto i = 0; i != text.length(); i++)
			{
				std::string symb = " ";
				for (int offset : result)
				{
					if (i == offset)
						symb = "^";
				}
				std::cout << symb;
			}
			std::cout << '\n';
		}

		return result;
	}
}