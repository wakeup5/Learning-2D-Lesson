#pragma once
#include "GameNode.h"
#include "Sceen1.h"

class GameStudy :
	public GameNode
{
private:

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

};
