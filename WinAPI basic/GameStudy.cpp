#include "stdafx.h"
#include "GameStudy.h"


GameStudy::GameStudy()
{
}


GameStudy::~GameStudy()
{
}

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	_rc = makeRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 100, 100);

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

	_rc = makeRectCenter(_mousePoint, 100, 100);
}

//화면출력
void GameStudy::render(HDC hdc)
{
	drawEllipse(hdc, _rc);
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
