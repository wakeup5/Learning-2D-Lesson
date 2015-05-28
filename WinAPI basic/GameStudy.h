#pragma once
#include "GameNode.h"
#include "Image.h"

using namespace std;

class GameStudy :
	public GameNode
{
private:
	Image *_background;

	Image *_image1;

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void gameInit();

	void setBackBuffer();
};

