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
		std::vector<std::vector<bool>> graph_;	// ������� �����
		UINT size_;								// ������ �����
		UINT chromatic_;						// ������������� ����� �����

		// ������� �������� ������� ������, ��������� ������������� �����
		UINT GetChromatic(std::vector<int> c_vertexes);
		// ������� �������� �������������� ����� max_k �������� �� �����
		void Chromatic(UINT vertex, std::vector<int> c_vertexes, int max_k);
	public:
		Graph();
		~Graph();

		// ������� ������ ����� �� �����
		void ReadGraph(std::string file_name);
		// ������� ������ ����� � �������
		void PrintGraph();

		// ������� ���������� �������������� �����
		UINT CalculateChromatic();
	};
}