#pragma once
#include "GameNode.h"
typedef enum JANGGIMAL{	//���� ����
	KING = 0, CANNON, ELEPHANT, HORSE, CAR, OFFICER, SOLDIER
};
typedef enum CAMP{	//������ ����
	RED = 0, BLUE
};
typedef enum JANGGI_TURN_STATE{	//���� ���� ����
	PLAY_TURN_START = 0, PLAY_MAL_CLICK, PLAY_MAL_MOVE, PLAY_MAL_MOVE_FAIL, PLAY_TURN_END
} TurnState;
class JangGiMal;
class JangGi : public GameNode{
private:
	typedef struct tagJangGiPan	{
		RECT rc;
		JangGiMal* mal;
		tagJangGiPan(RECT r) :rc(r), mal(NULL){}
	} JangGiPan;
	Image* _backImage;		//����� �̹���
	JangGiMal* _mal[2][16];	//���� ������ ����
	JangGiPan* _pan[10][9];	//�̵� ������ ��� ��ġ�� ������ ����
	CAMP _turn;				//��� ������ ���̴�
	TurnState _turnState;	//���� ����
	JangGiMal* _selectMal;	//������ ��
	std::list<POINT> _movablePoint;	//������ ���� �̵������� ����Ʈ��
	int _takeMal[2];		//���� ���� ����
	bool _isGameEnd;		//���� ��?
	bool _isJangGun;		//�屺?
	CAMP _jangGunCamp;		//���� �屺�޾Ҵ�?
public:
	JangGi();
	~JangGi(){}
	HRESULT initialize();
	void release();
	void update();
	void render();
	std::list<POINT> movablePoint(JangGiMal* mal);	//���� ��ġ�� ������ ���� �̵� ������ ��ǥ���� ����
	bool checkMovablePoint(int startX, int startY, int endX, int endY, JangGiMal *mal);	//���� ���� ���� ������������ ���������� �̵� ���������� ����
	void addMovablePoint(int malX, int malY, int endX, int endY, JangGiMal* mal, std::list<POINT> * lPoint); //���� ��ġ���� �̵��� ��� ��ġ�� �Է��� �̵� �����ϸ� �ش� �����ǥ�� ����Ʈ�� ���� 
	bool checkMovablePointByCannon(int startX, int startY, int endX, int endY, JangGiMal *mal, bool isExistWall); //�� ����
	void changeTurn();	//�� �ٲ�. �屺 ���ε� �Ǵ�
	void selectMal();	//������
	void moveMal();		//�� ������
	void takeMal(JangGiMal*);	//�� ����
};
class JangGiMal{
private:
	int _x, _y;	//���� x, y��ġ
	const JANGGIMAL _kind;	//���� ����
	const CAMP _camp;				//����
	SpriteImage* _image;	//�� �̹���
public:
	JangGiMal(int x, int y, JANGGIMAL mal, CAMP camp);
	~JangGiMal(){}
	void release();
	void move(POINT point);
	inline int getX(){ return _x; }
	inline int getY(){ return _y; }
	inline void setX(float x){ _x = x; }
	inline void setY(float y){ _y = y; }
	SpriteImage* getImage(){ return _image; }
	inline JANGGIMAL getKind(){ return _kind; }
	inline CAMP getCamp(){ return _camp; }
};