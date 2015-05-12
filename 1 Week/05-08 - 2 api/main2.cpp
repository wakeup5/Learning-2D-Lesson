#include <Windows.h>

HINSTANCE _hInstance;
HWND _hWnd;

CHAR _className[128] = "API";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int showNum)
{
	MSG message;
	WNDCLASS wndClass;

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;									// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;									// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			// 커서 모양
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// 상위 창 아이콘 모양
	wndClass.hInstance = hInstance;							// 윈도우 인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						// (*중요)프로시저 함수(메세지 처리함수) - 키보드 입력등에 호출되는 함수
	wndClass.lpszClassName = (LPCSTR)_className;					// 클래스 명(화면 창 이름)
	wndClass.lpszMenuName = NULL;									// 메뉴명
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		(LPCSTR)_className,
		(LPCSTR)_className,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		200,
		200,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
		);

	ShowWindow(_hWnd, showNum);

	//게임용
	/*
	while (true)
	{
		if (PeekMessage(&message, _hWnd, 0, 0, PM_REMOVE))
		{
			if (message.message = WM_QUIT)
			{
				break;
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		//출력 처리
	}
	*/

	//보통
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnregisterClass((LPCSTR)_className, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, lParam, wParam);
}