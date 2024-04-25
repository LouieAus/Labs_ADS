#include "FSM.h"
#include <algorithm>
#include <fstream>
#include <string>

namespace louie
{
	std::string getStringFromFile(std::string file_path)
	{
		std::string result = "";
		std::string line;
		std::ifstream file(file_path);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				result += line + "\n";
			}
		}
		file.close();
		return result;
	}

	std::vector<char> getAlphabet(std::string text)
	{
		std::vector<char> result;
		for (auto i = 0; i != text.length(); i++)
		{
			bool symb_in_vec = false;
			for (char s : result)
			{
				if (s == text[i])
				{
					symb_in_vec = true;
					break;
				}
			}
			if (!symb_in_vec)
				result.push_back(text[i]);
		}

		std::sort(result.begin(), result.end(), [](char a, char b) { return (int)a < (int)b; });
		return result;
	}

	bool isSubstring(std::vector<std::string> strs)
	{
		std::sort(strs.begin(), strs.end(), [](std::string a, std::string b) { return a.length() < b.length(); });
		
		for (auto i = 0; i != strs.size() - 1; i++)
		{
			for (auto j = i + 1; j != strs.size(); j++)
			{
				if (strs[j].find(strs[i]) != -1)
					return true;
			}
		}
		return false;
	}

	int suffixFunc(std::string prefix, std::string conc)
	{
		int max_length = 0;
		std::string suffix = "";
		for (auto i = conc.length() - 1; i != -1; i--)
		{
			suffix = conc[i] + suffix;
			if (suffix.length() > prefix.length())
				break;

			if (suffix == prefix.substr(0, suffix.length()))
			{
				if (suffix.length() > max_length)
					max_length = suffix.length();
			}
		}
		return max_length;
	}

	void FSM::PrepareTabel(std::vector<std::string> samples, std::vector<char> alphabet)
	{
		transitions_.clear();
		sample_states_.clear();

		// Сортировка образцов
		std::sort(samples.begin(), samples.end(), [](std::string a, std::string b) {
			int len = a.length() < b.length() ? a.length() : b.length();
			for (auto i = 0; i != len; i++)
			{
				if (a[i] != b[i])
					return (int)a[i] < (int)b[i];
			}
			});

		// Добавление префиксов образцов в таблицу
		transitions_.push_back(std::make_pair("", std::vector<int>(alphabet.size(), 0)));
		for (std::string sample : samples)
		{
			std::string prefix_base = "";
			for (auto i = 0; i != sample.length(); i++)
			{
				prefix_base = prefix_base + sample[i];
				transitions_.push_back(std::make_pair(prefix_base, std::vector<int>(alphabet.size(), 0)));
			}
		}

		// Удаление лишних префиксов
		int current_pos = 1;
		while (true)
		{
			if (current_pos == transitions_.size())
				break;

			std::string check_prefix = transitions_[current_pos].first;

			std::vector<int> delete_indexes;
			for (auto i = current_pos + 1; i != transitions_.size(); i++)
			{
				if (transitions_[i].first == check_prefix)
					delete_indexes.push_back(i);
			}
			
			for (auto i = delete_indexes.size() - 1; i != -1; i--)
			{
				transitions_.erase(transitions_.begin() + delete_indexes[i]);
			}

			current_pos++;
		}

		// Формирование значений переходов в таблице
		for (std::pair<std::string, std::vector<int>>& pair : transitions_)
		{
			for (auto s = 0; s != pair.second.size(); s++)
			{
				std::string conc = pair.first + alphabet[s];

				int max_suffix = 0;
				int state = 0;
				for (auto i = 0; i != transitions_.size(); i++)
				{
					std::string prefix = transitions_[i].first;

					int curr_suffix = suffixFunc(prefix, conc);
					if (curr_suffix > max_suffix)
					{
						max_suffix = curr_suffix;
						state = i;
					}
				}

				pair.second[s] = state;
			}
		}

		// Ищем выходные состояния автомата
		for (auto i = 0; i != transitions_.size(); i++)
		{
			std::string prefix = transitions_[i].first;
			for (std::string sample : samples)
			{
				if (prefix == sample)
				{
					sample_states_.push_back(i);
					break;
				}
			}
		}

		/*for (std::pair<std::string, std::vector<int>>& pair : transitions_)
		{
			std::cout << pair.first << ":\t";
			for (int num : pair.second)
				std::cout << num << '\t';
			std::cout << '\n';
		}

		for (int st : sample_states_)
			std::cout << st << '\t';*/
	}

	void FSM::ChangeState(char symbol, std::vector<char>& alphabet)
	{
		int alph_pos = 0;
		for (auto i = 0; i != alphabet.size(); i++)
		{
			if (alphabet[i] == symbol)
			{
				alph_pos = i;
				break;
			}
		}
		state_ = transitions_[state_].second[alph_pos];
	}

	std::vector<int> FSM::FindOneSample(std::string sample, std::string file_path, bool print)
	{
		std::vector<int> result;

		std::vector<std::string> samples = { sample };
		std::string input_text = getStringFromFile(file_path);
		std::vector<char> alphabet = getAlphabet(input_text);

		PrepareTabel(samples, alphabet);

		state_ = 0;
		for (auto i = 0; i != input_text.length(); i++)
		{
			char symbol = input_text[i];
			ChangeState(symbol, alphabet);
			
			for (int state : sample_states_)
			{
				if (state == state_)
				{
					result.push_back(i - transitions_[state].first.length() + 1);
				}
			}
		}

		if (print)
		{
			std::cout << input_text;
			for (auto i = 0; i != input_text.length(); i++)
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

	std::vector<std::pair<std::string, std::vector<int>>>
		FSM::FindSamples(std::vector<std::string> samples, std::string file_path, bool print)
	{
		std::vector<std::pair<std::string, std::vector<int>>> result;
		std::string input_text = getStringFromFile(file_path);

		if (!isSubstring(samples))
		{
			for (std::string str : samples)
				result.push_back(std::make_pair(str, std::vector<int>()));

			std::vector<char> alphabet = getAlphabet(input_text);

			PrepareTabel(samples, alphabet);

			state_ = 0;
			for (auto i = 0; i != input_text.length(); i++)
			{
				char symbol = input_text[i];
				ChangeState(symbol, alphabet);

				for (int state : sample_states_)
				{
					if (state == state_)
					{
						int offset = i - transitions_[state].first.length() + 1;
						std::string word = transitions_[state].first;
						for (std::pair<std::string, std::vector<int>>& pair : result)
						{
							if (pair.first == word)
								pair.second.push_back(offset);
						}
					}
				}
			}
		}
		else
		{
			for (std::string sample : samples)
			{
				std::vector<int> sub_result = FindOneSample(sample, file_path);
				result.push_back(std::make_pair(sample, sub_result));
			}
		}

		if (print)
		{
			for (std::pair<std::string, std::vector<int>>& pair : result)
			{
				std::cout << "Find " << pair.first << '\n';
				std::cout << input_text;
				for (auto i = 0; i != input_text.length(); i++)
				{
					std::string symb = " ";
					for (int offset : pair.second)
					{
						if (i == offset)
							symb = "^";
					}
					std::cout << symb;
				}
				std::cout << '\n';
			}
		}

		return result;
	}
}