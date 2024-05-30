#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> FindArraySumm(std::vector<int> nums, int summ)
{
	std::sort(nums.begin(), nums.end(), [](int a, int b) { return a < b; });

	std::vector<int> result;
	int temp_summ = 0;

	for (auto i = 0; i != nums.size(); i++)
	{
		int temp1 = summ - (temp_summ + nums[i]);
		int temp2 = summ - temp_summ;

		if (temp1 == 0)
		{
			result.push_back(nums[i]);
			return result;
		}
		else if (temp1 > 0 && temp1 < temp2)
		{
			temp_summ += nums[i];
			result.push_back(nums[i]);
		}
	}

	return result;
}

int main()
{
	std::vector<int> data = { 22, 7, 1, 4, 9, 10, 4, 38 };
	std::vector<int> res = FindArraySumm(data, 18);
	
	for (int r : res)
		std::cout << r << '\t';
}