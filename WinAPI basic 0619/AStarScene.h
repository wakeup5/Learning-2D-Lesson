#pragma once
#include "SceneManager.h"
#include "AStarAlgorithms.h"

#define COL 20
#define ROW 20
#define WIDTH 39
#define HEIGHT 39

typedef struct tagNode
{
	int x, y;
	int f, g, h;
	tagNode* prev;
}Node;

typedef struct tagTile
{
	float x, y;
	RECT rc;
	bool movable;
}Tile;

class AStarScene : public Scene
{
private:
	//AStarAlgorithms<ROW, COL> _as;
	typedef set<Node*> NodeList;

	NodeList _open;
	NodeList _close;

	Node* _nodes[ROW][COL];

	Tile _tile[ROW][COL];

	POINT _start;
	POINT _end;
	POINT _current;


public:
	AStarScene();
	~AStarScene();

	HRESULT initialize();
	void release();
	void update();
	void render();

	void clearNode();

	void findRoad();

	void findOpen();
	Node* findMoreNearParents(int x, int y);

	bool isExistOpen(int x, int y);
	bool isExistClose(int x, int y);

	Node* getMinFNodeByOpen();
	Node* getMinFNodeByCurrent();

	int getDistance(const Node* const n1, const Node* const n2)
	{
		return (int)(sqrt(pow(n2->x - n1->x, 2) + pow(n2->y - n1->y, 2)) * 10);
	}
};

