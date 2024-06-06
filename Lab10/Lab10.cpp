#include <iostream>
#include "euler.h"

int main()
{
	euler::Matrix graph1 = {
		{ 0, 1, 0, 1 },
		{ 1, 0, 1, 0 },
		{ 0, 1, 0, 1 },
		{ 1, 0, 1, 0 } };
								
	euler::Matrix graph2 = {
		{ 0, 1, 0, 1 },	
		{ 1, 0, 1, 1 },
		{ 0, 1, 0, 1 },
		{ 1, 1, 1, 0 } };
	

	euler::PrintVector(euler::FindEuler(graph1, 0));
	euler::PrintVector(euler::FindEuler(graph2, 0));
}