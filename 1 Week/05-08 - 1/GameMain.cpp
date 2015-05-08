#include "GameMain.h"

GameMain::GameMain()
{
	int dataNum;
	char temp[64];

	cout << "데이터 몇개 입력? 갯수 입력 : ";
	cin >> dataNum;
	cin.get();

	for (int i = 0; i < dataNum; i++)
	{
		//변수의 메모리를 초기화 한다.
		//memset은 3개 인자, ZeroMemory는 2개 인자. ZeroMemory는 0으로 초기화 한다.
		//memset(대상, 0(초기화 값), 사이즈)
		//ZeroMemory(대상, 사이즈);
		ZeroMemory(temp, sizeof(temp));

		cout << i + 1 << "번째 데이터를 입력 : ";
		cin.getline(temp, 64);

		vector<char*> charVector = charArraySeparation(temp);

		// atoi(문자형 숫자) 문자를 숫자로 형 바꿈.
		// itoa(숫자) 숫자를 문자형으로 바꿈.
		_map.insert(make_pair(charVector[0], atoi(charVector[1])));
		charVector.clear();
	}

	for (_mapIter = _map.begin(); _mapIter != _map.end(); _mapIter++)
	{
		cout << _mapIter->first << ", " << _mapIter->second << endl;
	}
}


GameMain::~GameMain()
{
}

vector<char*> GameMain::charArraySeparation(char charArray[])
{
	vector<char*> charVector;
	char* temp;
	char* separator = ",";
	char* token;

	token = strtok_s(charArray, separator, &temp);
	charVector.push_back(token);

	while ((token = strtok_s(NULL, separator, &temp)) != NULL)
	{
		charVector.push_back(token);
	}

	return charVector;
}