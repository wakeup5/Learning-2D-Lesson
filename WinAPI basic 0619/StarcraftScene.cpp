#include "stdafx.h"
#include "StarcraftScene.h"

extern Unit* _selectUnit;

StarcraftScene::StarcraftScene()
{
}


StarcraftScene::~StarcraftScene()
{
}

HRESULT StarcraftScene::initialize(void)
{
	_background = IMAGEMANAGER->addImage("space", "resource/starcraft/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_unit = _selectUnit;

	_camera = IMAGEMANAGER->addImage("camera", WIN_SIZE_X, WIN_SIZE_Y);
	/*
	_bullet = new Bullets();
	_bullet->initialize(NULL, 500, 50);
	*/

	return S_OK;
}
void StarcraftScene::release(void)
{
	SAFE_RELEASE(_unit);
}
void StarcraftScene::update(void)
{
	//_marine->setAngleR(myUtil::getGradeRadian(_marine->getX(), _marine->getY(), _mousePt.x, _mousePt.y));

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _unit->setAngleD(_unit->getAngleD() + 5);
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _unit->setAngleD(_unit->getAngleD() - 5);
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _unit->setAccel(_unit->getViewAccel());
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _unit->setAccel(-_unit->getViewAccel());
	else _unit->setAccel(-100);

	if (_unit->getSpeed() < 0)
	{
		_unit->setAccel(0);
		_unit->setSpeed(0);
	}
	if (_unit->getSpeed() > _unit->getMaxSpeed())
	{
		_unit->setAccel(0);
		_unit->setSpeed(_unit->getMaxSpeed());
	}

	_unit->update();
	_camera->setCenter(-_unit->getX() + _camera->getWidth(), -_unit->getY() + _camera->getHeight());

	//printf("x-%f, y-%f, speed-%f, accel-%f \n", _unit->getX(), _unit->getY(), _unit->getSpeed(), _unit->getAccel());

	if (_unit->getRect().left < 10) _unit->setX(10 + _unit->getWidth() / 2);
	if (_unit->getRect().right > _background->getWidth() - 10) _unit->setX(_background->getWidth() - 10 - _unit->getWidth() / 2);
	if (_unit->getRect().top < 10) _unit->setY(10 + _unit->getHeight() / 2);
	if (_unit->getRect().bottom > _background->getHeight() - 10) _unit->setY(_background->getHeight() - 10 - _unit->getHeight() / 2);

	/*
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SpriteImage* image = IMAGEMANAGER->addImage("overload", "resource/starcraft/overlord.bmp", 1344, 336, TRUE, RGB(0, 255, 0))->createSprite(16, 4);
		_bullet->fire(Bullets::createBullet(image, _marine->getX(), _marine->getY(), _marine->getAngleR(), 1));
	}
	*/
	
	//_bullet->update();
}
void StarcraftScene::render(void)
{
	_background->render(_camera->getMemDC());
	_unit->render(_camera->getMemDC());
	_camera->render(getMemDC());
	//_bullet->render();
}