#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	_mapImage = new Image();
	_mapImage->initialize("map.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_background = new Image;
	_background->initialize("resource/11.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	gameInit();

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	_mapImage->release();
	_background->release();

	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	_mapImage->render(backDC, 0, 0);
	_background->render(backDC);

	this->getBackBuffer()->render(hdc, 0, 0);
}

//게임 초기화
void GameStudy::gameInit()
{

}
