#pragma once
#include "GameNode.h"
class Screen1 :
	public GameNode
{
private:
	char _str[128];
public:
	Screen1();
	virtual ~Screen1();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void controlMessage(int message);
};

