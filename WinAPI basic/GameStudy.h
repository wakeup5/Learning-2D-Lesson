#pragma once
#include "GameNode.h"
#include "Image.h"

#define PUZZLE_COL 3
#define PUZZLE_ROW 3
#define PUZZLE_LENGTH PUZZLE_COL * PUZZLE_ROW

using namespace std;

class GameStudy :
	public GameNode
{
private:
	Image *_background;

	Image *_puzzleImage;

	int _puzzleNum[PUZZLE_LENGTH];
	RECT _puzzleRect[PUZZLE_LENGTH];
	int _voidNum;

	int _pieceWidth, _pieceHeight;

	bool _isGameStart = false;

	void puzzleSwap(int clickNum);

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void gameInit();

	void setBackBuffer();
};

