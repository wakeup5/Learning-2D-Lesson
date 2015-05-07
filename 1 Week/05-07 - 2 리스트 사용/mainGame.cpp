#include "mainGame.h"


mainGame::mainGame()
{
	for (int i = 0; i < 10; i++)
	{
		_list.push_back(i * 100);
	}

	_listIterator = _list.begin();
	_listIterator++;
	_listIterator++;
	_listIterator++;
	_listIterator++;
	_list.erase(_listIterator);
	//_list.remove(500);

	for (_listIterator = _list.begin(); _listIterator != _list.end(); _listIterator++)
	{
		cout << *_listIterator << endl;
	}


	//맵
	_map.insert(map<int, int>::value_type(1, 100));
	_map.insert(pair<int, int>(2, 2000));
	_map.insert(make_pair(3, 103124));

	for (_mapIter = _map.begin(); _mapIter != _map.end(); _mapIter++)
	{
		cout << "k : " << _mapIter->first << ", v : " << _mapIter->second << endl;
	}

	//맵(string, int)
	_sMap.insert(make_pair("수퍼맨", 100));
	_sMap.insert(make_pair("아이언맨", 50));
	_sMap.insert(make_pair("배트맨", 30));
	_sMap.insert(make_pair("에스퍼맨", 10));
	_sMap.insert(make_pair("가맨", 30));

	for (_siMap = _sMap.begin(); _siMap != _sMap.end(); _siMap++)
	{
		cout << "name : " << _siMap->first << ", score : " << _siMap->second << endl;
	}

	//맵 찾기. 찾는 키 데이터가 없으면 새로 만든다. 단점..
	if (_sMap["가맨"])
	{
		cout << _sMap["가맨"];
	}
	_sMap.erase("가맨");

	//맵 찾기 2
	if ((_siMap = _sMap.find("가맨")) != _sMap.end())
	{
		cout << _siMap->second;
		cout << _sMap.at("가맨");
	}

	_siMap = _sMap.find("가맨");

	

}


mainGame::~mainGame()
{
}
