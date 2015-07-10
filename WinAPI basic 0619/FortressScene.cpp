#include "stdafx.h"
#include "FortressScene.h"


FortressScene::FortressScene()
{

}


FortressScene::~FortressScene()
{
}

HRESULT FortressScene::initialize()
{
	_landImg = IMAGEMANAGER->addImage("land", "resource/fortress/land.bmp", WIN_SIZE_X / 2.0f, WIN_SIZE_Y / 2.0f, 800, 600, TRUE, TRANS_COLOR);
	_tankImg1 = IMAGEMANAGER->addImage("tank1", "resource/fortress/tank1.bmp", 50, 50, TRUE, TRANS_COLOR);
	_tankImg2 = IMAGEMANAGER->addImage("tank2", "resource/fortress/tank2.bmp", 50, 50, TRUE, TRANS_COLOR);

	_tank[0] = new Tank;
	_tank[0]->setCenter(100, 100);

	_tank[1] = new Tank;
	_tank[1]->setCenter(700, 100);

	_bullet = new GameObject;
	_bullet->initialize(0, 0, 10, 10, 0, 0);
	_isBulletLive = false;

	return S_OK;
}
void FortressScene::release()
{

}
void FortressScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_tank[0]->setSpeedX(-100);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_tank[0]->setSpeedX(100);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_tank[0]->setSpeedX(0);
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_tank[1]->setSpeedX(-100);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_tank[1]->setSpeedX(100);
	}
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		_tank[1]->setSpeedX(0);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_isBulletLive)
	{
		_bullet->setCenter(_tank[0]->getX(), _tank[0]->getY());
		_bullet->setAngleD(45);
		_bullet->setSpeed(300);
		_isBulletLive = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && !_isBulletLive)
	{
		_bullet->setCenter(_tank[1]->getX(), _tank[1]->getY());
		_bullet->setAngleD(135);
		_bullet->setSpeed(300);
		_isBulletLive = true;
	}

	if (_isBulletLive)
	{
		_bullet->setAccelY(980);
		_bullet->activate();

		if (!checkTransColor(_bullet->getX(), _bullet->getY(), TRANS_COLOR))
		{
			HBRUSH b, ob;
			HPEN p, op;

			b = CreateSolidBrush(TRANS_COLOR);
			ob = (HBRUSH)SelectObject(_landImg->getMemDC(), b);
			p = CreatePen(PS_SOLID, 1, TRANS_COLOR);
			op = (HPEN)SelectObject(_landImg->getMemDC(), p);

			Ellipse(_landImg->getMemDC(), _bullet->getX() - 50, _bullet->getY() - 50, _bullet->getX() + 50, _bullet->getY() + 50);

			SelectObject(_landImg->getMemDC(), ob);
			DeleteObject(b);
			SelectObject(_landImg->getMemDC(), op);
			DeleteObject(p);

			_isBulletLive = false;
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		long pixelY = getYPixel(_tank[i]->getRect());
		if (pixelY < 0)
		{
			_tank[i]->setAccelY(980);
		}
		else
		{
			_tank[i]->setY(pixelY - (_tank[i]->getHeight() / 2));
			_tank[i]->setSpeedY(0);
			_tank[i]->setAccel(0);
		}
		_tank[i]->activate();
	}
}
void FortressScene::render()
{
	_landImg->render(getMemDC());
	_tankImg1->render(getMemDC(), _tank[0]->getRect().left, _tank[0]->getRect().top);
	_tankImg2->render(getMemDC(), _tank[1]->getRect().left, _tank[1]->getRect().top);

	if (_isBulletLive)
	{
		Ellipse(getMemDC(), _bullet->getRect().left, _bullet->getRect().top, _bullet->getRect().right, _bullet->getRect().bottom);
	}
}

long FortressScene::getYPixel(RECT currentRect)
{
	long x = (currentRect.left + currentRect.right) / 2;
	long top = currentRect.top;
	long bottom = currentRect.bottom + 1;

	for (int i = top; i < bottom; ++i)
	{
		COLORREF color = GetPixel(_landImg->getMemDC(), x, i);

		if (color != TRANS_COLOR)
		{
			return i;
		}
	}

	return -1;
}

bool FortressScene::checkTransColor(long x, long y, COLORREF transColor)
{
	if (x < 0 || x > WIN_SIZE_X) return false;

	COLORREF color = GetPixel(_landImg->getMemDC(), x, y);

	return color == transColor;
}