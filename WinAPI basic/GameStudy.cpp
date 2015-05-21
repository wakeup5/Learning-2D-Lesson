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


