#pragma once
#include "GameNode.h"
#include "Cannon.h"
#include "Bullet.h"

#define MAX_BULLET 100
#define MAX_POWER 20

using namespace std;

class GameStudy :
	public GameNode
{
private:
    Cannon _cannon;
    Bullet _bullet[MAX_BULLET];

    float _power;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

