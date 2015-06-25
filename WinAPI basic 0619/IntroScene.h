#pragma once
#include "SceneManager.h"
#include "Unit.h"

class IntroScene : public Scene
{
private:
	Image* _image[3];
	SpriteImage* _buttonU;
	SpriteImage* _buttonD;
	Image* _button;

	Unit* _unit[3];
	Unit* _view;
	int _selectNum;
	int _selectMenu;
public:
	IntroScene();
	~IntroScene();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void viewInfo();
};

