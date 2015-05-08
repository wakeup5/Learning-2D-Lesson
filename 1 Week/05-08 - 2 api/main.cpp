/**========================================
 * api����
 * @file	main.cpp
 * @author	������(wakeup5, wlsgks5@naver.com)
 * @date	2015/05/08
 * @brief	�ܼ� ������Ʈ�� ���� api ������ â�� ����.
 * ======================================== */

/* ========================================
 *  ## ������� ##
 * ======================================== */
#include <Windows.h>

/* ========================================
 *  ## �������� ##
 * ======================================== */
HINSTANCE _hInstance; //<���α׷� �ν��Ͻ�
HWND _hWnd;

CHAR _className[128] = "API Window";

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

	wndClass.cbClsExtra		= 0;									// Ŭ���� ���� �޸�
	wndClass.cbWndExtra		= 0;									// ������ ���� �޸�
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	// ��׶���
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Ŀ�� ���
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// ���� â ������ ���
	wndClass.hInstance		= hInstance;							// ������ �ν��Ͻ�
	wndClass.lpfnWndProc	= (WNDPROC)WndProc;						// (*�߿�)���ν��� �Լ�(�޼��� ó���Լ�) - Ű���� �Էµ ȣ��Ǵ� �Լ�
	wndClass.lpszClassName	= (LPCSTR)_className;					// Ŭ���� ��(ȭ�� â �̸�)
	wndClass.lpszMenuName	= NULL;									// �޴���
	wndClass.style			= CS_HREDRAW | CS_VREDRAW;				// ������ â ��ܿ����� ��ư ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ ����
	_hWnd = CreateWindow(
		(LPCSTR)_className,		// ������ Ŭ���� �̸�
		(LPCSTR)_className,		// ������ Ÿ��Ʋ���� �̸�
		WS_OVERLAPPEDWINDOW,	// ������ ��Ÿ��
		CW_USEDEFAULT,			// ������ ȭ�� ��ǥ x(�¿�) - �ȼ� ����
		CW_USEDEFAULT,			// ������ ȭ�� ��ǥ y(����) - �ȼ� ����
		CW_USEDEFAULT,			// ������ ȭ�� ũ�� width(��)
		CW_USEDEFAULT,			// ������ ȭ�� ũ�� height(����)
		NULL,					// �θ� ������ �ν��Ͻ�
		(HMENU)NULL,			// �޴� �ڵ�
		hInstance,				// �ν��Ͻ� ������ ����
		NULL					// mdi Ŭ���̾�Ʈ ������ �� �ڽ� �����츦 �����ϸ� ������ �ְ�, ������� ������ NULL
		);

	setWindowPositionAndSize(0, 0, 200, 200);
	
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
	UnregisterClass((LPCSTR)_className, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, 
	WPARAM wParam, // Ű����
	LPARAM lParam) // ���콺
{
	//Ű���� �Է� Ȥ�� �������� �޼����� �����Ͽ� �۾��� �� �� �ִ�.
	switch (iMessage)
	{
	case WM_DESTROY: //���� ȣ�� �޼���
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
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