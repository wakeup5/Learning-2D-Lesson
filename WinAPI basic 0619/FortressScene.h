#pragma once
#include "SceneManager.h"
#include "Tank.h"

#define TRANS_COLOR RGB(255, 255, 255)

class FortressScene : public Scene
{
private:
	Image* _landImg;
	Image* _tankImg1;
	Image* _tankImg2;

	Tank* _tank[2];

	GameObject* _bullet;
	bool _isBulletLive;
public:
	FortressScene();
	~FortressScene();

	HRESULT initialize();
	void release();
	void update();
	void render();

	long getYPixel(RECT currentRect);
	bool checkTransColor(long x, long y, COLORREF transColor);
};
