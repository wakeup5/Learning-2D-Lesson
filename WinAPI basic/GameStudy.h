#pragma once
#include "GameNode.h"
#include "SaveLodeTest.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

class GameStudy :
	public GameNode
{
private:
	PlayerManager* _playerManager;
	EnemyManager* _enemyManager;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

};
