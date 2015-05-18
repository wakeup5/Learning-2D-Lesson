#pragma once
#include "GameNode.h"

using namespace std;

class GameStudy :
	public GameNode
{
private:
	
public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

