#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <optional>

namespace graph
{
	typedef unsigned char	BYTE;
	typedef unsigned int	UINT;

	struct Edge
	{
		std::pair<UINT, UINT> vertexes;
		int weight;
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
		int**				matrix_;	// Матрица смежности
		UINT				size_;		// Размер матрицы смежности
		std::vector<UINT>	lengths_;	// Вспомогательный вектор
	public:
		Graph();
		Graph(int** graph, UINT size);
		~Graph();

		UINT GetSize() const;
		int** GetMatrix() const;
		std::vector<UINT> GetLength() const;

		void SetEdge(UINT a, UINT b, int weight, bool bind = false);

		std::vector<Edge> matrixToEdges();

		bool checkPower();

		// Функция чтения матрицы из файла
		void ReadFromFile(std::string file_path) noexcept;
		void ReadFromTxtFile(std::string file_path) noexcept;
		
		// Фукнция поиска в глубину
		void PassDFS(UINT begin_node, std::vector<UINT>& vec, bool begin = true) noexcept;

		std::vector<Edge> PassKruskal() noexcept;
		std::vector<Edge> PassPrima() noexcept;

		std::vector<UINT> PassDijkstra(UINT vertex, bool to_null = true, std::vector<UINT> check_vertexes = {}) noexcept;

		std::vector<std::optional<int>> PassBelmanFord(UINT begin);

		std::vector<UINT> PassEuler(UINT begin)
	};

	bool checkBind(Graph& check_graph, UINT a, UINT b);
}

