#pragma once
#include "GameNode.h"
#include "Missile.h"

class Rocket :
	public GameNode
{
private:
	Image* _image;
	SpriteImage* _boostImage;

	GameObject _info;

	Missile* _missile;
public:
	Rocket();
	virtual ~Rocket();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render();
};

