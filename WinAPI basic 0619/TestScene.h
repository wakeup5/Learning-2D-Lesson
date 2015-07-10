#pragma once
#include "SceneManager.h"
class TestScene :
	public Scene
{
public:
	TestScene();
	~TestScene();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};

class AA : public DataObject
{
public:
	int _a;
	int _b;

	virtual int toString(vector<string>& info)
	{
		info.push_back(to_string(_a));
		info.push_back(to_string(_b));

		return getStrLenByList(info);
	}

	virtual int toObject(vector<string> info)
	{
		_a = atoi(info[0].c_str());
		_b = atoi(info[1].c_str());

		return getStrLenByList(info);
	}
};