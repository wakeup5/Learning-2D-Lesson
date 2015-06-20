#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);

	imageLoad();

	_image = IMAGEMANAGER->findImage("e")->createAnimate(4, 3);
	_image->setPlayFrame(8, 100, true, true);
	_image->setFPS(8);
	_image->start();
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
	_image->frameUpdate(TIMEMANAGER->getElapsedTime());
	EFFECTMANAGER->update();
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("backMap", getMemDC());
	_image->render(getMemDC(), 100, 100);
	GameNode::render();
}

void GameStudy::imageLoad()
{
	IMAGEMANAGER->addImage("backMap", "resource/backMap.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("queen", "resource/queen.bmp", 160, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("e", "resource/enemy_move.bmp", 160, 150, true, RGB(255, 0, 255));
}