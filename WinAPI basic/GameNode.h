#pragma once

class GameNode
{
private:
	Image* _backBuffer;
	HDC _hdc;
	bool _managerInit;

	GameObject *_object;
public:
	GameNode();
	virtual ~GameNode();

	//virtual HRESULT initialize(void);
	virtual HRESULT initialize(bool = false);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	virtual LRESULT mainProc(HWND, UINT, WPARAM, LPARAM);

	Image* getBackBuffer(void) { return _backBuffer; }
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }
};

