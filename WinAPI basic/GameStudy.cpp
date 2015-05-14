#include "stdafx.h"
#include "GameStudy.h"

//�ʱ�ȭ
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	_gamePad = makeRect(10, 10, WIN_SIZE_X - 10, WIN_SIZE_Y - 10);
	_player = makePoint(WIN_SIZE_X / 2, _gamePad.bottom - 50);

	for (int i = 0; i < _maxBullets; i++)
	{
		_bullets[i] = NULL;
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

	if ((_player.x > 0) && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player.x -= _speed;
	}

	if ((_player.x < WIN_SIZE_X) && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.x += _speed;
	}

	if ((_player.y > 0) && KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_player.y -= _speed;
	}

	if ((_player.y < WIN_SIZE_Y) && KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_player.y += _speed;
	}

	//�Ѿ� ��
	if (_coolTime <= 0)
	{
		if ((KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isStayKeyDown(VK_SPACE)) && _bullets[_maxBullets - 1] == NULL)
		{
			//_bullets.push_back(POINT{_player.x, _player.y - 20});
			for (int i = 0; i < _maxBullets; i++)
			{
				if (_bullets[i] == NULL)
				{
					_bullets[i] = new POINT{ _player.x, _player.y - 20 };
					break;
				}
			}
			_coolTime = BULLET_COOLTIME;
		}
	}
	else
	{
		//Ÿ�̸Ӱ� 100fps�̹Ƿ�
		_coolTime -= 10;
	}

	//�Ѿ� ����
	//vector<POINT>::iterator iter;
	/*
	for (auto iter = _bullets.begin(); iter != _bullets.end();)
	{
		iter->y -= _bulletSpeed;
		if (iter->y < 0) iter = _bullets.erase(iter);
		else iter++;
	}
	*/

	//�߰��� �Ѿ��� ��� �ڿ����� ������ ����� �ڸ� NULL�� ä��.
	for (int i = 0; i < _maxBullets; i++)
	{
		if (_bullets[i] == NULL) break;
		_bullets[i]->y -= _bulletSpeed;
		if (_bullets[i]->y < 0)
		{
			SAFE_DELETE(_bullets[i]);
			for (int j = i; j < _maxBullets - 1; j++)
			{
				_bullets[j] = _bullets[j + 1];
				_bullets[j + 1] = NULL;
			}
			i--;
		}
	}
}

//ȭ�����
void GameStudy::render(HDC hdc)
{
	/*
	for (auto iter = _bullets.begin(); iter != _bullets.end(); iter++)
	{
		drawRectangleCenter(hdc, *iter, 5, 15);
	}
	*/
	for (int i = 0; i < _maxBullets; i++)
	{
		if (_bullets[i] == NULL) break;
		drawRectangleCenter(hdc, *_bullets[i], 5, 15);
	}

	drawEllipse(hdc, makeRectCenter(_player, 20, 30));
}

/*
LRESULT GameStudy::mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_mousePoint = makeMousePoint(lParam);
		break;
	case WM_TIMER:

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
*/
