/**
Win API
@author	������(wakeup5, wlsgks5@naver.com)
@date	2015/05/08
@brief	������ api �⺻
*/
#include "stdafx.h"

HINSTANCE _hInstance; // ���α׷� �ν��Ͻ�
HWND _hWnd; // ������ �ڵ�

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowPositionAndSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	_hInstance = hInstance;

	wndClass.cbClsExtra		= 0;									// Ŭ���� ���� �޸�
	wndClass.cbWndExtra		= 0;									// ������ ���� �޸�
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	// ��׶���
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Ŀ�� ���
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// ���� â ������ ���
	wndClass.hInstance		= hInstance;							// ������ �ν��Ͻ�
	wndClass.lpfnWndProc	= (WNDPROC)WndProc;						// (*�߿�)���ν��� �Լ�(�޼��� ó���Լ�) - Ű���� �Էµ ȣ��Ǵ� �Լ�
	wndClass.lpszClassName	= WIN_NAME;					// Ŭ���� ��(ȭ�� â �̸�)
	wndClass.lpszMenuName	= NULL;									// �޴���
	wndClass.style			= CS_HREDRAW | CS_VREDRAW;				// ������ â ��ܿ����� ��ư ��Ÿ��

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WIN_NAME,		// ������ Ŭ���� �̸�
		WIN_NAME,		// ������ Ÿ��Ʋ���� �̸�
		WIN_STYLE,		// ������ ��Ÿ��
		WIN_START_X,	// ������ ȭ�� ��ǥ x(�¿�) - �ȼ� ����
		WIN_START_Y,	// ������ ȭ�� ��ǥ y(����) - �ȼ� ����
		WIN_SIZE_X,		// ������ ȭ�� ũ�� width(��)
		WIN_SIZE_Y,		// ������ ȭ�� ũ�� height(����)
		NULL,			// �θ� ������ �ν��Ͻ�
		(HMENU)NULL,	// �޴� �ڵ�
		hInstance,		// �ν��Ͻ� ������ ����
		NULL			// mdi Ŭ���̾�Ʈ ������ �� �ڽ� �����츦 �����ϸ� ������ �ְ�, ������� ������ NULL
		);

	setWindowPositionAndSize(WIN_START_X, WIN_START_Y, WIN_SIZE_X, WIN_SIZE_Y);

	ShowWindow(_hWnd, cmdShow);

	//���ӿ�
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
	//ó���� �޼����� ������ ���� ȣ��
	//render();
	}
	*/

	//�Ϲ� ������ â
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

		//�� ĥ�ϱ�
		//��� 1
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
	case WM_DESTROY: //���α׷� ����� �߻�.
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