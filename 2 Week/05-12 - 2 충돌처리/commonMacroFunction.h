/** commonMacroFunction
@file	commonMacroFunction.h
@author	박진한(wlsgks5@naver.com)
@date	2015/05/12
@brief	간편하게 사용할 인라인 매크로 함수들 선언.
*/
#include "stdafx.h"

/** makePoint 좌표를 입력하면 포인트 변수를 만들어 리턴
@date	2015/05/12
@param	x x좌표
@param	y y좌표
@return	POINT
*/
inline POINT makePoint(int x, int y)
{
	return POINT{ x, y };
}

/** makeRect 좌표와 폭을 입력하면 Rect를 만들어 리턴
@date	2015/05/12
@param	int x left
@param	int y top
@param	int width 폭
@param	int height 높이
@return	RECT
*/
inline RECT makeRect(int x, int y, int width, int height)
{
	return RECT{ x, y, x + width, y + height };
}

/** makeRectCenter 중심 좌표를 중심으로 Rect를 만들어 리턴
@date	2015/05/12
@param	int centerX 중심 x좌표
@param	int centerY 중심 y좌표
@param	int width 폭
@param	int height 높이
@return	RECT
*/
inline RECT makeRectCenter(int centerX, int centerY, int width, int height)
{
	return RECT{ centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2) };
}

/** drawLine 좌표를 입력받아 선을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int x1 시작 x좌표
@param	int y1 시작 y좌표
@param	int x2 끝 x좌표
@param	int y2 끝 y좌표
*/
inline void drawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

/** drawLines 여러 좌표들을 받아 여러개의 선을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	vector<POINT> 여러개의 포인터들
*/
inline void drawLines(HDC hdc, std::vector<POINT> pointVector)
{
	std::vector<POINT>::iterator iter;

	for (iter = pointVector.begin(); iter != pointVector.end(); iter++)
	{
		if (iter == pointVector.begin()) MoveToEx(hdc, iter->x, iter->y, NULL);
		else LineTo(hdc, iter->x, iter->y);
	}
}

/** drawRectangle 좌표와 크기를 입력받아 사각형을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int x left
@param	int y top
@param	int width 폭
@param	int height 높이
*/
inline void drawRectangle(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

/** drawRectangle RECT를 입력받아 사각형을 그린다.
@date	2015/05/12
@brief	RECT를 받기 때문에 left, top, right, bottom 기준으로 입력 받는다.
@param	HDC 윈도우 dc의 핸들
@param	RECT 
*/
inline void drawRectangle(HDC hdc, RECT r)
{
	Rectangle(hdc, r.left, r.top, r.right, r.bottom);
}

/** drawRectangleCenter 좌표를 중심으로 사각형을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int centerX 중심 좌표 x
@param	int centerY 중심 좌표 y
@param	int width 폭
@param	int height 높이
*/
inline void drawRectangleCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
}

/** drawEllipse 좌표와 크기를 받아 중심으로 원을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int x left
@param	int y top
@param	int width 폭
@param	int height 높이
*/
inline void drawEllipse(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

/** drawEllipse RECT를 받아 중심으로 원을 그린다.
@date	2015/05/12
@brief	RECT를 받기 때문에 left, top, right, bottom 기준으로 입력 받는다.
@param	HDC 윈도우 dc의 핸들
@param	RECT
*/
inline void drawEllipse(HDC hdc, RECT r)
{
	Ellipse(hdc, r.left, r.top, r.right, r.bottom);
}

/** drawEllipseCenter 좌표를 중심으로 원을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int centerX 중심 좌표 x
@param	int centerY 중심 좌표 y
@param	int width 폭
@param	int height 높이
*/
inline void drawEllipseCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Ellipse(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
}

/** checkInRect POINT가 RECT 내에 있는지 체크. 충돌 체크
@date	2015/05/12
@param	POINT
@param	RECT
@return	bool 안에 존재하는지의 여부
*/
inline bool checkInRect(POINT point, RECT rect)
{
	if (rect.left < point.x &&
		rect.right >= point.x && 
		rect.top < point.y && 
		rect.bottom >= point.y)
		return true;
	else
		return false;
}