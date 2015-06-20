#pragma once
#include "GameNode.h"
#include "BackGround.h"
#include "AnimationImage.h"

class GameStudy : public GameNode
{
private:
	AnimationImage* _image;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageLoad();

};
