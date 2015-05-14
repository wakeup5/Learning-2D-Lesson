/** commonMacroFunction
@file	commonMacroFunction.h
@author	������(wlsgks5@naver.com)
@date	2015/05/12
@brief	�����ϰ� ����� �ζ��� ��ũ�� �Լ��� ����.
*/
#include "stdafx.h"

/* ================================================================================
 * ===========================  ## ����ü ##  ======================================
 * ================================================================================*/

/** POINTRECT POINT�� RECT�� ����
@date	2015/05/13
*/
typedef struct tagPointRect
{
	POINT point;
	RECT rect;
} POINTRECT;

/* ================================================================================
 * ===========================  ## ��ǥ ���� �Լ� ##  ===============================
 * ================================================================================ */

/** makePoint ��ǥ�� �Է��ϸ� ����Ʈ ������ ����� ����
@date	2015/05/12
@param	x x��ǥ
@param	y y��ǥ
@return	POINT
*/
inline POINT makePoint(int x, int y)
{
	return POINT{ x, y };
}

/** makeRect ��ǥ�� ���� �Է��ϸ� Rect�� ����� ����
@date	2015/05/12
@param	int x left
@param	int y top
@param	int width ��
@param	int height ����
@return	RECT
*/
inline RECT makeRect(int x, int y, int width, int height)
{
	return RECT{ x, y, x + width, y + height };
}

/** makeRectCenter �߽� ��ǥ�� �߽����� Rect�� ����� ����
@date	2015/05/12
@param	int centerX �߽� x��ǥ
@param	int centerY �߽� y��ǥ
@param	int width ��
@param	int height ����
@return	RECT
*/
inline RECT makeRectCenter(int centerX, int centerY, int width, int height)
{
	return RECT{ centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2) };
}

/** makeRectCenter �߽� ��ǥPOINT�� �߽����� Rect�� ����� ����
@date	2015/05/13
@param	POINT x, y �߽� ��ǥ POINT
@param	int width ��
@param	int height ����
@return	RECT
*/
inline RECT makeRectCenter(POINT p, int width, int height)
{
	return makeRectCenter(p.x, p.y, width, height);//RECT{ p.x - (width / 2), p.y - (height / 2), p.x + (width / 2), p.y + (height / 2) };
}

/** makeRectCenter ���콺 ��ǥ�� �Է� �޾� ����Ʈ�� ����
@date	2015/05/13
@param	LPARAM
@return	POINT
*/
inline POINT makeMousePoint(LPARAM lParam)
{
	return POINT{ static_cast<int>(LOWORD(lParam)), static_cast<int>(HIWORD(lParam)) };
}

/** makePointRectCenter �߽���ǥ�� ũ�⸦ �Է¹޾� POINT�� RECT�� ���Ե� ����ü�� ����
@date	2015/05/13
@param	int centerX �߽� x��ǥ
@param	int centerY �߽� y��ǥ
@param	int width ��
@param	int height ����
@return	POINTRECT
*/
inline POINTRECT makePointRectCenter(int centerX, int centerY, int width, int height)
{
	return POINTRECT{ makePoint(centerX, centerY), makeRectCenter(centerX, centerY, width, height) };
}

/** makePointRectCenter �߽���ǥ�� ũ�⸦ �Է¹޾� POINT�� RECT�� ���Ե� ����ü�� ����
@date	2015/05/13
@param	POINT �߽���ǥ POINT
@param	int width ��
@param	int height ����
@return	POINTRECT
*/
inline POINTRECT makePointRectCenter(POINT p, int width, int height)
{
	return POINTRECT{ p, makeRectCenter(p.x, p.y, width, height) };
}


/* ================================================================================
* ===========================  ## ���� �׸��� �Լ� ##  =============================
* ================================================================================ */

/** drawLine ��ǥ�� �Է¹޾� ���� �׸���.
@date	2015/05/12
@param	HDC ������ dc�� �ڵ�
@param	int x1 ���� x��ǥ
@param	int y1 ���� y��ǥ
@param	int x2 �� x��ǥ
@param	int y2 �� y��ǥ
*/
inline void drawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

/** drawLines ���� ��ǥ���� �޾� �������� ���� �׸���.
@date	2015/05/12
@param	HDC ������ dc�� �ڵ�
@param	vector<POINT> �������� ����Ʈ��
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

/** drawRectangle ��ǥ�� ũ�⸦ �Է¹޾� �簢���� �׸���.
@date	2015/05/12
@param	HDC ������ dc�� �ڵ�
@param	int x left
@param	int y top
@param	int width ��
@param	int height ����
*/
inline void drawRectangle(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

/** drawRectangle RECT�� �Է¹޾� �簢���� �׸���.
@date	2015/05/12
@brief	RECT�� �ޱ� ������ left, top, right, bottom �������� �Է� �޴´�.
@param	HDC ������ dc�� �ڵ�
@param	RECT
*/
inline void drawRectangle(HDC hdc, RECT r)
{
	Rectangle(hdc, r.left, r.top, r.right, r.bottom);
}

/** drawRectangleCenter ��ǥ�� �߽����� �簢���� �׸���.
@date	2015/05/12
@param	HDC ������ dc�� �ڵ�
@param	int centerX �߽� ��ǥ x
@param	int centerY �߽� ��ǥ y
@param	int width ��
@param	int height ����
*/
inline void drawRectangleCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
}

/** drawRectangleCenter ��ǥ�� �߽����� �簢���� �׸���.
@date	2015/05/13
@param	HDC ������ dc�� �ڵ�
@param	POINT x, y �߽� ��ǥ POINT
@param	int width ��
@param	int height ����
*/
inline void drawRectangleCenter(HDC hdc, POINT p, int width, int height)
{
	//Rectangle(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
	drawRectangleCenter(hdc, p.x, p.y, width, height);
}

/** drawEllipse ��ǥ�� ũ�⸦ �޾� �߽����� ���� �׸���.
@date	2015/05/12
@param	HDC ������ dc�� �ڵ�
@param	int x left
@param	int y top
@param	int width ��
@param	int height ����
*/
inline void drawEllipse(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

/** drawEllipse RECT�� �޾� �߽����� ���� �׸���.
@date	2015/05/12
@brief	RECT�� �ޱ� ������ left, top, right, bottom �������� �Է� �޴´�.
@param	HDC ������ dc�� �ڵ�
@param	RECT
*/
inline void drawEllipse(HDC hdc, RECT r)
{
	Ellipse(hdc, r.left, r.top, r.right, r.bottom);
}

/** drawEllipseCenter ��ǥ�� �߽����� ���� �׸���.
@date	2015/05/12
@param	HDC ������ dc�� �ڵ�
@param	int centerX �߽� ��ǥ x
@param	int centerY �߽� ��ǥ y
@param	int width ��
@param	int height ����
*/
inline void drawEllipseCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Ellipse(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
}

/** drawEllipseCenter ��ǥ�� �߽����� ���� �׸���.
@date	2015/05/13
@param	HDC ������ dc�� �ڵ�
@param	POINT x, y �߽� ��ǥ POINT
@param	int width ��
@param	int height ����
*/
inline void drawEllipseCenter(HDC hdc, POINT p, int width, int height)
{
	//Ellipse(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
	drawEllipseCenter(hdc, p.x, p.y, width, height);
}

/* ================================================================================
* ===========================  ## �浹 üũ �Լ� ##  ===============================
* ================================================================================ */

/** checkInRect POINT�� RECT ���� �ִ��� üũ. �浹 üũ
@date	2015/05/12
@param	POINT
@param	RECT
@return	bool �ȿ� �����ϴ����� ����
*/
inline bool checkInRect(POINT point, RECT rect)
{
	if (point.x >= rect.left &&
		point.x <= rect.right &&
		point.y >= rect.top &&
		point.y <= rect.bottom)
		return true;
	else
		return false;
}
inline bool checkCollision(POINT p, RECT r)
{
	return checkInRect(p, r);
}

/** checkInRect RECT�� RECT ���� �ִ��� üũ.�浹 üũ
@date	2015/05/12
@param	RECT
@param	RECT
@return	bool �ȿ� �����ϴ����� ����
*/
inline bool checkInRect(RECT rect1, RECT rect2)
{
	if (checkInRect(makePoint(rect1.left + 1, rect1.top + 1), rect2) ||
		checkInRect(makePoint(rect1.right - 1, rect1.top + 1), rect2) ||
		checkInRect(makePoint(rect1.left + 1, rect1.bottom - 1), rect2) ||
		checkInRect(makePoint(rect1.right - 1, rect1.bottom - 1), rect2))
	{
		return true;
	}
	else
	{
		return false;
	}
}
inline bool checkCollision(RECT r1, RECT r2)
{
	return checkInRect(r1, r2);
}