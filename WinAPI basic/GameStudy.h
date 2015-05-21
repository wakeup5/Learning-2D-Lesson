#pragma once

#include "GameNode.h"

#define WORM_LENGTH 20

using namespace std;

class GameStudy :
	public GameNode
{
private:
    typedef struct tagWorm
    {
        float x, y;
        float angleR;
        float angleD;
        float prevR;
        float prevD;
        int speed;
        float size;
    }Worm;

    Worm _worm[WORM_LENGTH];
public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

