#include <iostream>
#include <vector>
#include <algorithm>

void Print2DimVec(std::vector<std::vector<int>> data)
{
	std::cout << '\n';
	for (std::vector<int>& vec : data)
	{
		for (int id : vec)
			std::cout << id << '\t';
		std::cout << '\n';
	}
}

class Containers
{
private:
	int crate_q_;					//Количество ящиков
	float crate_V_;					// Объем ящиков
	
	int objects_q_;					// Количество объектов (предметов)
	std::vector<float> objects_;	// Массив объемов объектов

	// Метод сортировки объектов по убыванию
	std::vector<float> SortObjDecrease();

	// Метод суммирует объем объектов в контейнере
	float SummCrate(std::vector<int>& crate, std::vector<float>& objects);
public:
	Containers(int crate_q, float crate_v, std::vector<float>& objects)
	{
		crate_q_ = crate_q;
		crate_V_ = crate_v;
		objects_q_ = objects.size();
		objects_ = objects;
	}

	std::vector<std::vector<int>> CalcBFD();	// Best Fit Decreasing алгоритм
	std::vector<std::vector<int>> CalcFFD();	// First Fit Decreasing алгоритм
};

std::vector<float> Containers::SortObjDecrease()
{
	std::vector<float> temp = objects_;
	std::sort(temp.begin(), temp.end(), [](float a, float b) { return a > b; });
	return temp;
}

float Containers::SummCrate(std::vector<int>& crate, std::vector<float>& objects)
{
	float result = 0.0;
	for (int obj_id : crate)
	{
		result += objects[obj_id];
	}
	return result;
}

std::vector<std::vector<int>> Containers::CalcBFD()
{
	std::vector<std::vector<int>> result;
	for (auto i = 0; i != crate_q_; i++)
		result.push_back(std::vector<int>());

	std::vector<float> objects = SortObjDecrease();
	for (float o : objects)
		std::cout << o << '\t';

	// Перебираем все объекты
	for (auto j = 0; j != objects_q_; j++)
	{
		int choosen_crate = 0;
		float choosen_free_V = crate_V_;

		// Перебираем каждый контейнер
		for (auto i = 0; i != crate_q_; i++)
		{
			float temp_V = SummCrate(result[i], objects) + objects[j];
			// Если объект влезает в контейнер
			if (temp_V <= crate_V_)
			{
				// Если в этом контейнере свободного места меньше, чем в выбранном
				if (choosen_free_V > crate_V_ - temp_V)
				{
					// Выбираем найденный контейнер
					choosen_crate = i;
					choosen_free_V = crate_V_ - temp_V;
				}
			}
		}

		// Добавляем в контейнер объект
		result[choosen_crate].push_back(j);
	}

	return result;
}

std::vector<std::vector<int>> Containers::CalcFFD()
{
	std::vector<std::vector<int>> result;
	for (auto i = 0; i != crate_q_; i++)
		result.push_back(std::vector<int>());

	std::vector<float> objects = SortObjDecrease();
	for (float o : objects)
		std::cout << o << '\t';

	// Перебираем все объекты
	for (auto j = 0; j != objects_q_; j++)
	{
		// Перебираем каждый контейнер
		for (auto i = 0; i != crate_q_; i++)
		{
			float temp_V = SummCrate(result[i], objects) + objects[j];
			// Если объект влезает в контейнер
			if (temp_V <= crate_V_)
			{
				// Добавляем в контейнер объект
				result[i].push_back(j);
				break;
			}
		}
	}

	return result;
}

int main()
{
	std::vector<float> obj = { 1.5, 0.7, 4.1, 1.2, 1.0, 3.7, 4.6, 1.7, 0.1, 0.2, 5.0 };
	Containers cont_1(10, 5, obj);

	Print2DimVec(cont_1.CalcBFD());

	Print2DimVec(cont_1.CalcFFD());
}