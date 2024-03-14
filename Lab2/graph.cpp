#include "graph.h"
#include <typeinfo>

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

	void graph::printUintVector(std::vector<UINT>& vec, std::string vec_name) noexcept
	{
		std::cout << "=== Vector " << vec_name << " ===\n";
		for (UINT& element : vec)
			std::cout << element << '\n';
		std::cout << '\n';
	}

	void writeToFile(std::string file_path, std::string& data)
	{
		std::ofstream file(file_path);
		if (file.is_open())
		{
			file << data;
		}
		file.close();
	}

	void writeToFile(std::string file_path, std::vector<std::vector<UINT>>& data)
	{
		std::string str;
		for (std::vector<UINT>& a : data)
		{
			for (UINT& b : a) {
				str += std::to_string(b) + ' ';
			}
			str += '\n';
		}
		writeToFile(file_path, str);
	}

	Graph::Graph()
	{
		matrix_	= nullptr;
		size_	= 0;
	}

	Graph::Graph(bool** graph, UINT size)
	{
		matrix_ = graph;
		size_ = size;

		for (auto i = 0; i != size_; i++)
			lengths_.push_back(0);
	}

	Graph::~Graph()
	{
		for (auto i = 0; i != size_; i++)
		{
			delete[] matrix_[i];
		}
		delete[] matrix_;
	}

	UINT Graph::GetSize() const
	{
		return size_;
	}

	bool** graph::Graph::GetMatrix() const
	{
		return matrix_;
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
		file.close();

		lengths_.clear();
		for (auto i = 0; i != size_; i++)
			lengths_.push_back(0);

		printMatrix(matrix_, size_);
	}

	void Graph::ReadFromTxtFile(std::string file_path) noexcept
	{
		std::ifstream file(file_path);
		std::string row;

		std::getline(file, row);
		size_ = std::stoi(row);

		matrix_ = new bool* [size_];

		UINT row_num = 0;
		while (std::getline(file, row))
		{
			bool* matrix_row = new bool[size_]();

			lengths_.clear();
			UINT last_pos = 0;
			for (auto i = 0; i != size_; i++)
			{
				lengths_.push_back(0);
				UINT curr_pos = row.find(' ', last_pos);

				if (curr_pos != -1)
				{
					UINT value = std::stoi(row.substr(last_pos, curr_pos - last_pos));

					last_pos = curr_pos + 1;
					matrix_row[i] = (bool)(value);
				}
				else
				{
					UINT value = std::stoi(row.substr(last_pos));
					matrix_row[i] = (bool)(value);
					break;
				}
			}

			matrix_[row_num] = matrix_row;
			row_num++;
		}

		file.close();
	}

	bool** Graph::GetReversedGraph()
	{
		bool** reversed_matrix_ = new bool*[size_];

		for (auto i = 0; i != size_; i++)
			reversed_matrix_[i] = new bool[size_];

		for (auto i = 0; i != size_; i++)
			for (auto j = 0; j != size_; j++)
				reversed_matrix_[j][i] = matrix_[i][j];

		return reversed_matrix_;
	}

	std::optional<std::vector<UINT>> Graph::PassBFS(UINT begin_node, bool null_length, std::string path) noexcept
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
			std::string str = "";
			str += "Min length from " + std::to_string(begin_node) + ":\n";
			for (int i = 0; i < lengths_.size(); i++)
			{
				str += "to node " + std::to_string(i) + ":\t" + std::to_string(lengths_[i]) + '\n';
			}
			writeToFile(path, str);
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

	void Graph::PassDFS(UINT begin_node, std::vector<UINT>& vec) noexcept
	{
		for (UINT length : lengths_)
			length = 0;

		if (lengths_[begin_node] == 0)
		{
			lengths_[begin_node] = 1;

			for (auto i = 0; i != size_; i++)
			{
				if (matrix_[begin_node][i] == 1)
				{
					PassDFS(i, vec);
				}
			}

			vec.push_back(begin_node);
		}
	}

	std::vector<std::vector<UINT>> Graph::FindConnectDFS() noexcept
	{
		for (UINT& length : lengths_)
			length = 0;

		std::vector<std::vector<UINT>> components;

		for (auto i = 0; i != size_; i++)
		{
			if (lengths_[i] == 0)
			{
				std::vector<UINT> component;
				PassDFS(i, component);
				components.push_back(component);
			}
		}

		return components;
	}

	std::vector<std::vector<UINT>> Graph::FindStrongConnectDFS() noexcept
	{
		for (UINT& length : lengths_)
			length = 0;

		std::vector<UINT> order;
		for (auto i = 0; i != size_; i++)
		{
			bool pass_i = true;
			for (auto j = 0; j != order.size(); j++)
			{
				if (i == order[j])
				{
					pass_i = false;
					break;
				}
			}

			if (pass_i)
			{
				PassDFS(i, order);
			}
		}

		Graph ReversedGraph(GetReversedGraph(), size_);

		std::vector<std::vector<UINT>> components;
		while(order.size() != 0)
		{
			std::vector<UINT> component;
			ReversedGraph.PassDFS(order[order.size() - 1], component);

			for (UINT vertex : component)
			{
				UINT curr_pos = order.size() - 1;
				while (curr_pos != -1)
				{
					if (vertex == order[curr_pos])
						order.erase(order.begin() + curr_pos);
					curr_pos--;
				}
			}

			components.push_back(component);
		}

		return components;
	}
}