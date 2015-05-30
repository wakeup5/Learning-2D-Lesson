#pragma once
#include "GameNode.h"
#include "Bullet.h"
#include "Image.h"
#include "SpriteImage.h"

using namespace std;

class GameStudy :
	public GameNode
{
private:
	Image *_background;

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void gameInit();

};
