﻿#include "stdafx.h"
#include "GameStudy.h"
#include "AStarScene.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);

	imageLoad();

	SCENEMANAGER->addScene("AStar", new AStarScene());
	SCENEMANAGER->changeScene("AStar");

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

	EFFECTMANAGER->update();
	SCENEMANAGER->update();
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("backMap", getMemDC());
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	GameNode::render();
}

void GameStudy::imageLoad()
{
	IMAGEMANAGER->addImage("backMap", "backMap.bmp", WIN_SIZE_X, WIN_SIZE_Y);
}