#pragma once
#include <list>
#include <iostream>

using namespace std;

class mainGame
{
private:
	list<int> _list;
	list<int>::iterator _listIterator;

public:
	mainGame();
	~mainGame();
};

