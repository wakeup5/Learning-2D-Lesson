#include "stdafx.h"
#include "GameStudy.h"

//�ʱ�ȭ
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	
	_ellipse = makeRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 100, 150);

	return S_OK;
}

//����
void GameStudy::release(void)
{
	GameNode::release();
}

//ȭ�鰻��
void GameStudy::update(void)
{
	GameNode::update();

}

//ȭ�����
void GameStudy::render(HDC hdc)
{
	drawEllipse(hdc, _ellipse);
	if (checkInEllipse(_mousePoint, _ellipse))
	{
		drawRectangleCenter(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 10, 10);
	}
	else
	{
		//drawRectangleCenter(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 10, 10);
	}
}
