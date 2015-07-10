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
	//Ÿ�� �ʱ�ȭ, Ÿ�� ��� �ʱ�ȭ
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

	//������
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

	//�� ����
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

	//�� ã��
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		findRoad();
	}

	//�� �ʱ�ȭ
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
	//Ÿ�� ���
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (_tile[i][j].movable)
				Rectangle(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top, _tile[i][j].rc.right, _tile[i][j].rc.bottom);
		}
	}

	//���� ���
	HBRUSH orangeB = CreateSolidBrush(RGB(255, 255, 0));
	for (NodeList::iterator i = _open.begin(); i != _open.end(); i++)
	{
		FillRect(getMemDC(), &makeRectCenter(_tile[(*i)->y][(*i)->x].x, _tile[(*i)->y][(*i)->x].y, WIDTH, HEIGHT), orangeB);
	}
	DeleteObject(orangeB);

	//Ŭ���� ���
	HBRUSH greenB = CreateSolidBrush(RGB(0, 255, 0));
	for (NodeList::iterator i = _close.begin(); i != _close.end(); i++)
	{
		FillRect(getMemDC(), &makeRectCenter(_tile[(*i)->y][(*i)->x].x, _tile[(*i)->y][(*i)->x].y, WIDTH, HEIGHT), greenB);
	}
	DeleteObject(greenB);

	//�̵���� ���
	HBRUSH grayB = CreateSolidBrush(RGB(128, 128, 128));
	Node* node = _nodes[_end.y][_end.x];
	while ((node = node->prev) != NULL)
	{
		FillRect(getMemDC(), &makeRectCenter(_tile[node->y][node->x].x, _tile[node->y][node->x].y, WIDTH, HEIGHT), grayB);
	}
	DeleteObject(grayB);

	//�� ���
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

	//������ ���
	HBRUSH redB = CreateSolidBrush(RGB(255, 0, 0));
	FillRect(getMemDC(), &makeRectCenter(_tile[_start.y][_start.x].x, _tile[_start.y][_start.x].y, WIDTH, HEIGHT), redB);
	DeleteObject(redB);
	//���� ���
	HBRUSH blueB = CreateSolidBrush(RGB(0, 0, 255));
	FillRect(getMemDC(), &makeRectCenter(_tile[_end.y][_end.x].x, _tile[_end.y][_end.x].y, WIDTH, HEIGHT), blueB);
	DeleteObject(blueB);
}

void AStarScene::findRoad()
{
	//��� �ʱ�ȭ
	clearNode();

	_current = _start;

	Node* startNode = _nodes[_current.y][_current.x];
	startNode->prev = NULL;
	_open.insert(startNode);

	Node* endNode = _nodes[_end.y][_end.y];

	//10���� �̳��� �� ��ã���� ���� - �ִ� Ž�� ���̰� Ÿ�� ������ŭ�̴�..
	//int i = 0;
	while (!(_current.x == _end.x && _current.y == _end.y) && _open.size())
	{
		//�̵��� �ڸ��� ��带 open���� �����ϰ� close�� ����
		_open.erase(_open.find(_nodes[_current.y][_current.x]));
		_close.insert(_nodes[_current.y][_current.x]);

		//�̵� ������ ���� Ž���Ͽ� open�� ����.
		findOpen();

		//f���� ���� ���� ���ã��
		Node* minFNode = getMinFNodeByOpen();

		//open�� ���� ���� ��带 ã�����ϸ�(���� ����������)
		if (!minFNode) return;

		//current�� �̵�
		_current.x = minFNode->x;
		_current.y = minFNode->y;
	}
}

void AStarScene::findOpen()
{
	//8���� 1ĭ�� ã������
	int sX = (_current.x > 0) ? _current.x - 1 : 0;
	int sY = (_current.y > 0) ? _current.y - 1 : 0;
	int eX = (_current.x < COL - 1) ? _current.x + 1 : COL - 1;
	int eY = (_current.y < ROW - 1) ? _current.y + 1 : ROW - 1;

	for (int y = sY; y <= eY; y++)
	{
		for (int x = sX; x <= eX; x++)
		{
			//�ش� ĭ�� ���ϰ�� �ѱ�
			//�ش� ĭ�� close�� ���� ��� �ѱ�
			if (isExistClose(x, y) || !_tile[y][x].movable)
			{
				continue;
			}

			//�ش� ĭ�� open�� ���� ���.
			if (isExistOpen(x, y))
			{
				//�ش� ĭ���� ������ ������ ��ŸƮ ���� ����� ���� ������ �θ� �ٲ�.
				//_nodes[y][x]->prev = findMoreNearParents(x, y);

				if (_nodes[_current.y][_current.x]->g < _nodes[y][x]->prev->g)
				{
					_nodes[y][x]->prev = _nodes[_current.y][_current.x];
					_nodes[y][x]->g = _nodes[y][x]->prev->g + getDistance(_nodes[y][x], _nodes[y][x]->prev); //g�� ����
				}
				continue;
			}

			//���ο� ĭ�� ���
			_nodes[y][x]->prev = _nodes[_current.y][_current.x]; //�θ�ĭ ����
			_nodes[y][x]->g = _nodes[y][x]->prev->g + getDistance(_nodes[y][x], _nodes[y][x]->prev); //g�� ����
			_nodes[y][x]->h = (abs(y - _end.y) + abs(x - _end.x)) * 10; //h�� ����
			_nodes[y][x]->f = _nodes[y][x]->g + _nodes[y][x]->h; //�� �ջ�

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

	//��� ��ũ �ʱ�ȭ
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