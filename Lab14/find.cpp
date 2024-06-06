#include "find.h"

namespace find
{
	unsigned long long HashFunc(std::string word)
	{
		unsigned long long result = 0;
		for (auto j = 0; j != word.length(); j++)
		{
			result += (int)word[j] * pow(2, j);
		}
		return result;
	}

	std::vector<int> FindRK(std::string text, std::string word)
	{
		std::vector<int> result;

		unsigned long long word_hash = HashFunc(word);

		for (auto i = 0; i != text.size() - word.size() + 1; i++)
		{
			std::string substr = text.substr(i, word.size());
			if (HashFunc(substr) == word_hash)
			{
				bool equal = true;
				for (auto j = 0; j != word.size(); j++)
				{
					if (word[j] != substr[j])
					{
						equal = false;
						break;
					}
				}

				if (equal)
					result.push_back(i);
			}
		}

		return result;
	}
}