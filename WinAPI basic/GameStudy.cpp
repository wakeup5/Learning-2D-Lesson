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

	static int count = 0;
	count++;
	if (count % 5 == 0)
	{
		count = 0;
		if (_image1->getFrameX() >= _image1->getMaxFrameX())
		{
			_image1->setFrameX(0);
		}
		else
		{
			_image1->setFrameX(_image1->getFrameX() + 1);
		}
	}
}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	_mapImage->render(backDC, 0, 0);
	_background->render(backDC);

	_image1->frameRender(backDC);
	//_image1->render(backDC);

	this->getBackBuffer()->render(hdc, 0, 0);
}

//게임 초기화
void GameStudy::gameInit()
{
	_image1 = new Image;
	_image1->initialize("resource/c1.bmp", WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 198, 256, 3, 4, TRUE, RGB(255, 0, 255));
}
