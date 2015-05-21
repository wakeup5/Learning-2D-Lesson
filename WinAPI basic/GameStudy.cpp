#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();	

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
  
}





//숙제

//아이스 하키
//공은 마찰력
//밀면 공이 움직임
//서로 본진 침범 못함

//숙제 2
//지렁이는 원으로 구성. 크기가 다 다름 같게해도됨 10개
//일직선으로 가고 있다 랜덤
//처음 원이 방향으로 가고 뒤에 작은 원들이 따라붙음.
//벽에 부딛히면 반사됨
//대가리를 조종하고 있다.
//죄우키를 누르면 방향 조종 가능.
