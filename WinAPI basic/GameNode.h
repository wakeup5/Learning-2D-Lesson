#pragma once
class GameNode
{
public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	virtual LRESULT mainProc(HWND, UINT, WPARAM, LPARAM);

	GameNode();
	virtual ~GameNode();
};

