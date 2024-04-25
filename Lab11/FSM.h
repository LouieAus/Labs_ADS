#pragma once
#include <vector>
#include <iostream>


namespace louie
{
	typedef unsigned int UINT;

	class FSM
	{
	private:
		// Вектор, состоящий из строк:
		//			строка	  префикс	   индексы переходов для алфавита	
		std::vector<std::pair<std::string, std::vector<int>>> transitions_;
		
		// Состояния автомата, при которых обозначается найденный образец
		std::vector<int> sample_states_;

		// Текущее состояние автомата
		UINT state_;
	
		// Функция готовит конечный автомат, т.е. таблицу переходов
		void PrepareTabel(std::vector<std::string> samples, std::vector<char> alphabet);

		// Функция меняет состояние автомата
		void ChangeState(char symbol, std::vector<char>& alphabet);
	public:
		// Функция FindOneSample возвращает сдвиги, которые указывают на положение
		// найденных слов в тексте (образец один)
		std::vector<int> FindOneSample(std::string sample, std::string file_path, bool print = false);

		// Функция FindSamples возвращает пары: образец и свдиги, которые указывают на положение
		// найденных слов в тексте (образцов больше одного)
		std::vector<std::pair<std::string, std::vector<int>>>
			FindSamples(std::vector<std::string> samples, std::string file_path, bool print = false);
	};
}