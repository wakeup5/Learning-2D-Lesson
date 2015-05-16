#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	
	//_ellipse = makeRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 100, 150);
	_ellipse = makePointRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 100, 150);
	_rectangle = makePointRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 20, 20);

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

	_rectangle.point = _mousePoint;

}

//화면출력
void GameStudy::render(HDC hdc)
{
	drawEllipse(hdc, _ellipse.rect);
	if (checkInEllipse(_mousePoint, _ellipse.rect))
	{
		drawRectangleCenter(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 10, 10);
	}
	else
	{
		//drawRectangleCenter(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 10, 10);
	}
}
