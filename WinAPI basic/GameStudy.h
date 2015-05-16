#pragma once
#include "GameNode.h"

using namespace std;

class GameStudy :
	public GameNode
{
private:
	POINTRECT _ellipse;
	POINTRECT _rectangle;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	//virtual LRESULT mainProc(HWND, UINT, WPARAM, LPARAM);

	GameStudy(){}
	virtual ~GameStudy(){}
};

