#include <iostream>
#include "graph.h"

void printEdges(std::vector<graph::Edge>& edges)
{
	for (graph::Edge& edge : edges)
		std::cout << edge.vertexes.first << " - "
		<< edge.vertexes.second << ": "
		<< edge.weight << '\n';
}

int main()
{
	graph::Graph graph_1;
	graph_1.ReadFromTxtFile("matrix.txt");

	// Задание 8
	// std::vector<graph::UINT> res = graph_1.PassDijkstra(0);
	// graph::printUintVector(res);

	// Задание 9
	/*std::vector<std::optional<int>> res = graph_1.PassBelmanFord(0);
	for (std::optional<int> dist : res)
	{
		std::cout << dist.value() << '\n';
	}*/
}