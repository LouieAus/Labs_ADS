#include <iostream>
#include "graph.h"

int main()
{
	graph::Graph graph_1;
	graph_1.ReadFromFile("file_matrix.matr");

	graph_1.PassBFS(0, true, "res1.txt");

	std::vector<std::vector<graph::UINT>> res = graph_1.FindConnectBFS();
	graph::writeToFile("res2.txt", res);
}