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

void homework2(HWND, UINT, WPARAM, LPARAM);
void homework3(HWND, UINT, WPARAM, LPARAM);
void homework4(HWND, UINT, WPARAM, LPARAM);
void homework5(HWND, UINT, WPARAM, LPARAM);

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
	static int homeworkNum = 1;
	
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			homeworkNum++;
			if (homeworkNum > 2) homeworkNum = 1;
			//KillTimer(hWnd, 2);
			//KillTimer(hWnd, 3);
			//KillTimer(hWnd, 4);
			//KillTimer(hWnd, 5);
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_DESTROY: //���α׷� ����� �߻�.
		PostQuitMessage(0);
		return 0;
	}

	switch (homeworkNum)
	{
	case 1:
		homework2(hWnd, iMessage, wParam, lParam);
		break;
	case 2:
		homework3(hWnd, iMessage, wParam, lParam);
		break;
	case 3:
		homework4(hWnd, iMessage, wParam, lParam);
		break;
	case 4:
		homework5(hWnd, iMessage, wParam, lParam);
		break;
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

//���� 1 RandomFunction float�޼ҵ� ����.
//���� 2 �簢���� ����� �簢���� �巡�� �ϸ� ũ�Ⱑ ����.
void homework2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static POINT mp;
	static RECT r;

	static POINTRECT pr = makePointRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 100, 100);

	static bool isClick = false;
	static int whereClick = 0;
	static int dx = 0, dy = 0;

	mp = makeMousePoint(lParam);

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		drawRectangle(hdc, pr.rect);
		TCHAR a[] = "���� 2 - ���콺 �巡�׷� ���� ũ�� ����";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
		if (checkCollision(mp, pr.rect))
		{
			isClick = true;
			if (mp.x < pr.point.x && mp.y < pr.point.y)
			{
				whereClick = 1;
				dx = pr.rect.left - mp.x;
				dy = pr.rect.top - mp.y;
			}
			else if (mp.x > pr.point.x && mp.y < pr.point.y)
			{
				whereClick = 2;
				dx = pr.rect.right - mp.x;
				dy = pr.rect.top - mp.y;
			}
			else if (mp.x < pr.point.x && mp.y > pr.point.y)
			{
				whereClick = 3;
				dx = pr.rect.left - mp.x;
				dy = pr.rect.bottom - mp.y;
			}
			else if (mp.x > pr.point.x && mp.y > pr.point.y)
			{
				whereClick = 4;
				dx = pr.rect.right - mp.x;
				dy = pr.rect.bottom - mp.y;
			}
		}
		break;
	case WM_LBUTTONUP:
		isClick = false;
		break;
	case WM_MOUSEMOVE:
	{
		if (isClick)
		{
			if (whereClick == 1)
			{
				pr.rect.left = mp.x + dx;
				pr.rect.top = mp.y + dy;
			}
			else if (whereClick == 2)
			{
				pr.rect.right = mp.x + dx;
				pr.rect.top = mp.y + dy;
			}
			else if (whereClick == 3)
			{
				pr.rect.left = mp.x + dx;
				pr.rect.bottom = mp.y + dy;
			}
			else if (whereClick == 4)
			{
				pr.rect.right = mp.x + dx;
				pr.rect.bottom = mp.y + dy;
			}
		}
		pr.point.x = pr.rect.left + (pr.rect.right - pr.rect.left) / 2;
		pr.point.y = pr.rect.top + (pr.rect.bottom - pr.rect.top) / 2;

		InvalidateRect(hWnd, NULL, true);
	}
		break;
	}
}

//���� 3 �����ϱ�
void homework3(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static POINTRECT player = makePointRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y - 20, 20, 20);

	player = makePointRectCenter(player.point, 20, 20);

	//int speed = 10;

	static vector<POINT> *ddongs = new vector<POINT>;
	vector<POINT>::iterator iter;

	static RECT gamePad = RECT{ 10, 10, WIN_SIZE_X - 10, WIN_SIZE_Y - 10 };
	static int maxSpeed = 10;
	static float speed = 0;
	static bool isKeyDown = false, isLeft = false, isRight = false;
	static bool isDead = false;
	static int po = 0;

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		drawRectangle(hdc, gamePad);
		drawEllipse(hdc, player.rect);

		for (iter = ddongs->begin(); iter != ddongs->end(); iter++)
		{
			drawRectangleCenter(hdc, *iter, 20, 20);
		}

		TCHAR a[128] = "���� 3 - �����ϱ� - ";
		wsprintf(a, "%s ����:%5d ����:%2d", a, po, ddongs->size());
		TextOut(hdc, 10, 10, a, _tcslen(a));

		if (isDead)
		{
			TCHAR b[128] = "���� ���";
			wsprintf(b, "%s %5d�� �����̽��� ������", b, po);
			TextOut(hdc, (WIN_SIZE_X / 2) - 50, (WIN_SIZE_Y / 2) - 10 , b, _tcslen(b));
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER:
		if (wParam == 0)
		{
			if (RANDOM->getInt(100) < 10 + po / 20)
			{
				int randX = RANDOM->getIntTo(gamePad.left + 10, gamePad.right - 10);
				ddongs->push_back(POINT{ randX, 20 });
			}

			for (iter = ddongs->begin(); iter != ddongs->end(); iter++)
			{
				iter->y *= 1.05;
				if (iter->y > WIN_SIZE_Y + 20)
				{
					iter = ddongs->erase(iter);
					po++;
				}
				//�浹ó��
				if (checkCollision(makeRectCenter(*iter, 20, 20), player.rect))
				{
					KillTimer(hWnd, 0);
					isDead = true;
				}
			}
			/*
			hdc = GetDC(hWnd);
			for (iter = ddongs.begin(); iter != ddongs.end(); iter++)
			{
			drawRectangleCenter(hdc, *iter, 20, 20);
			}
			ReleaseDC(hWnd, hdc);
			*/

			if (player.rect.left + speed > gamePad.left && player.rect.right + speed < gamePad.right)
			{
				player.point.x += speed;
			}
			else
			{
				speed = 0;
			}

			if (!isKeyDown) speed = (int)speed * 0.8;
			else
			{
				if (isLeft)
				{
					if (-maxSpeed < speed)
						speed -= 0.5;
				}
				else if (isRight)
				{
					if (maxSpeed > speed)
						speed += 0.5;
				}
			}

			InvalidateRect(hWnd, NULL, true);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_TAB)
		{
			SetTimer(hWnd, 0, 10, NULL);
			ddongs = new vector < POINT > ;
			po = 0;
			isDead = false;
		}
		switch (wParam)
		{
		case VK_LEFT:
			isLeft = true;
			isRight = false;
			break;
		case VK_RIGHT:
			isLeft = false;
			isRight = true;
			break;
		case VK_SPACE:
			if (isDead)
			{
				SetTimer(hWnd, 0, 10, NULL);
				ddongs = new vector < POINT >;
				po = 0;
				isDead = false;
			}
			break;
		}
		
		isKeyDown = true;
		break;
	case WM_KEYUP:
		isKeyDown = false;
		isLeft = false;
		isRight = false;
		break;
	}
}

//���� 4 ������ �� �ǳʱ� ���� 
// - �������� ������
// - �������� ����� �������� �پ��
// - �������� ó��, �߰��� ������ �ִ�.
// - �������� ��ġ�� �������� ������
// - ���ع��� �Դ� ���� �ϴµ� �����̶� ������ ����
void homework4(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		TCHAR a[] = "���� 4 - ��ǳʱ�";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}

//���� 5 ���ð���
// - �����̽��� ������ �Ѿ� �ϳ� ����. ���߷� ������ ������ �߻�.
void homework5(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		TCHAR a[] = "���� 5 - ���ð���";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}