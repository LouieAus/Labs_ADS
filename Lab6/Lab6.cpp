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

	// Задание 6
	std::vector<graph::Edge> result1 = graph_1.PassKruskal();
	printEdges(result1);
	std::cout << '\n';
	// Задание 7
	std::vector<graph::Edge> result2 = graph_1.PassPrima();
	printEdges(result2);
}