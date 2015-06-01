#include "stdafx.h"
#include "Missile.h"


Missile::Missile()
{
}


Missile::~Missile()
{
}


HRESULT Missile::initialize()
{
	GameNode::initialize();

	//_object->setSize(5, 30);
	_image = IMAGEMANAGER->addImage("bullet", "resource/missile.bmp", 5, 30, TRUE, RGB(255, 255, 255));

	return S_OK;
}
void Missile::release(void)
{

}
void Missile::update(void)
{
	//_object->getUpdateRect();
	//_image->setCenter(getInfo()->getX(), getInfo()->getY());
	getInfo()->move();
}
void Missile::render()
{
	_image->render(getMemDC(), getInfo()->getRect().left, getInfo()->getRect().top);
}