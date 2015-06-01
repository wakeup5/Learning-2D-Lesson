#pragma once
#include "GameNode.h"
class Missile : public GameNode
{
public:
	Missile();
	virtual ~Missile();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render();
};

