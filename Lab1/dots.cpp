#include "dots.h"

namespace dots
{
	bool operator== (dots::Oxy& point1, dots::Oxy& point2)
	{
		if (point1.x == point2.x && point1.y == point2.y)
			return true;
		return false;
	}

	float countAngle(Oxy& vec1, Oxy& vec2)
	{
		double scalar = vec1.x * vec2.x + vec1.y * vec2.y;
		double len_1 = sqrtf(vec1.x * vec1.x + vec1.y * vec1.y);
		double len_2 = sqrtf(vec2.x * vec2.x + vec2.y * vec2.y);

		return acos(scalar / (len_1 * len_2));
	}

	std::optional<std::vector<Oxy>> GetConvexHull(std::vector<Oxy> points)
	{
		if (points.size() == 0)
			return std::nullopt;

		std::vector<Oxy> convex_hull;		// Вектор точек выпуклой оболочки
		Oxy BeginPoint = points[0];			// Начальная точка

		// Поиск самой нижней правой точки
		for (Oxy& point: points)
		{
			if ((point.y < BeginPoint.y) ||
				((point.y == BeginPoint.y) && (point.x > BeginPoint.x)))
			{
				BeginPoint = point;
			}
		}
		convex_hull.push_back(BeginPoint);

		Oxy CurrentPoint = BeginPoint;								// Текущая точка, от которой идет проверка
		Oxy PreviousPoint = { BeginPoint.x - 1.0f, BeginPoint.y };	// Предыдущая точка (нужная для нахождения векторов)

		// Процесс нахождения выпкулой оболочки
		while (true)
		{
			float min_angle = 3.0f * PI;							// Минимальный угол между векторами
			Oxy NextPoint;											// Следующая точка

			// Поиск подходящей точки по углу между векторами
			for (Oxy& point : points)
			{
				Oxy vec1 = { CurrentPoint.x - PreviousPoint.x, CurrentPoint.y - PreviousPoint.y };
				Oxy vec2 = { point.x - CurrentPoint.x, point.y - CurrentPoint.y };

				float angle = countAngle(vec1, vec2);
				if (angle != 0.0f && angle < min_angle) {
					min_angle = angle;
					NextPoint = point;
				}
			}

			if (NextPoint == BeginPoint)
				break;

			convex_hull.push_back(NextPoint);
			PreviousPoint = CurrentPoint;
			CurrentPoint = NextPoint;
		}

		return convex_hull;
	}

}