#include <iostream>
#include "FSM.h"

int main()
{
	louie::FSM fsm;
	fsm.FindOneSample("cb", "test.txt", true);
	fsm.FindSamples({ "hello", "d", "t" }, "test.txt", true);
}