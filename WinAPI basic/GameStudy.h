#pragma once
#include "GameNode.h"
#include "Bullet.h"

#define MISSILE_SPEED 10
#define MISSILE_SIZE 30
#define MAX_MISSILE 16

using namespace std;

class GameStudy :
    public GameNode
{
private:
    Bullet _bullet[MAX_MISSILE];
    RECT _table;
    UINT _colors[8];

    float _power;
    float _mouseR;
    bool _isClick;

public:
    virtual HRESULT initialize(void);
    virtual void release(void);
    virtual void update(void);
    virtual void render(HDC hdc);

    void gameInit();

    GameStudy(){}
    virtual ~GameStudy(){}
};

