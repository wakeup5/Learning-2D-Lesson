#pragma once
#include "GameObject.h"
#include "Missile.h"

//game value define
#define PLAYER_SPEED 5

#define MAX_MISSILE 100
#define MAX_BASIC 10
#define MAX_SPECIAL_1 25
#define MAX_SPECIAL_2 30
#define MAX_SPECIAL_3 20

#define COOLTIME_BASIC 100
#define COOLTIME_SPECIAL_1 100
#define COOLTIME_SPECIAL_2 100
#define COOLTIME_SPECIAL_3 30

#define SPEED_BASIC 10
#define SPEED_SPECIAL_1 8
#define SPEED_SPECIAL_2 10
#define SPEED_SPECIAL_3 12

class Player : public GameObject
{
private:
	int _speed = PLAYER_SPEED;

	int _weaponMode = 0;

	int _maxBasic = MAX_BASIC;
	int _maxSpecial1 = MAX_SPECIAL_1;

	int _cooltimeBasic = COOLTIME_BASIC;
	int _cooltimeSpecial1 = COOLTIME_SPECIAL_1;
	
	Missile _basicBullets[MAX_BASIC];
	Missile _special1Bullets[MAX_SPECIAL_1];

public:
	Player();
	~Player();

	void setSpeed(int speed){ _speed = speed; }
	int getSpeed(){ return _speed;}

	void setMode(int);

	void printBullet(HDC);

	bool fire();

	bool fireBasic();
	bool fireSpecial1();
	bool fireSpecial2();
	bool fireSpecial3();

	void update();
};

