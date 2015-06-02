#pragma once
#include "GameNode.h"

class Bullet : public GameNode
{
private:
	class BulletObject : public GameObject
	{
	public:
		Image* image;

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
public:
	Bullet();
	~Bullet();

	virtual HRESULT initialize(int max, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();
	virtual void fire(float startX, float startY, float angleR);
};

