#pragma once
#include "GameNode.h"
#include "Missile.h"

class Rocket :
	public GameNode
{
private:
	std::vector<Missile*> _missile;
	SpriteImage* _boostImage;
public:
	Rocket();
	virtual ~Rocket();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render();
};

