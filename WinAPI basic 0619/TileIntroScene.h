#pragma once
#include "SceneManager.h"
class TileIntroScene :
	public Scene
{
public:
	TileIntroScene();
	~TileIntroScene();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};

