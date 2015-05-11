/**========================================
 * Win API
 * @author	������(wakeup5, wlsgks5@naver.com)
 * @date	2015/05/11
 * @brief	�ܼ� ������Ʈ�� ���� api ������ â�� ����.
 * ======================================== */
#include "stdafx.h"

/* ========================================
 *  ## �������� ##
 * ======================================== */
HINSTANCE _hInstance; // ���α׷� �ν��Ͻ�
HWND _hWnd; // ������ �ڵ�

/* ========================================
 *  ## �Լ� ���� ##
 * ======================================== */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowPositionAndSize(int x, int y, int width, int height);

/* ========================================
 *  ## ���� �Լ� ## - �ܼ� ���� �Լ�ó�� api�� ���� �Լ�
 * ======================================== */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	//_hInstance : �޼��� ó���Լ� ����.
	//�޼����� �߻��ϸ� �����Լ��� ȣ���� �޼����� ó���Ѵ�.
	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;									// Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;									// ������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			// Ŀ�� ���
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// ���� â ������ ���
	wndClass.hInstance = hInstance;							// ������ �ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						// (*�߿�)���ν��� �Լ�(�޼��� ó���Լ�) - Ű���� �Էµ ȣ��Ǵ� �Լ�
	wndClass.lpszClassName = WIN_NAME;					// Ŭ���� ��(ȭ�� â �̸�)
	wndClass.lpszMenuName = NULL;									// �޴���
	wndClass.style = CS_HREDRAW | CS_VREDRAW;				// ������ â ��ܿ����� ��ư ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ ����
	_hWnd = CreateWindow(
		WIN_NAME,		// ������ Ŭ���� �̸�
		WIN_NAME,		// ������ Ÿ��Ʋ���� �̸�
		WIN_STYLE,	// ������ ��Ÿ��
		WIN_START_X,			// ������ ȭ�� ��ǥ x(�¿�) - �ȼ� ����
		WIN_START_Y,			// ������ ȭ�� ��ǥ y(����) - �ȼ� ����
		WIN_SIZE_X,			// ������ ȭ�� ũ�� width(��)
		WIN_SIZE_Y,			// ������ ȭ�� ũ�� height(����)
		NULL,					// �θ� ������ �ν��Ͻ�
		(HMENU)NULL,			// �޴� �ڵ�
		hInstance,				// �ν��Ͻ� ������ ����
		NULL					// mdi Ŭ���̾�Ʈ ������ �� �ڽ� �����츦 �����ϸ� ������ �ְ�, ������� ������ NULL
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

	//GetMessage : �޼��� ť(FIFO)�� �Էµ� �޼����� �о �޼��� ����ü(���� MSG message)�� �����Ѵ�.
	//TranslateMessage : Ű���� �Է¿� ���� �޼��� ó��
	//DispatchMessage : ������ ���ν����� ���޵� �޼����� ���� ������� �������ش�. ������Ʈ? ���ν��� �Լ� ȣ�� �� ó���� ������ ȭ�鿡 �������ش�.


	//�Ϲ� ������ â
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//��ϵ� ������ Ŭ���� ����
	UnregisterClass(WIN_NAME, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_CREATE: //Ŭ������ �����ڿ� ���� �̺�Ʈ. ó�� ���α׷��� ���� �Ҷ� �� �ѹ� �߻�.

		break;
	case WM_PAINT: 
		// 1.�����츦 �ٽ� �׷��� �Ҷ� �߻�.
		// 2.������ ũ�⸦ �����Ҷ�
		// 3.�ٸ� �����쿡 �������ٰ� ��������
		// 4.�Լ� ȣ���(Invalidate, InvalidateRect, updateAllViews ��)
		// * DC Device Context
		//  ��¿� �ʿ��� ��� ����(���� ����, ����, ����, ��Ʈ ��)�� ������ �ִ� ����ü.
		// ������ �ü�������� ������ ������â���� DC�ڵ��� �ο�.
		// * �����쿡 �׸��� �׸��� ������ BeginPaint(), EndPaint()���̿� �ڵ带 �ִ´�.
		// * WM_PAINT �̺�Ʈ ������ BeginPaint, EndPaint��, �� ���� �̺�Ʈ���� GetDC�� ���.

		//�� �� ���׸���
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 255; i++)
		{
			for (int j = 0; j < 255; j++)
			{
				SetPixel(hdc, i, j, RGB(255, i, j)); //�����
			}
		}

		//���׸���
		MoveToEx(hdc, 200, 50, NULL);
		LineTo(hdc, 500, 400);

		{
			/* ��Ƽ����Ʈ/�����ڵ� ���� �ڵ� 1
#ifdef UNICODE
			//2����Ʈ ���ڼ� ����
			wchar_t str2[] = L"��� ����~2";
			TextOut(hdc, 100, 150, str2, wcslen(str2));
#else
			//1����Ʈ ���ڼ� ����
			char str[] = "��� ����~";
			TextOut(hdc, 100, 100, str, strlen(str));
#endif
			*/
			//������ ���
			int x, y;
			char str1[128], str2[128], str3[128];
			for (int i = 1; i < 10; i++)
			{
				x = ((i - 1) % 3) * 100;
				for (int j = 1; j < 10; j++)
				{
					y = ((j - 1) * 20) + (((i - 1) / 3) * 200);
					_itoa_s(i, str1, 10);
					_itoa_s(j, str2, 10);
					_itoa_s(i * j, str3, 10);
					sprintf_s(str1, "%s + %s = %s", str1, str2, str3);
					TextOut(hdc, x, y, str1, _tcslen(str1));
				}
			}

			//strlen + wcslen = _tcslen
			//strcpy + wcscpy = _tcscpy
			//str* + wcs* = _tcs*

		}
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY: //���α׷� ����� �߻�.
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN: //Ű������ Ű�� �������� �߻�.
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			hdc = GetDC(hWnd);

			TCHAR str3[] = TEXT("��� ����~\n asdas");
			TextOut(hdc, 0, 0, str3, _tcslen(str3));

			ReleaseDC(hWnd, hdc);
		}
		break;
	}

	//�� ����ġ������ ���� ó������ ���� �޼��� ó��.
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void setWindowPositionAndSize(int x, int y, int width, int height)
{
	//POINT : ��ġ, RECT : ũ��
	RECT rc;// {0, 0, width, height};
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//3��° ���ڴ� �޴� ���� ����(bool)
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}