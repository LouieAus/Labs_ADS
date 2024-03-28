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

	struct Edge
	{
		std::pair<UINT, UINT> vertexes;
		UINT weight;
	};

	// Функция печати матрицы
	template<typename T>
	void printMatrix(T** matrix, UINT size_) noexcept;

	void printUintVector(std::vector<UINT>& vec, std::string vec_name = "") noexcept;

	void writeToFile(std::string file_path, std::string& data);
	void writeToFile(std::string file_path, std::vector<std::vector<UINT>>& data);

	

	class Graph
	{
	private:
		UINT**				matrix_;	// Матрица смежности
		UINT				size_;		// Размер матрицы смежности
		std::vector<UINT>	lengths_;	// Длина до вершин графа
	public:
		Graph();
		Graph(UINT** graph, UINT size);
		~Graph();

		UINT GetSize() const;
		UINT** GetMatrix() const;
		std::vector<UINT> GetLength() const;

		void SetEdge(UINT a, UINT b, UINT weight, bool bind = false);

		// Функция чтения матрицы из файла
		void ReadFromFile(std::string file_path) noexcept;
		void ReadFromTxtFile(std::string file_path) noexcept;
		
		// Фукнция поиска в глубину
		void PassDFS(UINT begin_node, std::vector<UINT>& vec, bool begin = true) noexcept;

		std::vector<Edge> PassKruskal() noexcept;
		std::vector<Edge> PassPrima() noexcept;
	};

	bool checkBind(Graph& check_graph, UINT a, UINT b);
}

