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

    if (_cannon.getPosition().x > 0 && KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _cannon.moveX(-2);
    }

    if (_cannon.getPosition().x < WIN_SIZE_X && KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _cannon.moveX(2);
    }

    if (_cannon.getAngleD() < 100 && KEYMANAGER->isStayKeyDown(VK_UP))
    {
        _cannon.setAngleD(_cannon.getAngleD() + 2);
    }

    if (_cannon.getAngleD() > 10 && KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        _cannon.setAngleD(_cannon.getAngleD() - 2);
    }

    if (_power < MAX_POWER && KEYMANAGER->isStayKeyDown(VK_SPACE))
    {
        _power += GRAVITY_ACCEL;
    }

    if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
    {
        for (int i = 0; i < MAX_BULLET; i++)
        {
            if (!_bullet[i].isFire)
            {
                _bullet[i].isFire = true;
                _bullet[i].setSpeed(_power);
                _bullet[i].setAngleD(_cannon.getAngleD());
                _bullet[i].setPosition(_cannon.getEndPoint());

                _bulletEnd[i] = _bullet[i].getPosition().x + (_bullet[i].getPosition().y + (-_bullet[i].getSpeedY() / GRAVITY_ACCEL * 2)) * _bullet[i].getSpeedX();
                break;
            }
        }
        _power = 0;
    }

    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (_bullet[i].isFire)
        {
            _bullet[i].moveGravity();
        }

        if (_bullet[i].getPosition().y > WIN_SIZE_Y)
        {
            _bullet[i].isFire = false;
        }
    }

    if (KEYMANAGER->isOnceKeyDown('1'))
    {
        for (int i = 0; i < MAX_BULLET; i++)
        {
            if (_bullet[i].isFire)
            {
                _bullet[i].isFire = false;
            }
        }
    }
}

//화면출력
void GameStudy::render(HDC hdc)
{
    drawLine(hdc, _cannon.getPosition(), _cannon.getEndPoint());
    drawEllipse(hdc, _cannon.getSize());

    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (_bullet[i].isFire)
        {
            drawEllipseCenter(hdc, _bullet[i].getPosition(), 10, 10);
        }
    }

    Rectangle(hdc, 10, 10, 10 + (_power / MAX_POWER) * (WIN_SIZE_X - 20), 20);

    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (_bullet[i].isFire)
        {
            drawLine(hdc, _bulletEnd[i], 0, _bulletEnd[i], WIN_SIZE_Y);
        }
    }

    TCHAR a[128];
    sprintf_s(a, "%f", _bulletEnd[0]);
    TextOut(hdc, 10, 50, a, _tcslen(a));
    
}


