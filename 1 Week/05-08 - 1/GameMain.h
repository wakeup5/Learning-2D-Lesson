#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class GameMain
{
private:
	map<string, int> _map;
	map<string, int>::iterator _mapIter;


public:
	GameMain();
	~GameMain();

	vector<char*> charArraySeparation(char[]);
};

