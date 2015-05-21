#include "stdafx.h"
#include "GameStudy.h"

//�ʱ�ȭ
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

//����
void GameStudy::release(void)
{
	GameNode::release();
}

//ȭ�鰻��
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

    //�ܼ��� ���� ���� ������ ��ġ�� �Ű���.
    
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

//ȭ�����
void GameStudy::render(HDC hdc)
{
    for (int i = 0; i < WORM_LENGTH; i++)
    {
        drawEllipseCenter(hdc, _worm[i].x, _worm[i].y, _worm[i].size, _worm[i].size);
    }
   
}





//����

//���̽� ��Ű
//���� ������
//�и� ���� ������
//���� ���� ħ�� ����

//���� 2
//�����̴� ������ ����. ũ�Ⱑ �� �ٸ� �����ص��� 10��
//���������� ���� �ִ� ����
//ó�� ���� �������� ���� �ڿ� ���� ������ �������.
//���� �ε����� �ݻ��
//�밡���� �����ϰ� �ִ�.
//�˿�Ű�� ������ ���� ���� ����.
