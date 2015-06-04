#include "stdafx.h"
#include "Screen1.h"


Screen1::Screen1()
{
}


Screen1::~Screen1()
{
}

HRESULT Screen1::initialize(void)
{
	GameNode::initialize();

	_screen1WND[0] = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, WIN_SIZE_X / 2 - 75, WIN_SIZE_Y / 2 - 10, 150, 20, _hWnd, HMENU(1), _hInstance, NULL);
	_screen1WND[1] = CreateWindow("button", "확인", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, WIN_SIZE_X / 2 + 80, WIN_SIZE_Y / 2 - 10, 30, 20, _hWnd, HMENU(0x1002), _hInstance, NULL);

	return S_OK;
}

void Screen1::release(void)
{

}
void Screen1::update(void)
{
	GameNode::update();
}
void Screen1::render(void)
{
	TextOut(getMemDC(), 10, 10, _str, strlen(_str));
}

void Screen1::controlMessage(int message)
{
	DEBUGF("%d", message);
	if (message == 0x1002)
	{
		DEBUG("aa");
		char s[128];
		GetWindowText(_screen1WND[0], s, strlen(s));
		int number = atoi(s);
		if (number < 1 && number > 10)
		{
			memcpy(_str, "2 ~ 10 사이의 숫자를 입력 해라", sizeof(_str));
		}
	}
}