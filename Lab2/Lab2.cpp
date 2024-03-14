#include <iostream>
#include "graph.h"

int main()
{
	graph::Graph graph_1;
	graph_1.ReadFromTxtFile("matrix.txt");

	// Задание 4 O (n + m)
	std::vector<std::vector<graph::UINT>> connected_graphs = graph_1.FindConnectDFS();
	graph::writeToFile("res3.txt", connected_graphs);

	// Задание 5 от O(n + m) до O(n^2)
	std::vector<std::vector<graph::UINT>> strong_connected_graphs = graph_1.FindStrongConnectDFS();
	graph::writeToFile("res4.txt", strong_connected_graphs);
}