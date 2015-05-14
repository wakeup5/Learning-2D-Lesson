#pragma once
#include "GameNode.h"

class GameStudy :
	public GameNode
{
private:
	RECT _rc;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	//virtual LRESULT mainProc(HWND, UINT, WPARAM, LPARAM);

	GameStudy();
	virtual ~GameStudy();
};

