#pragma once
#include <iostream>
#include <vector>
#include <optional>

constexpr auto PI = 3.141592653589793;
constexpr auto HALF_PI = PI / 2.0f;
constexpr auto THALF_PI = 3.0f * HALF_PI;

namespace dots
{	
	struct Oxy
	{
		float x = 0.0f;
		float y = 0.0f;
	};

	// Функция вычисления угла между векторами
	float countAngle(Oxy& vec1, Oxy& vec2);

	// Функция нахождения выпуклой оболочки по алгоритму Джарвиса
	std::optional<std::vector<Oxy>> GetConvexHull(std::vector<Oxy> points);
}