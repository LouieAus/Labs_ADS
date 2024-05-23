#include <iostream>
#include "graph.h"

using namespace graph;

int main()
{
	Graph graph_1;
	graph_1.ReadGraph("graph.txt");
	graph_1.PrintGraph();

	std::cout << "\nC = " << graph_1.CalculateChromatic();
}