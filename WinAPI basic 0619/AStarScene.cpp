#include "stdafx.h"
#include "AStarScene.h"


AStarScene::AStarScene()
{
}


AStarScene::~AStarScene()
{
}

HRESULT AStarScene::initialize()
{
	//타일 초기화, 타일 노드 초기화
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			_tile[i][j].movable = true;
			_tile[i][j].x = j * WIDTH + WIDTH / 2;
			_tile[i][j].y = i * HEIGHT + HEIGHT / 2;
			_tile[i][j].rc = makeRectCenter(_tile[i][j].x, _tile[i][j].y, WIDTH, HEIGHT);

			_nodes[i][j] = new Node;
			_nodes[i][j]->x = j;
			_nodes[i][j]->y = i;
			_nodes[i][j]->f = 0;
			_nodes[i][j]->g = 0;
			_nodes[i][j]->h = 0;
			_nodes[i][j]->prev = NULL;
		}
	}

	_start = makePoint(5, 2);
	_end = makePoint(5, 7);

	return S_OK;
}
void AStarScene::release()
{

}
void AStarScene::update()
{
	//start
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < ROW * COL; i++)
		{
			if (PtInRect(&_tile[i / COL][i % COL].rc, _mousePt))
			{
				_start = makePoint(i % COL, i / COL);// makePoint(_tile[i / COL][i % COL].x, _tile[i / COL][i % COL].y);
				break;
			}
		}
		clearNode();
	}
	//end
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < ROW * COL; i++)
		{
			if (PtInRect(&_tile[i / COL][i % COL].rc, _mousePt))
			{
				_end = makePoint(i % COL, i / COL);//makePoint(_tile[i / COL][i % COL].x, _tile[i / COL][i % COL].y);
				break;
			}
		}
		clearNode();
	}

	//벽생성
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		for (int i = 0; i < ROW * COL; i++)
		{
			if (PtInRect(&_tile[i / COL][i % COL].rc, _mousePt))
			{
				_tile[i / COL][i % COL].movable = false;
				break;
			}
		}
	}

	//벽 지움
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		for (int i = 0; i < ROW * COL; i++)
		{
			if (PtInRect(&_tile[i / COL][i % COL].rc, _mousePt))
			{
				_tile[i / COL][i % COL].movable = true;
				break;
			}
		}
	}

	//길 찾기
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		findRoad();
	}

	//벽 초기화
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		for (int i = 0; i < ROW * COL; i++)
		{
			_tile[i / COL][i % COL].movable = true;
		}
		clearNode();
	}
}
void AStarScene::render()
{
	//타일 출력
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (_tile[i][j].movable)
				Rectangle(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top, _tile[i][j].rc.right, _tile[i][j].rc.bottom);
		}
	}

	//오픈 출력
	HBRUSH orangeB = CreateSolidBrush(RGB(255, 255, 0));
	for (NodeList::iterator i = _open.begin(); i != _open.end(); i++)
	{
		FillRect(getMemDC(), &makeRectCenter(_tile[(*i)->y][(*i)->x].x, _tile[(*i)->y][(*i)->x].y, WIDTH, HEIGHT), orangeB);
	}
	DeleteObject(orangeB);

	//클로즈 출력
	HBRUSH greenB = CreateSolidBrush(RGB(0, 255, 0));
	for (NodeList::iterator i = _close.begin(); i != _close.end(); i++)
	{
		FillRect(getMemDC(), &makeRectCenter(_tile[(*i)->y][(*i)->x].x, _tile[(*i)->y][(*i)->x].y, WIDTH, HEIGHT), greenB);
	}
	DeleteObject(greenB);

	//이동경로 출력
	HBRUSH grayB = CreateSolidBrush(RGB(128, 128, 128));
	Node* node = _nodes[_end.y][_end.x];
	while ((node = node->prev) != NULL)
	{
		FillRect(getMemDC(), &makeRectCenter(_tile[node->y][node->x].x, _tile[node->y][node->x].y, WIDTH, HEIGHT), grayB);
	}
	DeleteObject(grayB);

	//벽 출력
	HBRUSH blackB = CreateSolidBrush(RGB(1, 1, 1));
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (!_tile[i][j].movable)
				FillRect(getMemDC(), &makeRectCenter(_tile[i][j].x, _tile[i][j].y, WIDTH, HEIGHT), blackB);
		}
	}
	DeleteObject(blackB);

	//시작점 출력
	HBRUSH redB = CreateSolidBrush(RGB(255, 0, 0));
	FillRect(getMemDC(), &makeRectCenter(_tile[_start.y][_start.x].x, _tile[_start.y][_start.x].y, WIDTH, HEIGHT), redB);
	DeleteObject(redB);
	//끝점 출력
	HBRUSH blueB = CreateSolidBrush(RGB(0, 0, 255));
	FillRect(getMemDC(), &makeRectCenter(_tile[_end.y][_end.x].x, _tile[_end.y][_end.x].y, WIDTH, HEIGHT), blueB);
	DeleteObject(blueB);
}

void AStarScene::findRoad()
{
	//노드 초기화
	clearNode();

	_current = _start;

	Node* startNode = _nodes[_current.y][_current.x];
	startNode->prev = NULL;
	_open.insert(startNode);

	Node* endNode = _nodes[_end.y][_end.y];

	//10만번 이내에 길 못찾으면 포기 - 최대 탐색 길이가 타일 갯수만큼이다..
	//int i = 0;
	while (!(_current.x == _end.x && _current.y == _end.y) && _open.size())
	{
		//이동한 자리의 노드를 open에서 제외하고 close에 넣음
		_open.erase(_open.find(_nodes[_current.y][_current.x]));
		_close.insert(_nodes[_current.y][_current.x]);

		//이동 가능한 주위 탐색하여 open에 넣음.
		findOpen();

		//f값이 가장 작은 노드찾음
		Node* minFNode = getMinFNodeByOpen();

		//open중 가장 낮은 노드를 찾지못하면(길이 막혀있으면)
		if (!minFNode) return;

		//current를 이동
		_current.x = minFNode->x;
		_current.y = minFNode->y;
	}
}

void AStarScene::findOpen()
{
	//8방향 1칸씩 찾기위함
	int sX = (_current.x > 0) ? _current.x - 1 : 0;
	int sY = (_current.y > 0) ? _current.y - 1 : 0;
	int eX = (_current.x < COL - 1) ? _current.x + 1 : COL - 1;
	int eY = (_current.y < ROW - 1) ? _current.y + 1 : ROW - 1;

	for (int y = sY; y <= eY; y++)
	{
		for (int x = sX; x <= eX; x++)
		{
			//해당 칸이 벽일경우 넘김
			//해당 칸이 close에 있을 경우 넘김
			if (isExistClose(x, y) || !_tile[y][x].movable)
			{
				continue;
			}

			//해당 칸이 open에 있을 경우.
			if (isExistOpen(x, y))
			{
				//해당 칸에서 인접한 블럭에서 스타트 블럭에 가까운 블럭이 있으면 부모를 바꿈.
				//_nodes[y][x]->prev = findMoreNearParents(x, y);

				if (_nodes[_current.y][_current.x]->g < _nodes[y][x]->prev->g)
				{
					_nodes[y][x]->prev = _nodes[_current.y][_current.x];
					_nodes[y][x]->g = _nodes[y][x]->prev->g + getDistance(_nodes[y][x], _nodes[y][x]->prev); //g값 설정
				}
				continue;
			}

			//새로운 칸일 경우
			_nodes[y][x]->prev = _nodes[_current.y][_current.x]; //부모칸 설정
			_nodes[y][x]->g = _nodes[y][x]->prev->g + getDistance(_nodes[y][x], _nodes[y][x]->prev); //g값 설정
			_nodes[y][x]->h = (abs(y - _end.y) + abs(x - _end.x)) * 10; //h값 설정
			_nodes[y][x]->f = _nodes[y][x]->g + _nodes[y][x]->h; //값 합산

			_open.insert(_nodes[y][x]);
		}
	}
}

bool AStarScene::isExistOpen(int x, int y)
{
	if (_open.find(_nodes[y][x]) != _open.end())
	{
		return true;
	}

	return false;
}

bool AStarScene::isExistClose(int x, int y)
{
	if (_close.find(_nodes[y][x]) != _close.end())
	{
		return true;
	}

	return false;
}

Node* AStarScene::getMinFNodeByOpen()
{
	Node* result = NULL;

	for (NodeList::iterator i = _open.begin(); i != _open.end(); i++)
	{
		if (result == NULL || result->f > (*i)->f)
		{
			result = *i;
		}
	}

	return result;
}

Node* AStarScene::getMinFNodeByCurrent()
{
	Node* result = NULL;

	int sX = (_current.x > 0) ? _current.x - 1 : 0;
	int sY = (_current.y > 0) ? _current.y - 1 : 0;
	int eX = (_current.x < COL - 1) ? _current.x + 1 : COL - 1;
	int eY = (_current.y < ROW - 1) ? _current.y + 1 : ROW - 1;

	for (int y = sY; y <= eY; y++)
	{
		for (int x = sX; x <= eX; x++)
		{
			if (_nodes[y][x]->prev != _nodes[_current.y][_current.x]) continue;

			if (result == NULL || result->g > _nodes[y][x]->g)
			{
				result = _nodes[y][x];
			}
		}
	}

	return result;
}

void AStarScene::clearNode()
{
	_open.clear();
	_close.clear();

	//노드 링크 초기화
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			_nodes[i][j]->prev = NULL;
			_nodes[i][j]->g = 0;
			_nodes[i][j]->f = 0;
			_nodes[i][j]->h = 0;
		}
	}
}

Node* AStarScene::findMoreNearParents(int ix, int iy)
{
	Node* result = NULL;

	int sX = (ix > 0) ? ix - 1 : 0;
	int sY = (iy > 0) ? iy - 1 : 0;
	int eX = (ix < COL - 1) ? ix + 1 : COL - 1;
	int eY = (iy < ROW - 1) ? iy + 1 : ROW - 1;

	for (int y = sY; y <= eY; y++)
	{
		for (int x = sX; x <= eX; x++)
		{
			if (isExistOpen(x, y) || isExistClose(x, y))
			{
				if (result == NULL || result->g > _nodes[y][x]->g)
				{
					result = _nodes[y][x];
				}
			}
		}
	}

	return result;
}