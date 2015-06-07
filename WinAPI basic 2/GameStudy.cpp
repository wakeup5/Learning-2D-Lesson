#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);
	IMAGEMANAGER->addImage("mapImage", "resource/mapBlack.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("background", "resource/backMap.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	IMAGEMANAGER->addImage("time bar", "resource/time bar.bmp", WIN_SIZE_X - 20, 20);

	_stage = 1;
	_time = GetTickCount();
	_isGameOver = false;

	_gameTime = 6000;

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
	if (_hs != NULL) _hs->release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	static int time = 0;

	if (_hs == NULL)
	{
		if (_stage == 1) init1();
	}

	if (_hs != NULL)
	{
		if (!_isGameOver && !_hs->isClear()) _hs->update();

		if (_hs->isClear())
		{
			time++;

			if (time > 100)
			{
				_stage++;
				_hs->release();
				SAFE_DELETE(_hs);
				_time = GetTickCount();
			}
		}
		else
		{
			if (GetTickCount() - _time > _gameTime)
			{
				_isGameOver = true;
			}

			static int go = 0;
			if (_isGameOver)
			{
				if (go > 100)
				{
					if (_stage == 1) init1();
					_isGameOver = false;
					go = 0;
				}
				go++;
			}
		}
	}

	

	
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("mapImage", getMemDC());
	IMAGEMANAGER->render("background", getMemDC());

	if (_hs != NULL)
	{
		_hs->render();

		if (_hs->isClear())
		{
			TextOut(getMemDC(), WIN_SIZE_X / 2, WIN_SIZE_Y / 2, "클리어!!", 8);
		}
		else if (_isGameOver)
		{
			TextOut(getMemDC(), WIN_SIZE_X / 2, WIN_SIZE_Y / 2, "게임오버!!", 10);
		}
		else
		{
			float t = GetTickCount() - _time;
			IMAGEMANAGER->render("time bar", getMemDC(), 10.0f, 10.0f, 0, 0, (WIN_SIZE_X - 20) - ((t / _gameTime) * (WIN_SIZE_X - 20)), 20);
		}
	}

	GameNode::render();
}

void GameStudy::init1()
{
	vector<RECT> _vRc1;
	_vRc1.push_back(RECT{ 794, 481, 864, 533 });
	_vRc1.push_back(RECT{ 700, 434, 725, 450 });
	_vRc1.push_back(RECT{ 596, 553, 657, 578 });
	_vRc1.push_back(RECT{ 557, 52, 599, 77 });
	_vRc1.push_back(RECT{ 806, 79, 824, 109 });
	_vRc1.push_back(RECT{ 682, 332, 768, 387 });

	_hs = new HiddenSearch;
	_hs->initialize(
		IMAGEMANAGER->addImage("oreginal 2", "resource/2-1.bmp", 500, 700),
		IMAGEMANAGER->addImage("modify 2", "resource/2-2.bmp", 500, 700),
		_vRc1,
		IMAGEMANAGER->addImage("ok", "resource/ok.bmp", 50, 39, TRUE, RGB(255, 0, 255)));

	_time = GetTickCount();
}
void GameStudy::init2()
{

}
void GameStudy::init3()
{

}