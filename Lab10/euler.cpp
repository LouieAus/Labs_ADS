#include "euler.h"

namespace euler
{
	bool isGraphEuler(Matrix& graph)
	{
		for (std::vector<int>& vertex: graph)
		{
			int count = 0;
			for (int v : vertex)
				if (v == 1)
					count++;

			if (count % 2 == 1)
				return false;
		}

		return true;
	}

	std::vector<int> FindEuler(Matrix graph, int begin_vertex)
	{
		std::vector<int> result;

		if (!isGraphEuler(graph))
			return std::vector<int> { -1 };

		std::stack<int> S;
		S.push(begin_vertex);
		while (S.size() != 0)
		{
			int current_vertex = S.top();

			bool found = false;
			for (int i = 0; i != graph[current_vertex].size(); i++)
			{
				if (graph[current_vertex][i] == 1)
				{
					S.push(i);
					graph[current_vertex][i] = 0;
					graph[i][current_vertex] = 0;
					found = true;
					break;
				}
			}

			if (found == false)
			{
				S.pop();
				result.push_back(current_vertex);
			}
		}

		return result;
	}

	void PrintVector(std::vector<int> vec)
	{
		for (int v : vec)
		{
			std::cout << v << '\t';
		}
		std::cout << '\n';
	}
}