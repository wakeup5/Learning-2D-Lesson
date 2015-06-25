#include "stdafx.h"
#include "IntroScene.h"
#include "Marine.h"
#include "Zergling.h"
#include "Scourge.h"

extern Unit* _selectUnit;

IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

HRESULT IntroScene::initialize(void)
{
	_image[0] = IMAGEMANAGER->addImage("bg_marine", "resource/starcraft/background_marine.bmp", WIN_SIZE_X / 6.0f, WIN_SIZE_Y / 2.0f, WIN_SIZE_X / 3, WIN_SIZE_Y);
	_image[1] = IMAGEMANAGER->addImage("bg_zerg", "resource/starcraft/background_zerg.bmp", WIN_SIZE_X / 2.0f, WIN_SIZE_Y / 2.0f, WIN_SIZE_X / 3, WIN_SIZE_Y);
	_image[2] = IMAGEMANAGER->addImage("bg_scourge", "resource/starcraft/background_scourge.bmp", 5 * WIN_SIZE_X / 6.0f, WIN_SIZE_Y / 2.0f, WIN_SIZE_X / 3, WIN_SIZE_Y);

	_unit[0] = new Marine;
	_unit[0]->initialize(WIN_SIZE_X / 6.0f, 100, 270, 0);
	_unit[1] = new Zergling;
	_unit[1]->initialize(WIN_SIZE_X / 2.0f, 100, 270, 0);
	_unit[2] = new Scourge;
	_unit[2]->initialize(5 * WIN_SIZE_X / 6.0f, 100, 270, 0);

	_view = _unit[0];

	_selectNum = 0;
	_selectMenu = 0;

	_buttonU = IMAGEMANAGER->addImage("buttonUD", "resource/starcraft/star_button.bmp", 20, 10, TRUE, RGB(255, 0, 255))->createSprite(2, 1);
	_buttonU->setFrameX(0);
	_buttonD = IMAGEMANAGER->addImage("buttonUD", "resource/starcraft/star_button.bmp", 20, 10, TRUE, RGB(255, 0, 255))->createSprite(2, 1);
	_buttonD->setFrameX(1);
	_button = IMAGEMANAGER->addImage("button", "resource/starcraft/button.bmp", 200, 38);
	return S_OK;
}
void IntroScene::release(void)
{

}
void IntroScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_image[i]->boundingBox(), _mousePt))
			{
				_selectNum = i;
				_view = _selectUnit = _unit[i];
				if(_view) _view->setAngleD(270);
				break;
			}
		}
		if (_mousePt.y > 200 && _mousePt.y < 500) _selectMenu = float(_mousePt.y - 200) / 50;

		if (PtInRect(&_buttonU->getRect(), _mousePt))
		{
			if (_selectMenu == 0 && (_view->getMaxHP() < 5000)) _view->setMaxHP(_view->getMaxHP() + 100);
			if (_selectMenu == 1 && (_view->getHP() < _view->getMaxHP())) _view->setHP(_view->getHP() + 100);
			if (_selectMenu == 2 && (_view->getMaxMP() < 5000)) _view->setMaxMP(_view->getMaxMP() + 100);
			if (_selectMenu == 3 && (_view->getMP() < _view->getMaxMP())) _view->setMP(_view->getMP() + 100);
			if (_selectMenu == 4 && (_view->getMaxSpeed() < 500)) _view->setMaxSpeed(_view->getMaxSpeed() + 100);
			if (_selectMenu == 5 && (_view->getViewAccel() < 5000)) _view->setViewAccel(_view->getViewAccel() + 100);
		}
		if (PtInRect(&_buttonD->getRect(), _mousePt))
		{
			if (_selectMenu == 0 && (_view->getMaxHP() > 0)) _view->setMaxHP(_view->getMaxHP() - 100);
			if (_selectMenu == 1 && (_view->getHP() > 0)) _view->setHP(_view->getHP() - 100);
			if (_selectMenu == 2 && (_view->getMaxMP() > 0)) _view->setMaxMP(_view->getMaxMP() - 100);
			if (_selectMenu == 3 && (_view->getMP() > 0)) _view->setMP(_view->getMP() - 100);
			if (_selectMenu == 4 && (_view->getMaxSpeed() > 0)) _view->setMaxSpeed(_view->getMaxSpeed() - 100);
			if (_selectMenu == 5 && (_view->getViewAccel() > 0)) _view->setViewAccel(_view->getViewAccel() - 100);
		}

		if (PtInRect(&_button->boundingBox(), _mousePt))
		{
			SCENEMANAGER->changeScene("starcraft");
		}
	}

	float coorX = WIN_SIZE_X / 6 + ((WIN_SIZE_X / 3) * _selectNum);
	_buttonU->setCenter(coorX + 85, 205 + _selectMenu * 50);
	_buttonD->setCenter(coorX + 95, 205 + _selectMenu * 50);
	_button->setCenter(coorX, WIN_SIZE_Y - 40);

	if (TIMEMANAGER->checkTime("unit rolling", 50)) if (_view) _view->setAngleD(_view->getAngleD() + 2);
	if (_view)
	{
		_view->update();
		//_view->setPosition(coorX, 100);
	}
}
void IntroScene::render(void)
{
	for (int i = 0; i < 3; i++)
	{
		_image[i]->render(getMemDC(), (i == _selectNum)? 25 : 255);
	}
	if (_view) _view->render(getMemDC());
	_buttonU->render(getMemDC());
	_buttonD->render(getMemDC());
	_button->render(getMemDC());
	viewInfo();
}

//////////////////////출력/////////////////////////////i
inline void printNumber(HDC hdc, int x, int y, SpriteImage* image, int num)
{
	int digit = 1;
	int i = 0;

	if (num == 0)
	{
		image->setFrameX(0);
		image->render(hdc, x, y);
		return;
	}

	while (digit <= num)
	{
		int digitNum = num % (digit * 10) / digit;
		image->setFrameX(digitNum);
		image->render(hdc, x - (i * image->getFrameWidth()), y);

		digit *= 10;
		i++;
	}

}

void IntroScene::viewInfo()
{
	float coorX = WIN_SIZE_X / 6 + ((WIN_SIZE_X / 3) * _selectNum);

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(0, 100, 0));

	TextOut(getMemDC(), coorX - 100, 200, "최대 생명력", strlen("최대 생명력"));
	TextOut(getMemDC(), coorX - 100, 250, "생명력", strlen("생명력"));
	TextOut(getMemDC(), coorX - 100, 300, "최대 마나", strlen("최대 마나"));
	TextOut(getMemDC(), coorX - 100, 350, "마나", strlen("마나"));
	TextOut(getMemDC(), coorX - 100, 400, "최고 속도", strlen("최고 속도"));
	TextOut(getMemDC(), coorX - 100, 450, "가속도", strlen("가속도"));

	SpriteImage* image = IMAGEMANAGER->addImage("number", "resource/starcraft/star_number.bmp", 100, 10, TRUE, RGB(255, 0, 255))->createSprite(10, 1);

	printNumber(getMemDC(), coorX + 50, 200, image, _view->getMaxHP());
	printNumber(getMemDC(), coorX + 50, 250, image, _view->getHP());
	printNumber(getMemDC(), coorX + 50, 300, image, _view->getMaxMP());
	printNumber(getMemDC(), coorX + 50, 350, image, _view->getMP());
	printNumber(getMemDC(), coorX + 50, 400, image, _view->getMaxSpeed());
	printNumber(getMemDC(), coorX + 50, 450, image, _view->getViewAccel());
}
