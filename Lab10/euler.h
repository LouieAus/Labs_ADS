#pragma once
#include <iostream>
#include <stack>
#include <vector>

namespace euler
{
	typedef std::vector<std::vector<int>> Matrix;

	void PrintVector(std::vector<int> vec);

	std::vector<int> FindEuler(Matrix graph, int begin_vertex);
}