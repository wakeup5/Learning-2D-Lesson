#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{

}


GameNode::~GameNode()
{

}

//�ʱ�ȭ
HRESULT GameNode::initialize(void)
{
	SetTimer(_hWnd, 0, 10, NULL);

	KEYMANAGER->initialize();

	setBackBuffer();

	return S_OK;
}

//����
void GameNode::release(void)
{
	_backBuffer->release();
	SAFE_DELETE(_backBuffer);

	KillTimer(_hWnd, 0);

	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
}

//ȭ�鰻��
void GameNode::update(void)
{
	//ȭ�� ����
	InvalidateRect(_hWnd, NULL, false);
}

//ȭ�����
void GameNode::render(HDC hdc)
{
	//_backBuffer->render(hdc, WIN_SIZE_X, WIN_SIZE_Y);
}

LRESULT GameNode::mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		_mousePoint = makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_mousePoint = makeMousePoint(lParam);
		break;
	case WM_TIMER:
		this->update();
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


//����� ����
void GameNode::setBackBuffer()
{
	_backBuffer = new Image();
	_backBuffer->initialize(WIN_SIZE_X, WIN_SIZE_Y);

}