#include <iostream>
#include "KMP.h"

int main()
{
	louie::KMP kmp;
	std::vector<louie::UINT> res = kmp.Find("hello, i am louie", "am", true);
}