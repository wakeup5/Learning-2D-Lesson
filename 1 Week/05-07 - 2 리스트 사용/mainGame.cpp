#include "mainGame.h"


mainGame::mainGame()
{
	for (int i = 0; i < 10; i++)
	{
		_list.push_back(i + 1);
	}

	_list.push_front(100);

	for (_listIterator = _list.begin(); _listIterator != _list.end(); _listIterator++)
	{
		cout << *_listIterator << endl;
	}
}


mainGame::~mainGame()
{
}
