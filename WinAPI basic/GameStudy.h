#pragma once
#include "GameNode.h"
#include "Image.h"
#include "SpriteImage.h"

using namespace std;

class GameStudy :
	public GameNode
{
private:
	Image *_background;

	Image *_image;
	SpriteImage *_s;
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

