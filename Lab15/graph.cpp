#include "graph.h"

namespace graph
{
	Graph::Graph()
	{
		size_ = 0;
	}

	Graph::~Graph() {}

	void Graph::ReadGraph(std::string file_name)
	{
		std::string line;
		std::ifstream in_file(file_name);
		if (in_file.is_open())
		{
			std::string n_str;
			std::getline(in_file, n_str);
			size_ = std::stoi(n_str);

			while (std::getline(in_file, line))
			{
				std::vector<bool> row;
				for (auto i = 0; i != size_; i++)
				{
					row.push_back((bool)(line[2 * i] - 48));
				}
				graph_.push_back(row);
			}
		}
		in_file.close();
	}

	void Graph::PrintGraph()
	{
		for (std::vector<bool>& row : graph_)
		{
			for (bool edge : row)
			{
				std::cout << edge << '\t';
			}
			std::cout << '\n';
		}
	}

	UINT Graph::GetChromatic(std::vector<int> c_vertexes)
	{
		UINT chromatic = 0;

		for (UINT i = 0; i != size_; i++)
		{
			for (UINT j = 0; j != size_; j++)
			{
				if (graph_[i][j] == 1)
				{
					if (c_vertexes[i] == c_vertexes[j])
						return 0;
				}
			}

			if (c_vertexes[i] > chromatic)
				chromatic = c_vertexes[i];
		}

		return chromatic;
	}

	void Graph::Chromatic(UINT vertex, std::vector<int> c_vertexes, int max_k)
	{
		if (vertex == size_)
			return;

		for (UINT k = 1; k != max_k + 1; k++)
		{
			c_vertexes[vertex] = k;
			if (vertex == size_ - 1)
			{
				UINT res = GetChromatic(c_vertexes);
				if (res != 0)
				{
					if (chromatic_ == 0)
						chromatic_ = res;
					else if (res < chromatic_)
						chromatic_ = res;
				}
			}
			else
				Chromatic(vertex + 1, c_vertexes, max_k);
		}
	}

	UINT Graph::CalculateChromatic()
	{
		for (UINT k = 1; k != size_ + 1; k++)
		{
			std::vector<int> c_vec(size_, 0);
			Chromatic(0, c_vec, k);
		}

		return chromatic_;
	}
}