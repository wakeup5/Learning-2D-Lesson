#pragma once
#include "GameNode.h"
class Player : public GameObject
{
private:
	Image* _image;
	SpriteImage* _boostImage;
public:
	Player();
	virtual ~Player();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();
};

