#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

HRESULT Bullet::initialize(int max, float range)
{
	GameNode::initialize();

	_max = max;
	_range = range;

	return S_OK;
}
void Bullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		SAFE_RELEASE(_viBullet->image);
		_viBullet = _vBullet.erase(_viBullet);
	}

	_vBullet.clear();
}

void Bullet::update()
{
	GameNode::update();

	move();
}
void Bullet::render()
{
	draw();
}

void Bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->move();

		float x = _viBullet->getX();
		float y = _viBullet->getY();

		_viBullet->image->setCenter(x, y);

		//라이프 타임
		if (_range < myUtil::getDistanceByTwoPoint(_viBullet->startX, _viBullet->startY, x, y))
		{
			SAFE_RELEASE(_viBullet->image);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			_viBullet++;
		}
	}
}
void Bullet::draw()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->image->render(getMemDC());
	}
}
void Bullet::fire(float startX, float startY, float angleR)
{
	if (_vBullet.size() < _max)
	{
		Bullet::BulletObject bullet;
		bullet.image = new Image;
		bullet.image->initialize("resource/missile.bmp", 5, 30, TRUE, RGB(255, 0, 255));

		bullet.setAngleR(angleR);
		bullet.setSpeed(10.1f);

		bullet.setSize(bullet.image->getWidth(), bullet.image->getHeight());
		bullet.setPosition(startX, startY);
		bullet.startX = startX;
		bullet.startY = startY;

		_vBullet.push_back(bullet);

	}
}
