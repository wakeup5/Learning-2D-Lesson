#pragma once


class GameNode
{
private:
	static Image* _backBuffer;
	HDC _hdc;
	bool _managerInit;
protected:
	GameObject* _object;
	Image* _image;

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

	GameObject* getObject(){ return _object; }
	GameObject* getInfo(){ return _object; }
};

