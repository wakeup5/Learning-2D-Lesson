#include "stdafx.h"
#include "Missile.h"


Missile::Missile()
{
}


Missile::~Missile()
{
}


HRESULT Missile::initialize(int max, float range)
{
	GameNode::initialize();

	_max = max;
	_range = range;

	//정적으로 생성
	for (int i = 0; i < _max; i++)
	{
		Missile::MissileObject missile;
		missile.image = new SpriteImage;
		missile.image->initialize("resource/missile2.bmp", 390, 61, 13, 1, TRUE, RGB(255, 0, 255));
		missile.boostImage = new SpriteImage;
		missile.boostImage->initialize("resource/missile boost.bmp", 84, 34, 4, 1, TRUE, RGB(255, 0, 255));

		missile.setAngleD(90);
		missile.setSpeed(5.3f);

		missile.setSize(missile.image->getFrameWidth(), missile.image->getFrameHeight());
		missile.isFire = false;

		_missileVector.push_back(missile);
	}

	return S_OK;
}
void Missile::release()
{
	for (_missileVectorIter = _missileVector.begin(); _missileVectorIter != _missileVector.end();)
	{
		SAFE_RELEASE(_missileVectorIter->image);
		SAFE_RELEASE(_missileVectorIter->boostImage);
		_missileVectorIter = _missileVector.erase(_missileVectorIter);
	}

	_missileVector.clear();
}
void Missile::update()
{
	GameNode::update();

	move();
}
void Missile::render()
{
	draw();
}

void Missile::move()
{
	for (_missileVectorIter = _missileVector.begin(); _missileVectorIter != _missileVector.end(); _missileVectorIter++)
	{
		if (!_missileVectorIter->isFire) continue;

		_missileVectorIter->move();

		_missileVectorIter->image->nextFrameX(1);
		_missileVectorIter->boostImage->nextFrameX(3);

		float x = _missileVectorIter->getX();
		float y = _missileVectorIter->getY();

		_missileVectorIter->image->setCenter(x, y);
		_missileVectorIter->boostImage->setCenter(x, y + 50);

		//라이프 타임
		if (_range < myUtil::getDistanceByTwoPoint(_missileVectorIter->startX, _missileVectorIter->startY, x, y))
		{
			_missileVectorIter->isFire = false;
		}
	}
}
void Missile::draw()
{
	for (_missileVectorIter = _missileVector.begin(); _missileVectorIter != _missileVector.end(); _missileVectorIter++)
	{
		if (!_missileVectorIter->isFire) continue;
		
		_missileVectorIter->image->render(getMemDC());
		_missileVectorIter->boostImage->render(getMemDC());
	}
}

void Missile::fire(float startX, float startY)
{
	DEBUG("sss");
	for (_missileVectorIter = _missileVector.begin(); _missileVectorIter != _missileVector.end(); _missileVectorIter++)
	{
		if (_missileVectorIter->isFire) continue;

		_missileVectorIter->setPosition(startX, startY);
		_missileVectorIter->startX = startX;
		_missileVectorIter->startY = startY;
		_missileVectorIter->isFire = true;

		break;
	}
}