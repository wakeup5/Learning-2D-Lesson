#pragma once
#include <list>
#include <map>
#include <iostream>
#include <string>

using namespace std;

class mainGame
{
private:
	list<int> _list;
	list<int>::iterator _listIterator;

	map<int, int> _map;
	map<int, int>::iterator _mapIter;

	map<string, int> _sMap;
	map<string, int>::iterator _siMap;

public:
	mainGame();
	~mainGame();
};

