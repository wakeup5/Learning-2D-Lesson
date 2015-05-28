#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	_mapImage = new Image();
	_mapImage->initialize("map.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_background = new Image;
	_background->initialize("resource/11.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_puzzleImage = new Image;
	_puzzleImage->initialize("resource/puzzle.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_pieceWidth = WIN_SIZE_X / PUZZLE_COL;
	_pieceHeight = WIN_SIZE_Y / PUZZLE_ROW;

	gameInit();

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	_mapImage->release();
	_background->release();

	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();
	if (!_isGameStart && //게임 시작중이 아니고
		PtInRect(&makeRect(0, 0, WIN_SIZE_X, WIN_SIZE_Y), _mousePoint) && //마우스가 화면 안에 있고
		KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) //클릭하면
	{
		_isGameStart = true; //게임 시작
		for (int i = 0; i < 500 * PUZZLE_LENGTH; i++)
		{
			puzzleSwap(RANDOM->getInt(PUZZLE_LENGTH));
		}

		puzzleSwap(((_voidNum / PUZZLE_COL) * PUZZLE_COL) + PUZZLE_COL - 1);
		puzzleSwap(PUZZLE_LENGTH - 1);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < PUZZLE_LENGTH; i++)
		{
			if (PtInRect(&_puzzleRect[i], _mousePoint))
			{
				puzzleSwap(i);
			}
		}
	}

	//다 맞추었는지 확인
	for (int i = 1; i < PUZZLE_LENGTH; i++)
	{
		if (_puzzleNum[i - 1] > _puzzleNum[i]) break;

		if (i == PUZZLE_LENGTH - 1) _isGameStart = false;
	}

}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	_mapImage->render(backDC, 0, 0);
	_background->render(backDC);

	if (!_isGameStart)
	{
		_puzzleImage->render(backDC);
	}
	else
	{
		
		for (int i = 0; i < PUZZLE_LENGTH; i++)
		{
			drawRectangle(backDC, _puzzleRect[i]);
			
			if (i == _voidNum) continue;

			_puzzleImage->render(backDC, 
				((i % PUZZLE_COL) * _pieceWidth) + 1,
				((i / PUZZLE_COL) * _pieceHeight) + 1,
				((_puzzleNum[i] % PUZZLE_COL) * _pieceWidth) + 1,
				((_puzzleNum[i] / PUZZLE_COL) * _pieceHeight) + 1,
				_pieceWidth - 2, _pieceHeight - 2);
			

			/*
			TCHAR numStr[128];
			sprintf_s(numStr, "%d", _puzzleNum[i]);
			TextOut(backDC, (i % PUZZLE_COL) * _pieceWidth, (i / PUZZLE_COL) * _pieceHeight, numStr, _tcslen(numStr));
			*/
		}

		/*
		for (int i = 0; i < PUZZLE_LENGTH; i++)
		{
			TCHAR numStr[128];
			sprintf_s(numStr, "%d", _puzzleNum[i]);
			TextOut(backDC, (i % PUZZLE_COL) * _pieceWidth, (i / PUZZLE_COL) * _pieceHeight, numStr, _tcslen(numStr));
		}
		*/
		
	}

	TCHAR voidNumStr[128];
	sprintf_s(voidNumStr, "%d", _voidNum);
	TextOut(backDC, 10, 10, voidNumStr, _tcslen(voidNumStr));

	this->getBackBuffer()->render(hdc, 0, 0);
}

//게임 초기화
void GameStudy::gameInit()
{
	for (int i = 0; i < PUZZLE_LENGTH; i++)
	{
		_puzzleNum[i] = i;
		_puzzleRect[i] = makeRect((i % PUZZLE_COL) * _pieceWidth, (i / PUZZLE_COL) * _pieceHeight, _pieceWidth, _pieceHeight);
	}
	_voidNum = RANDOM->getInt(PUZZLE_LENGTH);
}

void GameStudy::puzzleSwap(int clickNum)
{
	/*
	퍼즐 배열이 1차원 배열이고, 내용 값이 0부터 갯수 - 1까지 있을때 작동.
	diff는 몇칸 차이나는지의 수.
	예) 빈 곳의 위 두칸을 클릭하며 diff는 2, 왼쪽 5칸을 누르면 5, 한칸옆이면 1
	direction는 클릭한 곳의 방향의 한칸의 숫자 차이
	-가로갯수를 해주면 위 한칸이다.
	예)3 * 3에서 한 가운데 자리(4)에서 위 한칸으로 가려면 -가로갯수(3)을 하면 위(1)칸이다.
	*/

	if (_voidNum == clickNum) return;

	int diff;
	int direction;
	//같은 세로줄이면서 클릭한 곳이 빈곳보다 위일때
	if (clickNum < _voidNum && (clickNum % PUZZLE_COL) == (_voidNum % PUZZLE_COL))//빈 곳 위쪽
	{
		diff = (_voidNum - clickNum) / PUZZLE_COL;
		direction = -PUZZLE_COL;
	}
	//같은 세로줄이면서 클릭한 곳이 빈곳보다 아래일때
	else if (clickNum > _voidNum && (clickNum % PUZZLE_COL) == (_voidNum % PUZZLE_COL))//아래쪽
	{
		diff = (clickNum - _voidNum) / PUZZLE_COL;
		direction = PUZZLE_COL;
	}
	//같은 가로줄이면서 클릭한 곳이 빈곳보다 왼쪽일때
	else if (clickNum < _voidNum && (clickNum / PUZZLE_COL) == (_voidNum / PUZZLE_COL))//왼쪽
	{
		diff = (_voidNum - clickNum);
		direction = -1;
	}
	//같은 가로줄이면서 클릭한 곳이 빈곳보다 오른쪽일때
	else if (clickNum > _voidNum && (clickNum / PUZZLE_COL) == (_voidNum / PUZZLE_COL))//오른쪽
	{
		diff = (clickNum - _voidNum);
		direction = 1;
	}
	//같은 가로, 세로줄이 아니면 아무것도 안함.
	//즉 어디든 클릭은 가능하나 바뀌지 않음
	else
	{
		return;
	}

	//빈곳의 거리가 1칸이면 1회, 3칸이면 3번 반복
	while (diff-- != 0)
	{
		int temp;
		int swapNum = _voidNum + direction;

		temp = _puzzleNum[_voidNum];
		_puzzleNum[_voidNum] = _puzzleNum[swapNum];
		_puzzleNum[swapNum] = temp;

		_voidNum = swapNum;
	}
}
//숙제
// 3 * 3 퍼즐
//기본 3 * 3인데 가로 세로 갯수 자유롭게 설정 가능
//우측 아래에 빈 곳
//섞기전에 그림이 전부 보이고, 섞기 누르면 빈 곳이 생김
//이미지를 실제로 자르면 안되고 통짜 이미지를 넣고 뿌릴때 자름
//맞출수 있어야 한다.
//직선상 어디를 클릭해도 한번에 이동 된다.