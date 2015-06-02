#pragma once
#include "GameNode.h"

class Bullet : public GameNode
{
private:
	class BulletObject : public GameObject
	{
	public:
		SpriteImage* image;

		float startX;
		float startY;

		bool isFire;

		BulletObject(){}
		~BulletObject(){}
	};

	std::vector<BulletObject> _vBullet;
	std::vector<BulletObject>::iterator _viBullet;

	int _max;
	float _range;
	Image* _image;
	int _frameCol;
	int _frameRow;
public:
	Bullet();
	~Bullet();

	virtual HRESULT initialize(int max, float range, const char* fileName, int frameCol = 1, int frameRow = 1);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();
	virtual void fire(float startX, float startY, float angleR, float speed);
};

