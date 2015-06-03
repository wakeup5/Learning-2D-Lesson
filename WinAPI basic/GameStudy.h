#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "Enemy.h"

class GameStudy :
	public GameNode
{
private:
	Rocket* _rocket;
	Enemy* _enemy;

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};
