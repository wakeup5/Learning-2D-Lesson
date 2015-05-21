#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();	

    float randomAngleD = RANDOM->getInt(360);
    float randomX = RANDOM->getIntTo(100, WIN_SIZE_X - 100);
    float randomY = RANDOM->getIntTo(100, WIN_SIZE_Y - 100);

    _worm[0].angleD = randomAngleD;
    _worm[0].angleR = randomAngleD * M_PI / 180;
    _worm[0].speed = 10;
    _worm[0].x = randomX;
    _worm[0].y = randomY;
    _worm[0].size = 30;

    for (int i = 1; i < WORM_LENGTH; i++)
    {
        _worm[i].angleD = randomAngleD;
        _worm[i].angleR = randomAngleD * M_PI / 180;
        _worm[i].speed = 10;
        _worm[i].x = _worm[i - 1].x - _worm[i - 1].speed * cos(_worm[i - 1].angleR);
        _worm[i].y = _worm[i - 1].y + _worm[i - 1].speed * sin(_worm[i - 1].angleR);
        _worm[i].size = 30 - (static_cast<float>(i) / WORM_LENGTH * 10);
    }

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
    
    //_worm[0].angleR = _worm[0].angleD * M_PI / 180;

    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _worm[0].angleD += 3;
    }
    
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _worm[0].angleD -= 3;
    }

    //단순히 마디가 이전 마디의 위치로 옮겨짐.
    
    for (int i = WORM_LENGTH - 1; i > 0; i--)
    {
        _worm[i].x = _worm[i - 1].x;
        _worm[i].y = _worm[i - 1].y;
    }
    
    
    //
    /*
    for (int i = 1; i < WORM_LENGTH; i++)
    {
        _worm[i].prevD = _worm[i].angleD;
        _worm[i].prevR = _worm[i].angleR;
        _worm[i].angleD = _worm[i].prevD;
        _worm[i].angleR = _worm[i].prevD * M_PI / 180;
        _worm[i].speed = 10;
        _worm[i].x = _worm[i].x + _worm[i].speed * sin(_worm[i].angleR);
        _worm[i].y = _worm[i].y - _worm[i].speed * cos(_worm[i].angleR);
    }
    */
    
    

    if (_worm[0].x < 0)
    {
        _worm[0].angleD = 180 - _worm[0].angleD;
        _worm[0].x = 5;
    }

    if (_worm[0].x > WIN_SIZE_X)
    {
        _worm[0].angleD = 180 - _worm[0].angleD;
        _worm[0].x = WIN_SIZE_X - 5;
    }

    if (_worm[0].y < 0)
    {
        _worm[0].angleD = 360 - _worm[0].angleD;
        _worm[0].y = 5;
    }

    if (_worm[0].y > WIN_SIZE_Y)
    {
        _worm[0].angleD = 360 - _worm[0].angleD;
        _worm[0].y = WIN_SIZE_Y - 5;
    }

    _worm[0].angleR = _worm[0].angleD * M_PI / 180;
    _worm[0].x = _worm[0].x + _worm[0].speed * cos(_worm[0].angleR);
    _worm[0].y = _worm[0].y - _worm[0].speed * sin(_worm[0].angleR);

}

//화면출력
void GameStudy::render(HDC hdc)
{
    for (int i = 0; i < WORM_LENGTH; i++)
    {
        drawEllipseCenter(hdc, _worm[i].x, _worm[i].y, _worm[i].size, _worm[i].size);
    }
   
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
