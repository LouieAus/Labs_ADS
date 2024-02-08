#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>

namespace graph
{
	typedef unsigned char	BYTE;
	typedef unsigned int	UINT;

	// Функция конвертации 4 байтов в unsigned int
	UINT getFromBytes(char* bytes) noexcept;

	// Функция печати матрицы
	template<typename T>
	void printMatrix(T** matrix, UINT size_) noexcept;

	void writeToFile(std::string file_path, std::string& data);
	void writeToFile(std::string file_path, std::vector<std::vector<UINT>>& data);

	class Graph
	{
	private:
		bool**				matrix_;	// Матрица смежности
		UINT				size_;		// Размер матрицы смежности
		std::vector<UINT>	lengths_;	// Длина до вершин графа
	public:
		Graph();
		~Graph();

		// Функция чтения матрицы из файла
		void ReadFromFile(std::string file_path) noexcept;

		// Фукнция поиска в ширину
		std::optional<std::vector<UINT>> PassBFS(UINT begin_node, bool null_length = true, std::string path = "") noexcept;
		// Функция нахождения состава компомнент связности
		std::vector< std::vector<UINT>> FindConnectBFS() noexcept;

		// Фукнция поиска в глубину
		void PassDFS(UINT begin_node) noexcept;
	};
}

