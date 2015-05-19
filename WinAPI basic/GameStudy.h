#pragma once
#include "GameNode.h"

#define MISSILE_SPEED 10
#define MISSILE_SIZE 5
#define MAX_MISSILE 10

using namespace std;

class GameStudy :
	public GameNode
{
private:
	typedef struct tagCannon
	{
		POINT center;
		POINT cannonEnd;
		int radius;
		float angle;
		float angleRadian;
		int length;
	} Cannon;

	typedef struct tagMissile
	{
		POINT position;
		float angleRadian;
		float angle;
		int speed;
		int radius;
		bool isFire;
	} Missile;

	Cannon _cannon;
	Missile _missiles[10];

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

