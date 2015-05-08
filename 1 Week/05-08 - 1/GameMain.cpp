#include "GameMain.h"

GameMain::GameMain()
{
	int dataNum;
	char temp[64];

	cout << "������ � �Է�? ���� �Է� : ";
	cin >> dataNum;
	cin.get();

	for (int i = 0; i < dataNum; i++)
	{
		//������ �޸𸮸� �ʱ�ȭ �Ѵ�.
		//memset�� 3�� ����, ZeroMemory�� 2�� ����. ZeroMemory�� 0���� �ʱ�ȭ �Ѵ�.
		//memset(���, 0(�ʱ�ȭ ��), ������)
		//ZeroMemory(���, ������);
		ZeroMemory(temp, sizeof(temp));

		cout << i + 1 << "��° �����͸� �Է� : ";
		cin.getline(temp, 64);

		vector<char*> charVector = charArraySeparation(temp);

		// atoi(������ ����) ���ڸ� ���ڷ� �� �ٲ�.
		// itoa(����) ���ڸ� ���������� �ٲ�.
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