#include "graph.h"

namespace graph
{
	UINT getFromBytes(char* bytes) noexcept
	{
		UINT a = UINT((BYTE)(bytes[0]) |
			(BYTE)(bytes[1]) << 8 |
			(BYTE)(bytes[2]) << 16 |
			(BYTE)(bytes[3]) << 24);

		return a;
	}

	template<typename T>
	void printMatrix(T** matrix, UINT size_) noexcept
	{
		for (auto i = 0; i != size_; i++)
		{
			std::cout << i << ":\t";
			for (auto j = 0; j != size_; j++)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << '\n';
		}
	}

	Graph::Graph()
	{
		matrix_	= nullptr;
		size_	= 0;
	}

	Graph::~Graph()
	{
		for (auto i = 0; i != size_; i++)
		{
			delete[] matrix_[i];
		}
		delete[] matrix_;
	}

	void Graph::ReadFromFile(std::string file_path) noexcept
	{
		std::ifstream file(file_path, std::ios::binary);
		if (file.is_open())
		{
			char dwBuff[4];

			file.read(dwBuff, 4);
			size_ = getFromBytes(dwBuff);

			matrix_ = new bool* [size_];
			for (auto i = 0; i < size_; i++)
			{
				matrix_[i] = new bool[size_];

				char* bytes = new char[size_];

				file.read(bytes, size_);
				memcpy(matrix_[i], bytes, size_);

				delete[] bytes;
			}

		}

		lengths_.clear();
		for (auto i = 0; i != size_; i++)
			lengths_.push_back(0);

		printMatrix(matrix_, size_);
	}


	std::optional<std::vector<UINT>> Graph::PassBFS(UINT begin_node, bool null_length) noexcept
	{
		std::vector<UINT> connect_comp;

		if (null_length)
		{
			for (UINT& length : lengths_)
			{
				length = 0;
			}
		}

		std::queue<UINT> gray_nodes;
		gray_nodes.push(begin_node);

		while (gray_nodes.size() != 0)
		{
			UINT node = gray_nodes.front();
			gray_nodes.pop();

			if (!null_length)
			 connect_comp.push_back(node);

			for (UINT i = 0; i < size_; i++)
			{
				if (i != begin_node)
				{
					if (matrix_[node][i] == 1 && lengths_[i] == 0)
					{
						lengths_[i] = lengths_[node] + 1;
						gray_nodes.push(i);
					}
				}
			}
		}

		if (null_length)
		{
			std::cout << "\nMin length from " << begin_node << ":\n";
			for (int i = 0; i < lengths_.size(); i++)
			{
				std::cout << "to node " << i << ":\t" << lengths_[i] << '\n';
			}
		}

		if (!null_length)
			return connect_comp;
		else
			return std::nullopt;
	}

	std::vector<std::vector<UINT>> Graph::FindConnectBFS() noexcept
	{
		std::vector<std::vector<UINT>> components;

		for (UINT& length : lengths_)
		{
			length = 0;
		}

		if (size_ != 0)
		{
			UINT i = 0;
			while (true)
			{
				bool pass = true;
				while (lengths_[i] != 0)
				{
					if (i == lengths_.size())
					{
						pass = false;
						break;
					}
					i++;
				}
				if (pass && i != lengths_.size())
				{
					std::vector<UINT> result = PassBFS(i, false).value();
					components.push_back(std::move(result));
					i++;
				}
				else
					break;
			}
		}
		return components;
	}

	void Graph::PassDFS(UINT begin_node) noexcept
	{
		for (UINT& length : lengths_)
		{
			length = 0;
		}
		std::stack<UINT> gray_nodes;

		gray_nodes.push(begin_node);

		while (gray_nodes.size() != 0)
		{
			UINT node = gray_nodes.top();
			gray_nodes.pop();

			for (UINT i = 0; i < size_; i++)
			{
				if (i != begin_node)
				{
					if (matrix_[node][i] == 1 && lengths_[i] == 0)
					{
						lengths_[i] = lengths_[node] + 1;
						gray_nodes.push(i);
					}
				}
			}
		}

		std::cout << "\nLength from " << begin_node << ":\n";
		for (int i = 0; i < lengths_.size(); i++)
		{
			std::cout << "to node " << i << ":\t" << lengths_[i] << '\n';
		}
	}
}