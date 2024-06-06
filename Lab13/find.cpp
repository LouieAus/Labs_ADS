#include "find.h"

namespace find
{
	int GetValue(char symbol, std::vector<Symbol>& symbols, int offset)
	{
		for (auto j = 0; j != symbols.size(); j++)
		{
			if (symbol == symbols[j].symbol)
			{
				return symbols[j].value;
			}
		}

		return offset;
	}

	std::vector<Symbol> find::PrepareWord(std::string word)
	{
		std::vector<Symbol> result;

		int offset = 1;
		for (auto i = word.length() - 2; i != -1; i--)
		{
			Symbol new_symbol;
			new_symbol.symbol = word[i];

			new_symbol.value = GetValue(word[i], result, offset);

			result.push_back(new_symbol);
			offset++;
		}

		result.push_back(Symbol{ word[word.length() - 1], GetValue(word[word.length() - 1], result, offset)});

		return result;
	}

	std::vector<int> FindBM(std::string text, std::string word)
	{
		std::vector<int> result;

		// Подготавливаем таблицу символов
		std::vector<Symbol> word_values = PrepareWord(word);

		// Начинаем поиск
		int last_index = word.size() - 1;
		while (last_index < text.size())
		{
			bool found = true;
			int last_offset = word.size();

			// Сравниваем образец и подстроку текса
			for (auto i = 0; i != word.size(); i++)
			{
				int text_index = last_index - i;
				// Если нашлось несоответствие
				if (word[word.size() - 1 - i] != text[text_index])
				{
					found = false;
					bool found_symbol = false;

					// Ищем символ в таблице
					for (Symbol& symbol : word_values)
					{
						// Если символ нашелся, то сдвигаем индекс поиска на величину из таблицы
						if (symbol.symbol == text[text_index])
						{
							last_index += symbol.value;
							found_symbol = true;
							break;
						}
					}

						// Если символ не нашелся, то сдивгаем индекс поиска на последнюю найденную величину
					if (found_symbol == false)
					{
						last_index += last_offset;
					}

					break;
				}
				else
				{
					// Запоминаем последнюю найденную величину в случае соответствия
					for (Symbol& symbol : word_values)
					{
						if (symbol.symbol == text[text_index])
						{
							last_offset = symbol.value;
							break;
						}
					}
				}
			}

			// Если нашли подстроку, то добавляем индекс в результат
			if (found)
			{
				result.push_back(last_index - word.size() + 1);
				last_index++;
			}
						
		}

		return result;
	}
}