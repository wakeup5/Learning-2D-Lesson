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


	//��
	_map.insert(map<int, int>::value_type(1, 100));
	_map.insert(pair<int, int>(2, 2000));
	_map.insert(make_pair(3, 103124));

	for (_mapIter = _map.begin(); _mapIter != _map.end(); _mapIter++)
	{
		cout << "k : " << _mapIter->first << ", v : " << _mapIter->second << endl;
	}

	//��(string, int)
	_sMap.insert(make_pair("���۸�", 100));
	_sMap.insert(make_pair("���̾��", 50));
	_sMap.insert(make_pair("��Ʈ��", 30));
	_sMap.insert(make_pair("�����۸�", 10));
	_sMap.insert(make_pair("����", 30));

	for (_siMap = _sMap.begin(); _siMap != _sMap.end(); _siMap++)
	{
		cout << "name : " << _siMap->first << ", score : " << _siMap->second << endl;
	}

	//�� ã��. ã�� Ű �����Ͱ� ������ ���� �����. ����..
	if (_sMap["����"])
	{
		cout << _sMap["����"];
	}
	_sMap.erase("����");

	//�� ã�� 2
	if ((_siMap = _sMap.find("����")) != _sMap.end())
	{
		cout << _siMap->second;
		cout << _sMap.at("����");
	}

	_siMap = _sMap.find("����");

	

}


mainGame::~mainGame()
{
}
