#pragma once

#include "Singletonbase.h"
#include <vector>

class txtDataManager : public SingletonBase <txtDataManager>
{
public:
	HRESULT init(void);
	void release(void);

	//���̺�~~
	void txtSave(const char* saveFileName,
		vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//�ε�
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);	

	txtDataManager(void);
	~txtDataManager(void);
};
