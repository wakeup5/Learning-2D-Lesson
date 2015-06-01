#include "stdafx.h"
#include "Rocket.h"


Rocket::Rocket()
{
}


Rocket::~Rocket()
{
}

HRESULT Rocket::initialize()
{
	GameNode::initialize();
	//getInfo()->setPosition(WIN_SIZE_X / 2, WIN_SIZE_Y - 100);
	//getInfo()->setSize(50, 50);

	getInfo()->initialize(WIN_SIZE_X / 2, WIN_SIZE_Y - 100, 50, 50, 0, 0);
	_image = IMAGEMANAGER->addImage("rocket", "resource/slug.bmp", 52, 64, TRUE, RGB(255, 0, 255));
	_boostImage = IMAGEMANAGER->addSpriteImage("rocket boost", "resource/boost.bmp", 200, 298, 5, 1, TRUE, RGB(255, 0, 255));
	return S_OK;
}
void Rocket::release()
{

}
void Rocket::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_object->setX(_object->getX() - 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_object->setX(_object->getX() + 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_object->setY(_object->getY() - 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_object->setY(_object->getY() + 3);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_missile.size() < 20)
		{
			Missile* missile = new Missile;
			missile->initialize();
			missile->getObject()->initialize(_object->getX(), _object->getY(), 5, 30, 90, 10);
			_missile.push_back(missile);
		}
	}

	for (auto missileIter = _missile.begin(); missileIter != _missile.end();)
	{
		(*missileIter)->update();
		if ((*missileIter)->getObject()->getY() < 0)
		{
			(*missileIter)->release();
			missileIter = _missile.erase(missileIter);
		}
		else
		{
			missileIter++;
		}
	}

	
	_boostImage->nextFrameX(2);
	

	_image->setCenter(getInfo()->getX(), getInfo()->getY());
	_boostImage->setCenter(getInfo()->getX(), getInfo()->getY() + 180);
	_object->move();
}
void Rocket::render()
{
	for (auto missileIter = _missile.begin(); missileIter != _missile.end(); missileIter++)
	{
		(*missileIter)->render();
	}

	_image->render(getMemDC());
	_boostImage->render(getMemDC());
}