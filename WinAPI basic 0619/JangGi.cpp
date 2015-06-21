#include "stdafx.h"
#include "JangGi.h"

using namespace std;

inline float getCoorXByPointX(const long x){
	return WIN_SIZE_X / 2 + ((x - 4) * 55);
}
inline float getCoorYByPointY(const long y){
	return WIN_SIZE_Y / 2 + ((y - 4) * 50) - 25;
}
inline int changeCamp(int camp){
	return (camp + 1) & 1;
}
/****************************************** JangGi ******************************************/
JangGi::JangGi(){}
JangGi::~JangGi(){}
HRESULT JangGi::initialize(){
	_backImage = IMAGEMANAGER->findImage("janggi back");
	_backImage->setCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);

	_mal[0][0] = new JangGiMal(4, 1, KING, RED);
	_mal[0][1] = new JangGiMal(3, 0, OFFICER, RED);
	_mal[0][2] = new JangGiMal(5, 0, OFFICER, RED);
	_mal[0][3] = new JangGiMal(0, 0, CAR, RED);
	_mal[0][4] = new JangGiMal(8, 0, CAR, RED);
	_mal[0][5] = new JangGiMal(1, 0, HORSE, RED);
	_mal[0][7] = new JangGiMal(6, 0, HORSE, RED);
	_mal[0][6] = new JangGiMal(7, 0, ELEPHANT, RED);
	_mal[0][8] = new JangGiMal(2, 0, ELEPHANT, RED);
	_mal[0][9] = new JangGiMal(1, 2, CANNON, RED);
	_mal[0][10] = new JangGiMal(7, 2, CANNON, RED);
	_mal[0][11] = new JangGiMal(0, 3, SOLDIER, RED);
	_mal[0][12] = new JangGiMal(2, 3, SOLDIER, RED);
	_mal[0][13] = new JangGiMal(4, 3, SOLDIER, RED);
	_mal[0][14] = new JangGiMal(6, 3, SOLDIER, RED);
	_mal[0][15] = new JangGiMal(8, 3, SOLDIER, RED);

	_mal[1][0] = new JangGiMal(4, 8, KING, BLUE);
	_mal[1][1] = new JangGiMal(3, 9, OFFICER, BLUE);
	_mal[1][2] = new JangGiMal(5, 9, OFFICER, BLUE);
	_mal[1][3] = new JangGiMal(0, 9, CAR, BLUE);
	_mal[1][4] = new JangGiMal(8, 9, CAR, BLUE);
	_mal[1][5] = new JangGiMal(2, 9, HORSE, BLUE);
	_mal[1][7] = new JangGiMal(7, 9, HORSE, BLUE);
	_mal[1][6] = new JangGiMal(6, 9, ELEPHANT, BLUE);
	_mal[1][8] = new JangGiMal(1, 9, ELEPHANT, BLUE);
	_mal[1][9] = new JangGiMal(1, 7, CANNON, BLUE);
	_mal[1][10] = new JangGiMal(7, 7, CANNON, BLUE);
	_mal[1][11] = new JangGiMal(0, 6, SOLDIER, BLUE);
	_mal[1][12] = new JangGiMal(2, 6, SOLDIER, BLUE);
	_mal[1][13] = new JangGiMal(4, 6, SOLDIER, BLUE);
	_mal[1][14] = new JangGiMal(6, 6, SOLDIER, BLUE);
	_mal[1][15] = new JangGiMal(8, 6, SOLDIER, BLUE);

	for (int i = 0; i < 10; i++) for (int j = 0; j < 9; j++) _pan[i][j] = new JangGiPan(makeRectCenter(getCoorXByPointX(j), getCoorYByPointY(i), 30, 30));
	for (int i = 0; i < 2; i++) for (int j = 0; j < 16; j++) _pan[_mal[i][j]->getY()][_mal[i][j]->getX()]->mal = _mal[i][j];

	_turn = BLUE;
	_turnState = PLAY_TURN_START;

	_isGameEnd = false;

	return S_OK;
}
void JangGi::release(){
	for (int i = 0; i < 2; i++) for (int j = 0; j < 16; j++) SAFE_RELEASE(_mal[i][j]);
}
void JangGi::update(){
	if (_isGameEnd) return;
	switch (_turnState){
	case PLAY_TURN_START: selectMal(); break;
	case PLAY_MAL_CLICK: moveMal(); break;
	case PLAY_MAL_MOVE: changeTurn(); 
	case PLAY_MAL_MOVE_FAIL: _turnState = PLAY_TURN_START; break;
	}
}
list<POINT> JangGi::movablePoint(JangGiMal* mal){
	list<POINT> lPoint;
	if (mal->getKind() == ELEPHANT || mal->getKind() == HORSE) {
		int length;
		if (mal->getKind() == ELEPHANT) length = 3;
		else length = 2;
		addMovablePoint(mal->getX() - 1, mal->getY(), length, length, mal, &lPoint);
		addMovablePoint(mal->getX() - 1, mal->getY(), length, -length, mal, &lPoint);
		addMovablePoint(mal->getX() + 1, mal->getY(), -length, length, mal, &lPoint);
		addMovablePoint(mal->getX() + 1, mal->getY(), -length, -length, mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY() - 1, length, length, mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY() - 1, -length, length, mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY() + 1, length, -length, mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY() + 1, -length, -length, mal, &lPoint);
	} else if (mal->getKind() == KING || mal->getKind() == OFFICER || mal->getKind() == SOLDIER) {
		if (mal->getKind() == KING || mal->getKind() == OFFICER) 	{
			if ((mal->getCamp() == RED && mal->getY() < 2) || (mal->getCamp() == BLUE && mal->getY() < 9)) addMovablePoint(mal->getX(), mal->getY(), 0, 1, mal, &lPoint);
			if ((mal->getCamp() == RED && mal->getY() > 0) || (mal->getCamp() == BLUE && mal->getY() > 7)) addMovablePoint(mal->getX(), mal->getY(), 0, -1, mal, &lPoint);
			if (mal->getX() < 5) addMovablePoint(mal->getX(), mal->getY(), 1, 0, mal, &lPoint);
			if (mal->getX() > 3) addMovablePoint(mal->getX(), mal->getY(), -1, 0, mal, &lPoint);
			if ((mal->getCamp() == RED && mal->getY() == 2) || (mal->getCamp() == BLUE && mal->getY() == 9)){
				if (mal->getX() == 5) addMovablePoint(mal->getX(), mal->getY(), -1, -1, mal, &lPoint);
				else if (mal->getX() == 3) addMovablePoint(mal->getX(), mal->getY(), 1, -1, mal, &lPoint);
			} else if ((mal->getCamp() == RED && mal->getY() == 0) || (mal->getCamp() == BLUE && mal->getY() == 7)) {
				if (mal->getX() == 5) addMovablePoint(mal->getX(), mal->getY(), -1, 1, mal, &lPoint);
				else if (mal->getX() == 3) addMovablePoint(mal->getX(), mal->getY(), 1, 1, mal, &lPoint);
			} else if (mal->getX() == 4){
				addMovablePoint(mal->getX(), mal->getY(), 1, 1, mal, &lPoint);
				addMovablePoint(mal->getX(), mal->getY(), 1, -1, mal, &lPoint);
				addMovablePoint(mal->getX(), mal->getY(), -1, 1, mal, &lPoint);
				addMovablePoint(mal->getX(), mal->getY(), -1, -1, mal, &lPoint);
			}
		} else if (mal->getKind() == SOLDIER) {
			addMovablePoint(mal->getX(), mal->getY(), 0, ((mal->getCamp() == RED) ? 1 : -1), mal, &lPoint);
			addMovablePoint(mal->getX(), mal->getY(), 1, 0, mal, &lPoint);
			addMovablePoint(mal->getX(), mal->getY(), -1, 0, mal, &lPoint);
		}
	} else {
		if (mal->getKind() == CAR) {
			for (int i = 0; i < 9; i++) addMovablePoint(mal->getX(), mal->getY(), i - mal->getX(), 0, mal, &lPoint);
			for (int i = 0; i < 10; i++) addMovablePoint(mal->getX(), mal->getY(), 0, i - mal->getY(), mal, &lPoint);
			if (mal->getY() == 2 || mal->getY() == 9){
				if (mal->getX() == 5) {
					addMovablePoint(mal->getX(), mal->getY(), -1, -1, mal, &lPoint);
					addMovablePoint(mal->getX(), mal->getY(), -2, -2, mal, &lPoint);
				} else if (mal->getX() == 3) {
					addMovablePoint(mal->getX(), mal->getY(), 1, -1, mal, &lPoint);
					addMovablePoint(mal->getX(), mal->getY(), 2, -2, mal, &lPoint);
				}
			} else if (mal->getY() == 0 || mal->getY() == 7) {
				if (mal->getX() == 5) {
					addMovablePoint(mal->getX(), mal->getY(), -1, 1, mal, &lPoint);
					addMovablePoint(mal->getX(), mal->getY(), -2, 2, mal, &lPoint);
				} else if (mal->getX() == 3) {
					addMovablePoint(mal->getX(), mal->getY(), 1, 1, mal, &lPoint); 
					addMovablePoint(mal->getX(), mal->getY(), 2, 2, mal, &lPoint);
				}
			} else if (mal->getX() == 4){
				addMovablePoint(mal->getX(), mal->getY(), 1, 1, mal, &lPoint);
				addMovablePoint(mal->getX(), mal->getY(), 1, -1, mal, &lPoint);
				addMovablePoint(mal->getX(), mal->getY(), -1, 1, mal, &lPoint);
				addMovablePoint(mal->getX(), mal->getY(), -1, -1, mal, &lPoint);
			}
		} else if (mal->getKind() == CANNON) {
			for (int i = 0; i < 9; i++) addMovablePointByCannon(mal->getX(), mal->getY(), i - mal->getX(), 0, mal, &lPoint);
			for (int i = 0; i < 10; i++) addMovablePointByCannon(mal->getX(), mal->getY(), 0, i - mal->getY(), mal, &lPoint);
			if (mal->getY() == 2 || mal->getY() == 9){
				if (mal->getX() == 5) {
					addMovablePointByCannon(mal->getX(), mal->getY(), -2, -2, mal, &lPoint);
				} else if (mal->getX() == 3) {
					addMovablePointByCannon(mal->getX(), mal->getY(), 2, -2, mal, &lPoint);
				}
			} else if (mal->getY() == 0 || mal->getY() == 7) {
				if (mal->getX() == 5) {
					addMovablePointByCannon(mal->getX(), mal->getY(), -2, 2, mal, &lPoint);
				} else if (mal->getX() == 3) {
					addMovablePointByCannon(mal->getX(), mal->getY(), 2, 2, mal, &lPoint);
				}
			}
		}
	}
	return lPoint;
}
MOVABLE_STATE JangGi::checkMovablePoint(int startX, int startY, int endX, int endY, JangGiMal *mal){
	if (endX < 0 || endX > 8 || endY < 0 || endY > 9) return MOVABLE_NO_OUT;
	startX += (startX == endX) ? 0 : ((endX - startX) / abs(endX - startX));
	startY += (startY == endY) ? 0 : ((endY - startY) / abs(endY - startY));
	if ((startY == endY) && (startX == endX))
		if (_pan[startY][startX]->mal != NULL)
			if (_pan[startY][startX]->mal->getCamp() == mal->getCamp())
				if (_pan[startY][startX]->mal->getKind() == CANNON)	return MOVABLE_NO_SAME_CANNON;
				else return MOVABLE_NO_SAME;
			else
				if (_pan[startY][startX]->mal->getKind() == CANNON)	return MOVABLE_DIFF_CANNON;
				else return MOVABLE_DIFF;
		else return MOVABLE_EMPTY;
	else
		if (_pan[startY][startX]->mal != NULL) return MOVABLE_NO_BLOCKED;
		else return checkMovablePoint(startX, startY, endX, endY, mal);
}
MOVABLE_STATE JangGi::checkMovablePointByCannon(int startX, int startY, int endX, int endY, JangGiMal *mal, bool isExistWall){
	if (endX < 0 || endX > 8 || endY < 0 || endY > 9) return MOVABLE_NO_OUT;
	startX += (startX == endX) ? 0 : ((endX - startX) / abs(endX - startX));
	startY += (startY == endY) ? 0 : ((endY - startY) / abs(endY - startY));
	if (startX == endX && startY == endY)
		if (isExistWall)
			if (_pan[startY][startX]->mal != NULL)
				if (_pan[startY][startX]->mal->getCamp() == mal->getCamp()) return MOVABLE_NO_SAME;
				else
					if (_pan[startY][startX]->mal->getKind() == CANNON)	return MOVABLE_NO_OUT;
					else return MOVABLE_DIFF;
			else return MOVABLE_EMPTY;
		else return MOVABLE_NO_OUT;
	else
		if (isExistWall)
			if (_pan[startY][startX]->mal != NULL) return MOVABLE_NO_OUT;
			else return checkMovablePointByCannon(startX, startY, endX, endY, mal, true);
		else
			if (_pan[startY][startX]->mal != NULL)
				if (_pan[startY][startX]->mal->getKind() != CANNON) return checkMovablePointByCannon(startX, startY, endX, endY, mal, true);
				else return MOVABLE_NO_OUT;
			else return checkMovablePointByCannon(startX, startY, endX, endY, mal, false);
}
void JangGi::addMovablePoint(int malX, int malY, int moveX, int moveY, JangGiMal* mal, std::list<POINT> * lPoint){
	if (checkMovablePoint(malX, malY, malX + moveX, malY + moveY, mal) < 10) lPoint->push_back(makePoint(malX + moveX, malY + moveY));
}
void JangGi::addMovablePointByCannon(int malX, int malY, int moveX, int moveY, JangGiMal* mal, std::list<POINT> * lPoint){
	if (checkMovablePointByCannon(malX, malY, malX + moveX, malY + moveY, mal, false) < 10) lPoint->push_back(makePoint(malX + moveX, malY + moveY));
}
void JangGi::render(){
	_backImage->render(getMemDC(), (WIN_SIZE_X - _backImage->getWidth()) / 2, (WIN_SIZE_Y - _backImage->getHeight()) / 2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 16; j++) _mal[i][j]->render(getMemDC());
	for (list<POINT>::iterator liPoint = _movablePoint.begin(); liPoint != _movablePoint.end(); liPoint++) _selectMal->getImage()->render(getMemDC(), getCoorXByPointX(liPoint->x) - _selectMal->getImage()->getFrameWidth() / 2, getCoorYByPointY(liPoint->y) - _selectMal->getImage()->getFrameHeight() / 2, 100);
	if (_isGameEnd) TextOut(getMemDC(), WIN_SIZE_X / 2, WIN_SIZE_Y / 2, (_turn == RED ? "利铰" : "没铰"), strlen((_turn == RED ? "利铰" : "没铰")));
}
void JangGi::changeTurn(){
	_turn = (CAMP)changeCamp(_turn);
}
void JangGi::selectMal(){
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_backImage->boundingBox(), _mousePoint))
		for (int i = 0; i < 16; i++)
			if (PtInRect(&_mal[_turn][i]->getRect(), _mousePoint)){
				_selectMal = _mal[_turn][i];
				_movablePoint = movablePoint(_selectMal);
				_turnState = PLAY_MAL_CLICK;
				return;
			}
}
void JangGi::moveMal(){
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_backImage->boundingBox(), _mousePoint)){
		for (list<POINT>::iterator liPoint = _movablePoint.begin(); liPoint != _movablePoint.end(); liPoint++)
			if (PtInRect(&_pan[liPoint->y][liPoint->x]->rc, _mousePoint) && !(_selectMal->getY() == liPoint->y && _selectMal->getX() == liPoint->x)) {
				if (_pan[liPoint->y][liPoint->x]->mal != NULL) takeMal(_pan[liPoint->y][liPoint->x]->mal);
				_pan[_selectMal->getY()][_selectMal->getX()]->mal = NULL;
				_selectMal->move(makePoint(liPoint->x, liPoint->y));
				_pan[liPoint->y][liPoint->x]->mal = _selectMal;
				_movablePoint.clear();
				_turnState = PLAY_MAL_MOVE;
				return;
			}
		_movablePoint.clear();
		_turnState = PLAY_MAL_MOVE_FAIL;
	}
}
void JangGi::takeMal(JangGiMal* mal){
	mal->move((changeCamp(_turn) == RED) ? (makePoint(10, 9 - _takeMal[changeCamp(_turn)]++)) : (makePoint(-2, _takeMal[changeCamp(_turn)]++)));
	if (mal->getKind() == KING) _isGameEnd = true;
}
/****************************************** JangGiMal ******************************************/
JangGiMal::JangGiMal(const int x, const int y, const JANGGIMAL mal, const CAMP camp) : _x(x), _y(y), _kind(mal), _camp(camp){
	_image = IMAGEMANAGER->findImage("janggi mal")->createSprite(7, 2);
	_image->setFrameX(_kind);
	_image->setFrameY(_camp);
	_image->setCenter(getCoorXByPointX(_x), getCoorYByPointY(_y));
}
JangGiMal::~JangGiMal(){}
void JangGiMal::release(){
	SAFE_RELEASE(_image);
}
void JangGiMal::render(HDC hdc){
	_image->render(hdc);
}
void JangGiMal::move(POINT point){
	_x = point.x;
	_y = point.y;
	_image->setCenter(getCoorXByPointX(_x), getCoorYByPointY(_y));
}
const RECT JangGiMal::getRect(){
	return _image->getRect();
}