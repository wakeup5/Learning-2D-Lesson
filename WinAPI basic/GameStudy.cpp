#include "stdafx.h"
#include "GameStudy.h"

//�ʱ�ȭ
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	_cannon.angle = 90;
	_cannon.length = 70;
	_cannon.radius = 50;
	_cannon.center.x = WIN_SIZE_X / 2;
	_cannon.center.y = WIN_SIZE_Y;

	for (int i = 0; i < MAX_MISSILE; i++)
	{
		_missiles[i].angleRadian = M_PI / 2;
		_missiles[i].speed = MISSILE_SPEED;
		_missiles[i].radius = MISSILE_SIZE;
		_missiles[i].isFire = false;
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

	//���� ����
	if (_cannon.angle < 170 && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cannon.angle += 1;
	}

	if (_cannon.angle > 10 && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cannon.angle -= 1;
	}

	_cannon.angleRadian = _cannon.angle * M_PI / 180;
	_cannon.cannonEnd.x = _cannon.center.x + _cannon.length * cos(_cannon.angleRadian);
	_cannon.cannonEnd.y = _cannon.center.y - _cannon.length * sin(_cannon.angleRadian);

	//�̻��� �߻�
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		for (int i = 0; i < MAX_MISSILE; i++)
		{
			if (!_missiles[i].isFire)
			{
				_missiles[i].position = _cannon.cannonEnd;
				_missiles[i].angle = _cannon.angle;
				_missiles[i].isFire = true;
				break;
			}
		}
	}

	//�̻��� �浹ó��
	for (int i = 0; i < MAX_MISSILE; i++)
	{
		if (_missiles[i].position.x < 0 && _missiles[i].angle > 90 && _missiles[i].angle < 270)
		{
			//_missiles[i].isFire = false; //1������
			_missiles[i].angle = -_missiles[i].angle + (_missiles[i].angle <= 180 ? -180 : 540);
		}

		if (_missiles[i].position.x > WIN_SIZE_X && !(_missiles[i].angle > 90 && _missiles[i].angle < 270))
		{
			//_missiles[i].isFire = false; //1������
			_missiles[i].angle = -_missiles[i].angle + (_missiles[i].angle <= 180 ? 180 : -540);
		}

		if (_missiles[i].position.y < 0)
		{
			//_missiles[i].isFire = false; //1������
			_missiles[i].angle = 360 - _missiles[i].angle;
		}

		if (_missiles[i].position.y > WIN_SIZE_Y)
		{
			//_missiles[i].isFire = false; //1������
			_missiles[i].angle = 360 - _missiles[i].angle;
		}


		while (_missiles[i].angle <= 0)
		{
			_missiles[i].angle += 360;
		}
		while (_missiles[i].angle >= 360)
		{
			_missiles[i].angle -= 360;
		}
	}

	//�̻��� ������
	for (int i = 0; i < MAX_MISSILE; i++)
	{
		if (_missiles[i].isFire)
		{
			_missiles[i].angleRadian = _missiles[i].angle * M_PI / 180;
			_missiles[i].position.x += _missiles[i].speed * cos(_missiles[i].angleRadian);
			_missiles[i].position.y -= _missiles[i].speed * sin(_missiles[i].angleRadian);
		}
	}

}

//ȭ�����
void GameStudy::render(HDC hdc)
{
	drawLine(hdc, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);
	drawEllipseCenter(hdc, _cannon.center.x, _cannon.center.y, _cannon.radius * 2, _cannon.radius * 2);

	for (int i = 0; i < MAX_MISSILE; i++)
	{
		if (_missiles[i].isFire)
		{
			drawEllipseCenter(hdc, _missiles[i].position, _missiles[i].radius, _missiles[i].radius);
		}
	}

	TCHAR a[128];
	sprintf_s(a, "degree %.1f, radian %.1f", _cannon.angle, _cannon.angleRadian);
	TextOut(hdc, 10, 10, a, _tcslen(a));

	sprintf_s(a, "m1 degree %.1f, radian %.1f", _missiles[0].angle, _missiles[0].angleRadian);
	TextOut(hdc, 10, 40, a, _tcslen(a));
}

//05-19 ����

//ù��° ������ ���� �Ѿ� ���, ����, ���� ǥ��
//�����迭��.

//�ι�° �Ѿ��� ���� ���� ƨ�� ������ �ٲ۴�.

//����°