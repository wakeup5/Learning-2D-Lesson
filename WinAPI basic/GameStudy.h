#pragma once
#include "GameNode.h"
#include "Bullet.h"
#include "Tank.h"

using namespace std;

class GameStudy :
    public GameNode
{
private:
    const int MAX_BULLET = 100;

    Tank _player;
    Bullet _bullet[20];

public:
    virtual HRESULT initialize(void);
    virtual void release(void);
    virtual void update(void);
    virtual void render(HDC hdc);

    void gameInit();

    GameStudy(){}
    virtual ~GameStudy(){}
};

