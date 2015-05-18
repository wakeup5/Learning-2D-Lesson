#include "stdafx.h"
#include "GameStudy.h"

//�ʱ�ȭ
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	int x, y;

	for (int i = 0; i < GAME_LENGTH; i++)
	{
		x = 10 + ((i % GAME_WIDTH) * 48);
		y = 10 + ((i / GAME_WIDTH) * 48);

		_rect[i] = RECT{ x, y, x + 40, y + 40 };
		_isClicks[i] = false;
	}

	_selectNum = RANDOM->getInt(GAME_LENGTH);

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

	if (!_gameover && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < GAME_LENGTH; i++)
		{
			if (!_isClicks[i] && PtInRect(&_rect[i], _mousePoint))
			{
				_isClicks[i] = true;
				if (i == _selectNum) _gameover = true;
			}
		}
	}

}

//ȭ�����
void GameStudy::render(HDC hdc)
{
	HBRUSH p = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH s = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH o = CreateSolidBrush(RGB(100, 0, 100));

	SelectObject(hdc, p);
	for (int i = 0; i < GAME_LENGTH; i++)
	{
		if (_isClicks[i])
		{
			if (_selectNum == i)
			{
				SelectObject(hdc, s);
			}
			else
			{
				SelectObject(hdc, o);
			}
		}
		else
		{
			SelectObject(hdc, p);
		}

		Rectangle(hdc, _rect[i].left, _rect[i].top, _rect[i].right, _rect[i].bottom);
	}

	if (_gameover)
	{
		TextOut(hdc, 10, 100, "���� �ɸ�", 9);
	}
}
