/**========================================
 * Win API
 * @author	박진한(wakeup5, wlsgks5@naver.com)
 * @date	2015/05/11
 * @brief	콘솔 프로젝트로 부터 api 윈도우 창을 구현.
 * ======================================== */
#include "stdafx.h"

/* ========================================
 *  ## 전역변수 ##
 * ======================================== */
HINSTANCE _hInstance; // 프로그램 인스턴스
HWND _hWnd; // 윈도우 핸들

/* ========================================
 *  ## 함수 원형 ##
 * ======================================== */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowPositionAndSize(int x, int y, int width, int height);

/* ========================================
 *  ## 메인 함수 ## - 콘솔 메인 함수처럼 api의 메인 함수
 * ======================================== */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	//_hInstance : 메세지 처리함수 지정.
	//메세지가 발생하면 지정함수를 호출해 메세지를 처리한다.
	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;									// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;									// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			// 커서 모양
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// 상위 창 아이콘 모양
	wndClass.hInstance = hInstance;							// 윈도우 인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						// (*중요)프로시저 함수(메세지 처리함수) - 키보드 입력등에 호출되는 함수
	wndClass.lpszClassName = WIN_NAME;					// 클래스 명(화면 창 이름)
	wndClass.lpszMenuName = NULL;									// 메뉴명
	wndClass.style = CS_HREDRAW | CS_VREDRAW;				// 윈도우 창 상단오른쪽 버튼 스타일

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//윈도우 생성
	_hWnd = CreateWindow(
		WIN_NAME,		// 윈도우 클래스 이름
		WIN_NAME,		// 윈도우 타이틀바의 이름
		WIN_STYLE,	// 윈도우 스타일
		WIN_START_X,			// 윈도우 화면 좌표 x(좌우) - 픽셀 단위
		WIN_START_Y,			// 윈도우 화면 좌표 y(상하) - 픽셀 단위
		WIN_SIZE_X,			// 윈도우 화면 크기 width(폭)
		WIN_SIZE_Y,			// 윈도우 화면 크기 height(높이)
		NULL,					// 부모 윈도우 인스턴스
		(HMENU)NULL,			// 메뉴 핸들
		hInstance,				// 인스턴스 윈도우 지정
		NULL					// mdi 클라이언트 윈도우 및 자식 윈도우를 생성하면 지정해 주고, 사용하지 않으면 NULL
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

	//GetMessage : 메세지 큐(FIFO)에 입력된 메세지를 읽어서 메세지 구조체(변수 MSG message)에 저장한다.
	//TranslateMessage : 키보드 입력에 대한 메세지 처리
	//DispatchMessage : 윈도우 프로시저에 전달된 메세지를 실제 윈도우로 전달해준다. 업데이트? 프로시저 함수 호출 후 처리된 내용을 화면에 갱신해준다.


	//일반 윈도우 창
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//등록된 윈도우 클래스 제거
	UnregisterClass(WIN_NAME, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_CREATE: //클래스의 생성자와 같은 이벤트. 처음 프로그램이 시작 할때 단 한번 발생.

		break;
	case WM_PAINT: 
		// 1.윈도우를 다시 그려야 할때 발생.
		// 2.윈도우 크기를 조정할때
		// 3.다른 윈도우에 가려졌다가 보여질때
		// 4.함수 호출시(Invalidate, InvalidateRect, updateAllViews 등)
		// * DC Device Context
		//  출력에 필요한 모든 정보(선의 색상, 굵기, 배경색, 폰트 등)를 가지고 있는 구조체.
		// 윈도우 운영체제에서는 각각의 윈도우창에게 DC핸들을 부여.
		// * 윈도우에 그림을 그리고 싶으면 BeginPaint(), EndPaint()사이에 코드를 넣는다.
		// * WM_PAINT 이벤트 에서는 BeginPaint, EndPaint를, 이 외의 이벤트에는 GetDC를 사용.

		//점 찍어서 선그리기
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 255; i++)
		{
			for (int j = 0; j < 255; j++)
			{
				SetPixel(hdc, i, j, RGB(255, i, j)); //점찍기
			}
		}

		//선그리기
		MoveToEx(hdc, 200, 50, NULL);
		LineTo(hdc, 500, 400);

		{
			/* 멀티바이트/유니코드 대응 코드 1
#ifdef UNICODE
			//2바이트 문자셋 전용
			wchar_t str2[] = L"헬로 월드~2";
			TextOut(hdc, 100, 150, str2, wcslen(str2));
#else
			//1바이트 문자셋 전용
			char str[] = "헬로 월드~";
			TextOut(hdc, 100, 100, str, strlen(str));
#endif
			*/
			//구구단 출력
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
	case WM_DESTROY: //프로그램 종료시 발생.
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN: //키보드의 키를 눌렀을때 발생.
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

			TCHAR str3[] = TEXT("헬로 월드~\n asdas");
			TextOut(hdc, 0, 0, str3, _tcslen(str3));

			ReleaseDC(hWnd, hdc);
		}
		break;
	}

	//위 스위치문에서 직접 처리하지 않은 메세지 처리.
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void setWindowPositionAndSize(int x, int y, int width, int height)
{
	//POINT : 위치, RECT : 크기
	RECT rc;// {0, 0, width, height};
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//3번째 인자는 메뉴 존재 여부(bool)
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}