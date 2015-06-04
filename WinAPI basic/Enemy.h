#pragma once
#include "GameNode.h"
class Enemy : public GameObject
{
private:
	SpriteImage* _image;
	float _frameTime;
public:
	Enemy();
	virtual ~Enemy();

	virtual HRESULT initialize(SpriteImage* image, float frameTime);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};

