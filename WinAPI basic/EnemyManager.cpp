#include "stdafx.h"
#include "EnemyManager.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::initialize()
{
	GameNode::initialize();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Enemy* enemy = new Enemy;
			enemy->initialize(IMAGEMANAGER->addSpriteImage("ufo", "resource/enemy.bmp", 306, 58, 6, 2, TRUE, RGB(255, 0, 255)), RANDOM->getFloatTo(20, 100));
			enemy->setPosition((WIN_SIZE_X / 2) + (j - 2) * 100, 100 + i * 100);
			enemy->setSize(50, 50);
			enemy->setAngleR(RANDOM->getFloat(2 * M_PI));
			enemy->setSpeed(1);

			_vEnemy.push_back(enemy);
		}
	}

	return S_OK;
}
void EnemyManager::release(void)
{

}
void EnemyManager::update(void)
{
	GameNode::update();

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->update();
		if ((*_viEnemy)->getY() > WIN_SIZE_Y - 100 || 
			(*_viEnemy)->getY() < 100 ||
			(*_viEnemy)->getX() > WIN_SIZE_X - 100 ||
			(*_viEnemy)->getX() < 100)
		{
			(*_viEnemy)->setAngleD((*_viEnemy)->getAngleD() + 2);
		}
	}
}
void EnemyManager::render(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->render();
	}
}