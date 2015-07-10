#pragma once
#include <set>

template < int r, int c >
struct Tiles
{
	bool movableTiles[r][c];
	int col = c;
	int row = r;
};

template < typename T, int row, int col >
struct SetMovableTile
{
	bool operator () (T tiles[row][col], int x, int y)
	{
		return (bool)tiles[y][x];
	}
};

template < int row, int col >
class AStarAlgorithms
{
private:
	typedef struct tagNode
	{
		int x, y;
		int f, g, h;
		tagNode* prev;
	}Node;

	typedef vector<Node*> NodeList;
	typedef vector<POINT> CoorList;

	Tiles<row, col> _tile;

	NodeList _open;
	NodeList _close;

	Node* _currentNode;
	Node* _startNode;
	Node* _endNode;

public:
	AStarAlgorithms()
	{

	}
	~AStarAlgorithms()
	{

	}

	void setStart(int x, int y)
	{
		if (_startNode) SAFE_DELETE(_startNode);

		_startNode = new Node;
		_startNode->x = x;
		_startNode->y = y;
		_startNode->prev = NULL;
	}
	void setEnd(int x, int y)
	{
		if (_endNode) SAFE_DELETE(_endNode);

		_endNode = new Node;
		_endNode->x = x;
		_endNode->y = y;
		_endNode->prev = NULL;
	}

	CoorList result()
	{
		CoorList result;
		_currentNode = _startNode;

		if (!_startNode || !_endNode) return result;

		_open.clear();
		_close.clear();

		_close.push_back(_currentNode);

		while (_currentNode != _endNode)
		{
			int startX = _currentNode->x - 1;
			int startY = _currentNode->y - 1;
			int endX = _currentNode->x + 1;
			int endY = _currentNode->y + 1;

			if (startX < 0) startX = 0;
			if (startY < 0) startY = 0;
			if (endX > col) endX = col;
			if (endY > row) endY = row;

			for (int i = startY; i <= endY; i++)
			{
				for (int j = startX; j <= endX; j++)
				{
					bool isExist = false;

					for (int k = 0; k < _close.size(); k++)
					{
						if (_close[k]->y == i && _close[k]->x == j)
						{
							isExist = true;
						}
					}

					if (isExist) continue;

					Node* node = NULL;

					if (_endNode->x == j && _endNode->y == i)
					{
						node = _endNode;
					}
					else
					{
						node = new Node;
					}

					node->x = j;
					node->y = i;
					node->prev = _currentNode;
					node->g = getDistanse(_currentNode->x, _currentNode->y, j, i);
					node->h = getDistanse(_endNode->x, _endNode->y, j, i);
					node->f = node->g + node->h;

					_open.push_back(node);
				}
			}
			
			Node* node1 = NULL;
			int num = 0;
			for (int i = 0; i < _open.size(); i++)
			{
				if (node1 == NULL || node1->f < _open[i]->f)
				{
					_currentNode = node1 = _open[i];
					num = i;
				}
			}

			if (node1 != NULL)
			{
				_close.push_back(node1);
				_open.erase(_open.begin() + num);
			}

			printf("%d, %d\n", _currentNode->x, _currentNode->y);
			Sleep(100);
		}

		return result;
	}

	Node* getEndNode()
	{
		return _endNode;
	}

	int getDistanse(int x1, int y1, int x2, int y2)
	{
		return (int)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}

	template <typename T, class oper = SetMovableTile<T, row, col>>
	Tiles<row, col> setMovableTile(T tiles[row][col])
	{
		bool tile[row][col];
		Tiles<row, col> tileInfo;

		oper o;

		//tileInfo.movableTiles = new bool*[row];
		for (int i = 0; i < row; i++)
		{
			//tileInfo.movableTiles[i] = new bool[col];
			for (int j = 0; j < col; j++)
			{
				tileInfo.movableTiles[i][j] = tile[i][j] = o(tiles, j, i);
			}
			//tileInfo.movableTiles[i] = tile[i];
		}


		tileInfo.col = col;
		tileInfo.row = row;
		//tileInfo.movableTiles = tile;

		_tile = tileInfo;

		return tileInfo;
	}
};

