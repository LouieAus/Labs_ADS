#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

namespace graph
{
	typedef unsigned int UINT;

	class Graph
	{
	private:
		std::vector<std::vector<bool>> graph_;	// матрица графа
		UINT size_;								// размер графа
		UINT chromatic_;						// хроматическое число графа

		// Функция проверки вектора цветов, озвращает хроматическое число
		UINT GetChromatic(std::vector<int> c_vertexes);
		// Функция проверки хроматического числа max_k проходом по графу
		void Chromatic(UINT vertex, std::vector<int> c_vertexes, int max_k);
	public:
		Graph();
		~Graph();

		// Функция чтения графа из файла
		void ReadGraph(std::string file_name);
		// Функция вывода графа в консоль
		void PrintGraph();

		// Функция вычисления хроматического числа
		UINT CalculateChromatic();
	};
}