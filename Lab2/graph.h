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
		~Graph();

		// ������� ������ ������� �� �����
		void ReadFromFile(std::string file_path) noexcept;

		// ������� ������ � ������
		std::optional<std::vector<UINT>> PassBFS(UINT begin_node, bool null_length = true, std::string path = "") noexcept;
		// ������� ���������� ������� ���������� ���������
		std::vector< std::vector<UINT>> FindConnectBFS() noexcept;

		// ������� ������ � �������
		void PassDFS(UINT begin_node) noexcept;
	};
}

