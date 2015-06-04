#pragma once
#include "GameNode.h"
#include "Enemy.h"

class EnemyManager :
	public GameNode
{
private:
	typedef std::vector<Enemy*> VEnemy;
	typedef std::vector<Enemy*>::iterator VIEnemy;

	VEnemy _vEnemy;
	VIEnemy _viEnemy;
public:
	EnemyManager();
	~EnemyManager();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};

