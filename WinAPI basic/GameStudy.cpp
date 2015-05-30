#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	_mapImage = IMAGEMANAGER->addImage("mapImage", "map.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_background = IMAGEMANAGER->addImage("background", "resource/11.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	gameInit();

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

}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = getBackBuffer()->getMemDC();
	_mapImage->render(backDC);
	_background->render(backDC);

	getBackBuffer()->render(hdc);
}

//게임 초기화
void GameStudy::gameInit()
{

}

//숙제
//1. 알카노이드(벽돌깨기)
//벽돌 배치를 여러 모양으로
//배치 사각형으로
//1방맞으면, 2방, 3방 블럭이 있다.
//플레이어가 있다
//시작하기전에 공이 붙어있다.
//안움직일때 마우스를 누르면 앞으로 나감
//블럭을 깨면 아이템이 천천히 내려옴
//아이템을 먹으면 범위가 커짐, 공이 하나 더 늘어남, 일정시간 총알이 나감(데미지가 공과 같음)

//2. 플래시게임중에 마이더스 구현
//첫번째 스테이지는 빼고 나머지 스테이지 구현

//3. 오락실게임
//오리지널 너구리
//스테이지 하나만 구현
//압정있으면 점프해서 넘어감
//이미지는 자유롭게하나 가능하면 똑같이
