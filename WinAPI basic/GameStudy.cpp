#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	
	//_ellipse = makeRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 100, 150);
	//_ellipse = makePointRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 100, 150);
	//_rectangle = makePointRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 20, 20);

	_player.setPosition(makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y - 50));
	_player.setSize(20, 30);
	_player.setSpeed(5);

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	//_rectangle.point = _mousePoint;
	//_rectangle.rect = makeRectCenter(_mousePoint, 200, 200);

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player.getSize().bottom < WIN_SIZE_Y)
	{
		_player.moveY(_player.getSpeed());
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player.getSize().top > 0)
	{
		_player.moveY(-_player.getSpeed());
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player.getSize().left > 0)
	{
		_player.moveX(-_player.getSpeed());
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player.getSize().right < WIN_SIZE_X)
	{
		_player.moveX(_player.getSpeed());
	}

	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_player.fire();
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_player.setMode(0);
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_player.setMode(1);
	}

	_player.update();
}

//화면출력
void GameStudy::render(HDC hdc)
{
	//drawEllipse(hdc, _ellipse.rect);
	//drawRectangle(hdc, _rectangle.rect);

	/*
	if (isCollisionEllipse(_rectangle.rect, _ellipse.rect))
	{
		drawRectangleCenter(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 30, 30);
	}
	if (isCollisionEllipse(_mousePoint, _ellipse.rect))
	{
		drawRectangleCenter(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 10, 10);
	}
	*/

	drawEllipse(hdc, _player.getSize());
	_player.printBullet(hdc);
}
