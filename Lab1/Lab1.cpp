#include <iostream>
#include "dots.h"

std::ostream& operator<< (std::ostream& stream, dots::Oxy point)
{
	return stream << point.x << ", " << point.y;
}

int main()
{
	std::vector<dots::Oxy> points;

	for (int i = 0; i < 5; i++)
	{
		float a, b;
		std::cin >> a >> b;
		points.push_back(dots::Oxy{ a, b });
		std::cout << '\n';
	}

	std::vector res = dots::GetConvexHull(points).value();

	for (dots::Oxy& point : res)
	{
		std::cout << point << '\n';
	}
}