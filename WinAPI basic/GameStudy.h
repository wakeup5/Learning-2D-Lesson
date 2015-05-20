#pragma once
#include "GameNode.h"

#define MISSILE_SPEED 5
#define MISSILE_SIZE 50
#define MAX_MISSILE 200

#define PLAYER_SPEED 2

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
		double px, py;
		float angleRadian;
		float angle;
		int speed;
		int radius;
		bool isFire;
	} Missile;

	Cannon _cannon;
	Missile _missiles[MAX_MISSILE];

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

