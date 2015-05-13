#pragma once

#include "SingletonBase.h"

class RandomFunction : public SingletonBase < RandomFunction >
{
public:
	RandomFunction()
	{
		srand((unsigned int)time(NULL));
	}

	~RandomFunction()
	{

	}

	int getint(int num = 10)
	{
		return rand() % num;
	}

	int getIntTo(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}
};