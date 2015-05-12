/**
Win API
@author	박진한(wakeup5, wlsgks5@naver.com)
@date	2015/05/08
@brief	윈도우 api 기본
*/
#include "stdafx.h"

HINSTANCE _hInstance; // 프로그램 인스턴스
HWND _hWnd; // 윈도우 핸들

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowPositionAndSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	_hInstance = hInstance;

	wndClass.cbClsExtra		= 0;									// 클래스 여분 메모리
	wndClass.cbWndExtra		= 0;									// 윈도우 여분 메모리
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	// 백그라운드
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// 커서 모양
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// 상위 창 아이콘 모양
	wndClass.hInstance		= hInstance;							// 윈도우 인스턴스
	wndClass.lpfnWndProc	= (WNDPROC)WndProc;						// (*중요)프로시저 함수(메세지 처리함수) - 키보드 입력등에 호출되는 함수
	wndClass.lpszClassName	= WIN_NAME;					// 클래스 명(화면 창 이름)
	wndClass.lpszMenuName	= NULL;									// 메뉴명
	wndClass.style			= CS_HREDRAW | CS_VREDRAW;				// 윈도우 창 상단오른쪽 버튼 스타일

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WIN_NAME,		// 윈도우 클래스 이름
		WIN_NAME,		// 윈도우 타이틀바의 이름
		WIN_STYLE,		// 윈도우 스타일
		WIN_START_X,	// 윈도우 화면 좌표 x(좌우) - 픽셀 단위
		WIN_START_Y,	// 윈도우 화면 좌표 y(상하) - 픽셀 단위
		WIN_SIZE_X,		// 윈도우 화면 크기 width(폭)
		WIN_SIZE_Y,		// 윈도우 화면 크기 height(높이)
		NULL,			// 부모 윈도우 인스턴스
		(HMENU)NULL,	// 메뉴 핸들
		hInstance,		// 인스턴스 윈도우 지정
		NULL			// mdi 클라이언트 윈도우 및 자식 윈도우를 생성하면 지정해 주고, 사용하지 않으면 NULL
		);

	setWindowPositionAndSize(WIN_START_X, WIN_START_Y, WIN_SIZE_X, WIN_SIZE_Y);

	ShowWindow(_hWnd, cmdShow);

	//게임용
	/*
	while (true)
	{
	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
	if (message.message == WM_QUIT)
	{
	break;
	}
	TranslateMessage(&message);
	DispatchMessage(&message);
	}
	//처리할 메세지가 없으면 렌더 호출
	//render();
	}
	*/

	//일반 윈도우 창
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnregisterClass(WIN_NAME, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static RECT r1;

	switch (iMessage)
	{
	case WM_CREATE:
	
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		r1 = makeRectCenter(250, 250, 200, 200);
		Rectangle(hdc, r1.left, r1.top, r1.right, r1.bottom);

		//색 칠하기
		//방법 1
		HBRUSH brush;

		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
	{

		hdc = GetDC(hWnd);

		int mx = LOWORD(lParam);
		int my = HIWORD(lParam);

		char p[128];

		if (checkInRect(makePoint(mx, my), r1))
		{
			wsprintf(p, "%4d, %4d", mx, my);
			TextOut(hdc, 10, 10, p, _tcslen(p));
		}
		else
		{
			InvalidateRect(hWnd, NULL, true);
		}

		ReleaseDC(hWnd, hdc);
	}
		break;
	case WM_DESTROY: //프로그램 종료시 발생.
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void setWindowPositionAndSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}