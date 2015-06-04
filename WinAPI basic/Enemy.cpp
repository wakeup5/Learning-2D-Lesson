#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}
HRESULT Enemy::initialize(SpriteImage* image, float frameTime)
{
	GameNode::initialize();
	GameObject::initialize(0, 0);

	_image = image;
	_frameTime = frameTime;

	return S_OK;
}
void Enemy::release(void)
{

}
void Enemy::update(void)
{
	_image->nextFrame(_frameTime);
	_image->setCenter(getX(), getY());

	move();
}
void Enemy::render(void)
{
	_image->render(getMemDC());
}