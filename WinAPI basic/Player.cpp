#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

HRESULT Player::initialize(void)
{
	GameObject::initialize(WIN_SIZE_X / 2, WIN_SIZE_Y - 100, 30, 30, 90, 0);
	_image = IMAGEMANAGER->addImage("player", "resource/slug.bmp", 52, 64, TRUE, RGB(255, 0, 255));
	_boostImage = IMAGEMANAGER->addSpriteImage("player boost", "resource/boost.bmp", 200, 298, 5, 1, TRUE, RGB(255, 0, 255));

	return S_OK;
}
void Player::release(void)
{
	
}
void Player::update(void)
{
	_image->setCenter(getX(), getY());
	_boostImage->setCenter(getX(), getY() + 180);
	_boostImage->nextFrame(50);
}
void Player::render()
{
	_image->render(getMemDC());
	_boostImage->render(getMemDC(), 100);
}