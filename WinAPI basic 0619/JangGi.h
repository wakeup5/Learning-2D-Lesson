#pragma once
#include "GameNode.h"

inline float getCoorXByPointX(long x);
inline float getCoorYByPointY(long y);
inline int changeCamp(int camp);

typedef enum JANGGIMAL{
	KING = 0, CANNON, ELEPHANT, HORSE, CAR, OFFICER, SOLDIER
};
typedef enum CAMP{
	RED = 0, BLUE
};
typedef enum JANGGI_TURN_STATE{
	PLAY_TURN_START = 0, PLAY_MAL_CLICK, PLAY_MAL_MOVE, PLAY_MAL_MOVE_FAIL, PLAY_MAL_TAKE
} TurnState;
typedef enum MOVABLE_STATE{
	MOVABLE_EMPTY = 0, MOVABLE_DIFF_CANNON = 1, MOVABLE_DIFF, MOVABLE_NO_OUT = 10, MOVABLE_NO_SAME_CANNON = 11, MOVABLE_NO_SAME, MOVABLE_NO_BLOCKED
} MovableState;
enum CASTLE_MOVABLE{
	CASTLE_LEFT, CASTLE_RIGHT, CASTLE_UP, CASTLE_DOWN
};

class JangGiMal;
class JangGi : public GameNode
{
private:
	typedef struct tagJangGiPan
	{
		RECT rc;
		JangGiMal* mal;
		tagJangGiPan(RECT r)
		{
			rc = r;
			mal = NULL;
		}
	} JangGiPan;

	Image* _backImage;

	JangGiMal* _mal[2][16];
	JangGiPan* _pan[10][9];

	CAMP _turn;
	TurnState _turnState;
	JangGiMal* _selectMal;

	std::list<POINT> _movablePoint;

	int _takeMal[2];		//잡힌 말의 갯수

	bool _isGameEnd;
public:
	JangGi();
	~JangGi();

	HRESULT initialize();
	void release();
	void update();
	void render();

	std::list<POINT> movablePoint(JangGiMal* mal);

	MOVABLE_STATE checkMovablePoint(int startX, int startY, int endX, int endY, JangGiMal *mal);
	void addMovablePoint(int malX, int malY, int endX, int endY, JangGiMal* mal, std::list<POINT> * lPoint);
	MOVABLE_STATE checkMovablePointByCannon(int startX, int startY, int endX, int endY, JangGiMal *mal, bool isExistWall);
	void addMovablePointByCannon(int malX, int malY, int moveX, int moveY, JangGiMal* mal, std::list<POINT> * lPoint);

	void changeTurn();
	void selectMal();
	void moveMal();
	void takeMal(JangGiMal*);
};

class JangGiMal
{
public:
	
private:
	int _x;	//말의 x위치
	int _y;	//말의 y위치

	const JANGGIMAL _kind;	//말의 종류
	const CAMP _camp;				//진영

	SpriteImage* _image;	//말 이미지

public:
	JangGiMal(int x, int y, JANGGIMAL mal, CAMP camp);
	~JangGiMal();

	void release();
	void render(HDC hdc);

	void move(POINT point);

	inline int getX(){ return _x; }
	inline int getY(){ return _y; }
	inline void setX(float x){ _x = x; }
	inline void setY(float y){ _y = y; }

	SpriteImage* getImage(){ return _image; }

	inline JANGGIMAL getKind(){ return _kind; }
	inline CAMP getCamp(){ return _camp; }

	const RECT getRect();
};