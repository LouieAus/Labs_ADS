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
		matrix_ = nullptr;
		size_ = 0;
	}

	Graph::Graph(int** graph, UINT size)
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

	int** graph::Graph::GetMatrix() const
	{
		return matrix_;
	}

	std::vector<UINT> Graph::GetLength() const
	{
		return lengths_;
	}

	void Graph::SetEdge(UINT a, UINT b, int weight, bool bind)
	{
		matrix_[a][b] = weight;
		if (bind)
			matrix_[b][a] = weight;
	}

	void Graph::ReadFromFile(std::string file_path) noexcept
	{
		std::ifstream file(file_path, std::ios::binary);
		if (file.is_open())
		{
			char dwBuff[4];

			file.read(dwBuff, 4);
			size_ = getFromBytes(dwBuff);

			matrix_ = new int* [size_];
			for (auto i = 0; i < size_; i++)
			{
				matrix_[i] = new int[size_];

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

		matrix_ = new int* [size_];

		lengths_.clear();

		UINT row_num = 0;
		while (std::getline(file, row))
		{
			lengths_.push_back(0);

			int* matrix_row = new int[size_]();

			UINT last_pos = 0;
			for (auto i = 0; i != size_; i++)
			{
				UINT curr_pos = row.find(' ', last_pos);

				if (curr_pos != -1)
				{
					UINT value = std::stoi(row.substr(last_pos, curr_pos - last_pos));

					last_pos = curr_pos + 1;
					matrix_row[i] = (UINT)(value);
				}
				else
				{
					UINT value = std::stoi(row.substr(last_pos));
					matrix_row[i] = (UINT)(value);
					break;
				}
			}

			matrix_[row_num] = matrix_row;
			row_num++;
		}

		file.close();
	}

	void Graph::PassDFS(UINT begin_node, std::vector<UINT>& vec, bool begin) noexcept
	{
		if (begin)
		{
			for (UINT& length : lengths_)
				length = 0;
		}

		if (lengths_[begin_node] == 0)
		{
			lengths_[begin_node] = 1;

			for (auto i = 0; i != size_; i++)
			{
				if (matrix_[begin_node][i] != 0)
				{
					PassDFS(i, vec, false);
				}
			}

			vec.push_back(begin_node);
		}
	}

	bool checkBind(Graph& check_graph, UINT a, UINT b)
	{
		std::vector<UINT> vertexes;
		check_graph.PassDFS(a, vertexes);

		for (UINT vertex : vertexes)
		{
			if (vertex == b)
				return true;
		}

		return false;
	}

	std::vector<Edge> Graph::PassKruskal() noexcept
	{
		std::vector<Edge> edges;
		for (auto i = 0; i != size_; i++)
		{
			for (auto j = i; j != size_; j++)
			{
				if (matrix_[i][j] != 0)
				{
					edges.push_back(Edge{ std::make_pair<UINT, UINT>(i, j), matrix_[i][j] });
				}
			}
		}
		std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {return a.weight > b.weight; });

		int** new_matrix = new int * [size_];
		for (auto i = 0; i != size_; i++)
		{
			new_matrix[i] = new int[size_];
			for (auto j = 0; j != size_; j++)
			{
				new_matrix[i][j] = 0;
			}
		}
		Graph result_graph(new_matrix, size_);

		UINT curr_pos = edges.size() - 1;
		while (curr_pos != -1)
		{
			UINT a = edges[curr_pos].vertexes.first;
			UINT b = edges[curr_pos].vertexes.second;
			UINT weight = edges[curr_pos].weight;

			if (!checkBind(result_graph, a, b))
			{
				result_graph.SetEdge(a, b, weight);
				result_graph.SetEdge(b, a, weight);
			}
			else
			{
				edges.erase(edges.begin() + curr_pos);
			}

			curr_pos--;
		}

		return edges;
	}

	std::vector<Edge> Graph::PassPrima() noexcept
	{
		std::vector<Edge> result;

		std::vector<UINT> vertexes;
		vertexes.push_back(0);

		int** new_matrix = new int * [size_];
		for (auto i = 0; i != size_; i++)
		{
			new_matrix[i] = new int[size_];
			for (auto j = 0; j != size_; j++)
			{
				new_matrix[i][j] = 0;
			}
		}
		Graph result_graph(new_matrix, size_);

		while (true)
		{
			if (result.size() + 1 == size_)
				break;

			Edge min_edge;
			bool first = true;
			for (int i : vertexes)
			{
				for (auto j = 0; j != size_; j++)
				{
					if (!checkBind(result_graph, i, j) && matrix_[i][j] != 0)
					{
						if (first)
						{
							min_edge = { std::make_pair<UINT, UINT>(i, j), matrix_[i][j] };
							first = false;
						}
						else
						{
							if (min_edge.weight > matrix_[i][j])
							{
								min_edge.vertexes.first = i;
								min_edge.vertexes.second = j;
								min_edge.weight = matrix_[i][j];
							}
						}
					}
				}
			}

			result.push_back(min_edge);
			vertexes.push_back(min_edge.vertexes.second);
			result_graph.SetEdge(min_edge.vertexes.first, min_edge.vertexes.second, min_edge.weight, true);
		}

		return result;
	}

	bool isInVec(std::vector<UINT> vec, UINT num)
	{
		for (UINT in_num : vec)
		{
			if (num == in_num)
				return true;
		}
		return false;
	}

	std::vector<UINT> Graph::PassDijkstra(UINT vertex, bool to_null, std::vector<UINT> check_vertexes) noexcept
	{
		if (to_null)
		{
			lengths_ = {};
			for (UINT k = 0; k != size_; k++)
				lengths_.push_back(-1);
			lengths_[vertex] = 0;
		}

		for (UINT i = 0; i != size_; i++)
		{
			if (matrix_[vertex][i] != 0 && i != vertex)
			{
				if ((lengths_[i] == -1) || (matrix_[vertex][i] + lengths_[vertex] < lengths_[i]))
					lengths_[i] = matrix_[vertex][i] + lengths_[vertex];
			}
		}
		check_vertexes.push_back(vertex);

		if (check_vertexes.size() != size_)
		{
			int min = -1;
			int next_vertex = 0;
			for (UINT j = 0; j != size_; j++)
			{
				if (!isInVec(check_vertexes, j))
				{
					if (min == -1 && lengths_[j] != -1)
					{
						min = lengths_[j];
						next_vertex = j;
					}
					else if (lengths_[j] < min)
					{
						min = lengths_[j];
						next_vertex = j;
					}
				}
			}
			PassDijkstra(next_vertex, false, check_vertexes);
		}

		return lengths_;
	}

	std::vector<Edge> Graph::matrixToEdges()
	{
		std::vector<Edge> edges;
		for (auto i = 0; i != size_; i++)
		{
			for (auto j = 0; j != size_; j++)
			{
				if (matrix_[i][j] != 0)
					edges.push_back(Edge{ std::make_pair<UINT>(i, j), matrix_[i][j] });
			}
		}
		return edges;
	}

	std::optional<int> getMinDistance(std::optional<int> a, std::optional<int> b, int weight)
	{
		if (a.has_value() && b.has_value())
			return (a.value() < b.value() + weight) ? (a.value()) : (b.value() + weight);

		if (a.has_value() && !b.has_value())
			return a.value();

		if (!a.has_value() && b.has_value())
			return b.value() + weight;

		return std::nullopt;
	}

	std::vector<std::optional<int>> Graph::PassBelmanFord(UINT begin)
	{
		std::vector<Edge> edges = matrixToEdges();
		for (auto j = 0; j != edges.size(); j++)
			std::cout << edges[j].weight << " <= " << edges[j].vertexes.first << ", " << edges[j].vertexes.second << '\n';

		std::vector<std::optional<int>> distances(size_);
		for (auto j = 0; j != size_; j++)
			distances[j] = std::nullopt;

		distances[begin] = 0;

		for (auto i = 0; i != size_ - 1; i++)
		{
			for (Edge& edge : edges)
			{
				distances[edge.vertexes.second] = getMinDistance(
													distances[edge.vertexes.second],
													distances[edge.vertexes.first],
													edge.weight);
			}
		}

		return distances;
	}

	bool Graph::checkPower()
	{
		for (int i = 0; i != size_; i++)
		{
			int vertexes = 0;
			for (int j = 0; j != size_; j++)
			{
				if (matrix_[i][j] != 0)
					vertexes++;
			}
			if (vertexes % 2 != 0)
				return false;
		}
		return true;
	}

	std::vector<UINT> Graph::PassEuler(UINT begin)
	{
		
	}
}