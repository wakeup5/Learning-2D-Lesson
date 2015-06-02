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

	GameObject::initialize(WIN_SIZE_X / 2, WIN_SIZE_Y - 100, 50, 50, 0, 0);
	
	_image = IMAGEMANAGER->addImage("rocket", "resource/slug.bmp", 52, 64, TRUE, RGB(255, 0, 255));
	_boostImage = IMAGEMANAGER->addImage("rocket boost", "resource/boost.bmp", 200, 298, TRUE, RGB(255, 0, 255))->getSpriteImage(5, 1);

	_missile = new Missile;
	_missile->initialize(100, 400);

	_bullet = new Bullet;
	_bullet->initialize(200, 200, "resource/missile.bmp", 1, 1);

	return S_OK;
}
void Rocket::release()
{
	_missile->release();
	_bullet->release();
}
void Rocket::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && getRect().left > 0)
	{
		setX(getX() - 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && getRect().right < WIN_SIZE_X)
	{
		setX(getX() + 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && getRect().top > 0)
	{
		setY(getY() - 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && getRect().bottom < WIN_SIZE_Y)
	{
		setY(getY() + 3);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(getX(), getY() - 50);
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_bullet->fire(getX(), getY() - 50, M_PI / 2, 10);
		_bullet->fire(getX(), getY() - 50, M_PI * 1 / 4, 10);
		_bullet->fire(getX(), getY() - 50, M_PI * 1.5 / 4, 10);
		_bullet->fire(getX(), getY() - 50, M_PI * 2.5 / 4, 10);
		_bullet->fire(getX(), getY() - 50, M_PI * 3 / 4, 10);
	}

	_image->setCenter(getX(), getY());

	_boostImage->nextFrameX(20);
	_boostImage->setCenter(getX(), getY() + 185);

	_missile->update();
	_bullet->update();
}
void Rocket::render()
{
	_image->render(getMemDC());
	_boostImage->render(getMemDC());

	_missile->render();
	_bullet->render();
}