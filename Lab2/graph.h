#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

namespace graph
{
	typedef unsigned char	BYTE;
	typedef unsigned int	UINT;

	// ������� ����������� 4 ������ � unsigned int
	UINT getFromBytes(char* bytes) noexcept;

	// ������� ������ �������
	template<typename T> void printMatrix(T** matrix, UINT size_) noexcept;

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
		std::optional<std::vector<UINT>> PassBFS(UINT begin_node, bool null_length = true) noexcept;
		// ������� ���������� ������� ���������� ���������
		std::vector< std::vector<UINT>> FindConnectBFS() noexcept;
		// ������� ������ � �������
		void PassDFS(UINT begin_node) noexcept;
	};
}

