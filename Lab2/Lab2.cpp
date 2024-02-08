#include <iostream>
#include "graph.h"

int main()
{
	graph::Graph graph_1;
	graph_1.ReadFromFile("file_matrix.matr");
	std::vector<std::vector<graph::UINT>> res = graph_1.FindConnectBFS();

	for (auto& a : res)
	{
		for (auto& b : a) {
			std::cout << b << ' ';
		}
		std::cout << '\n';
	}
}