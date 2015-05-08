/**========================================
 * api구현
 * @file	main.cpp
 * @author	박진한(wakeup5, wlsgks5@naver.com)
 * @date	2015/05/08
 * @brief	콘솔 프로젝트로 부터 api 윈도우 창을 구현.
 * ======================================== */

/* ========================================
 *  ## 헤더파일 ##
 * ======================================== */
#include <Windows.h>

/* ========================================
 *  ## 전역변수 ##
 * ======================================== */
HINSTANCE _hInstance; //<프로그램 인스턴스
HWND _hWnd;

CHAR _className[128] = "API Window";

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

	wndClass.cbClsExtra		= 0;									// 클래스 여분 메모리
	wndClass.cbWndExtra		= 0;									// 윈도우 여분 메모리
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	// 백그라운드
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// 커서 모양
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// 상위 창 아이콘 모양
	wndClass.hInstance		= hInstance;							// 윈도우 인스턴스
	wndClass.lpfnWndProc	= (WNDPROC)WndProc;						// (*중요)프로시저 함수(메세지 처리함수) - 키보드 입력등에 호출되는 함수
	wndClass.lpszClassName	= (LPCSTR)_className;					// 클래스 명(화면 창 이름)
	wndClass.lpszMenuName	= NULL;									// 메뉴명
	wndClass.style			= CS_HREDRAW | CS_VREDRAW;				// 윈도우 창 상단오른쪽 버튼 스타일

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//윈도우 생성
	_hWnd = CreateWindow(
		(LPCSTR)_className,		// 윈도우 클래스 이름
		(LPCSTR)_className,		// 윈도우 타이틀바의 이름
		WS_OVERLAPPEDWINDOW,	// 윈도우 스타일
		CW_USEDEFAULT,			// 윈도우 화면 좌표 x(좌우) - 픽셀 단위
		CW_USEDEFAULT,			// 윈도우 화면 좌표 y(상하) - 픽셀 단위
		CW_USEDEFAULT,			// 윈도우 화면 크기 width(폭)
		CW_USEDEFAULT,			// 윈도우 화면 크기 height(높이)
		NULL,					// 부모 윈도우 인스턴스
		(HMENU)NULL,			// 메뉴 핸들
		hInstance,				// 인스턴스 윈도우 지정
		NULL					// mdi 클라이언트 윈도우 및 자식 윈도우를 생성하면 지정해 주고, 사용하지 않으면 NULL
		);

	setWindowPositionAndSize(0, 0, 200, 200);
	
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
	UnregisterClass((LPCSTR)_className, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, 
	WPARAM wParam, // 키보드
	LPARAM lParam) // 마우스
{
	//키보드 입력 혹은 여러가지 메세지를 구분하여 작업을 할 수 있다.
	switch (iMessage)
	{
	case WM_DESTROY: //종료 호출 메세지
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