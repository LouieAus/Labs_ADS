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

	// ������� ����������� 4 ������ � unsigned int
	UINT getFromBytes(char* bytes) noexcept;

	// ������� ������ �������
	template<typename T>
	void printMatrix(T** matrix, UINT size_) noexcept;

	void printUintVector(std::vector<UINT>& vec, std::string vec_name = "") noexcept;

	void writeToFile(std::string file_path, std::string& data);
	void writeToFile(std::string file_path, std::vector<std::vector<UINT>>& data);

	class Graph
	{
	private:
		bool**				matrix_;	// ������� ���������
		UINT				size_;		// ������ ������� ���������
		std::vector<UINT>	lengths_;	// ����� �� ������ �����
	public:
		Graph();
		Graph(bool** graph, UINT size);
		~Graph();

		UINT GetSize() const;
		bool** GetMatrix() const;

		// ������� ������ ������� �� �����
		void ReadFromFile(std::string file_path) noexcept;
		void ReadFromTxtFile(std::string file_path) noexcept;

		// ������ ��������� ���������������� �����
		bool** GetReversedGraph();

		// ������� ������ � ������
		std::optional<std::vector<UINT>> PassBFS(UINT begin_node, bool null_length = true, std::string path = "") noexcept;
		// ������� ���������� ������� ���������� ���������
		std::vector< std::vector<UINT>> FindConnectBFS() noexcept;

		// ������� ������ � �������
		void PassDFS(UINT begin_node, std::vector<UINT>& vec) noexcept;
		// ������� ���������� ������� ���������� ���������
		std::vector<std::vector<UINT>> FindConnectDFS() noexcept;
		// ������� ���������� ������� ���������� ������� ���������
		std::vector<std::vector<UINT>> FindStrongConnectDFS() noexcept;
	};
}

