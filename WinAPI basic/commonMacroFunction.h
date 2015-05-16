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
typedef struct tagPOINTRECT
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

/** reverseRect RECT�� left, right�� top, bottom�� ���� �ڸ��� �ٲ� ��� ���� ���� �ٲ��ش�.
@date	2015/05/16
@param	RECT
@return	RECT
*/
inline RECT reverseRect(RECT &rect)
{
	int temp;

	if (rect.left > rect.right)
	{
		temp = rect.left;
		rect.left = rect.right;
		rect.right = temp;
	}

	if (rect.top > rect.bottom)
	{
		temp = rect.top;
		rect.top = rect.bottom;
		rect.bottom = temp;
	}

	return rect;
}

/** makePointByRect RECT�� �߽� ��ǥ ����
@date	2015/05/16
@param	RECT
@return	POINT
*/
inline POINT makePointByRect(RECT r)
{
	r = reverseRect(r);
	return POINT{ r.left + (r.right - r.left) / 2, r.top + (r.bottom - r.top) / 2 };
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

/** checkInRectangle POINT�� RECT ���� �ִ��� üũ. �浹 üũ
@date	2015/05/12
@param	POINT
@param	RECT
@return	bool �ȿ� �����ϴ����� ����
*/
inline bool checkInRectangle(POINT point, RECT rect)
{
	rect = reverseRect(rect);

	if (point.x >= rect.left &&
		point.x <= rect.right &&
		point.y >= rect.top &&
		point.y <= rect.bottom)
		return true;
	else
		return false;
}
inline bool isCollisionRectangle(POINT p, RECT r)
{
	return checkInRectangle(p, r);
}

/** checkInRectangle RECT�� RECT ���� �ִ��� üũ.�浹 üũ
@date	2015/05/12
@param	RECT
@param	RECT
@return	bool �ȿ� �����ϴ����� ����
*/
inline bool checkInRectangle(RECT rect1, RECT rect2)
{
	rect1 = reverseRect(rect1);
	rect2 = reverseRect(rect2);

	if (checkInRectangle(makePoint(rect1.left + 1, rect1.top + 1), rect2) || //1 -> 2
		checkInRectangle(makePoint(rect1.right - 1, rect1.top + 1), rect2) ||
		checkInRectangle(makePoint(rect1.left + 1, rect1.bottom - 1), rect2) ||
		checkInRectangle(makePoint(rect1.right - 1, rect1.bottom - 1), rect2) ||
		checkInRectangle(makePoint(rect2.left + 1, rect2.top + 1), rect1) || // 2 -> 1
		checkInRectangle(makePoint(rect2.right - 1, rect2.top + 1), rect1) ||
		checkInRectangle(makePoint(rect2.left + 1, rect2.bottom - 1), rect1) ||
		checkInRectangle(makePoint(rect2.right - 1, rect2.bottom - 1), rect1))
	{
		return true;
	}
	else
	{
		return false;
	}
}
inline bool isCollisionRectangle(RECT r1, RECT r2)
{
	return checkInRectangle(r1, r2);
}

/** checkInEllipse POINT�� RECT(��) ���� �ִ��� üũ.�浹 üũ
@date	2015/05/12
@param	POINT
@param	RECT
@return	bool �ȿ� �����ϴ����� ����
*/
inline bool checkInEllipse(POINT p, RECT r)
{
	r = reverseRect(r);

	POINT center = POINT{ (r.left + (r.right - r.left) / 2), (r.top + (r.bottom - r.top) / 2) };
	int x = p.x - center.x;
	int y = p.y - center.y;
	int width = (r.right - r.left) / 2;
	int height = (r.bottom - r.top) / 2;

	if (pow(x, 2) / pow(width, 2) + pow(y, 2) / pow(height, 2) <= 1)
	{
		return true;
	}

	return false;
}
inline bool isCollisionEllipse(POINT p, RECT r)
{
	return checkInEllipse(p, r);
}

/** checkInEllipse �簢���� ���� �浹 ó��
@date	2015/05/16
@param	RECT �簢��
@param	RECT ��
@return	bool �ȿ� �����ϴ����� ����
*/
inline bool checkInEllipse(RECT rectangle, RECT ellipse)
{
	POINT ellipseCenter = makePointByRect(ellipse);

	rectangle = reverseRect(rectangle);
	ellipse = reverseRect(ellipse);

	//������ ���ɼ��� ������ ���� �ؾ���..
	if (checkInEllipse(makePoint(rectangle.left + 1, rectangle.top + 1), ellipse) || //�� �簢���� �𼭸��� �� �ȿ� ������
		checkInEllipse(makePoint(rectangle.right - 1, rectangle.top + 1), ellipse) ||
		checkInEllipse(makePoint(rectangle.left + 1, rectangle.bottom - 1), ellipse) ||
		checkInEllipse(makePoint(rectangle.right - 1, rectangle.bottom - 1), ellipse) ||
		checkInRectangle(ellipseCenter, rectangle) || //�� �߽��� �簢�� �ȿ� ������
		(ellipseCenter.x >= rectangle.left && ellipseCenter.x <= rectangle.right && //�� �߽��� x���� �簢�� �� �ȿ� �����鼭 �簢�� �Ʒ��� �� ��, �簢�� ���� �� �Ʒ� �ȿ� ������
		ellipse.top < rectangle.bottom && ellipse.bottom > rectangle.top) ||
		(ellipseCenter.y >= rectangle.top && ellipseCenter.y <= rectangle.bottom && //y ��
		ellipse.left < rectangle.right && ellipse.right > rectangle.left))
	{
		return true;
	}
	else
	{
		return false;
	}
}
inline bool isCollisionEllipse(RECT rectangle, RECT ellipse)
{
	return checkInEllipse(rectangle, ellipse);
}
