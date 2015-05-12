/** commonMacroFunction
@file		commonMacroFunction.h
@author	������(wlsgks5@naver.com)
@date	2015/05/12
@brief	�����ϰ� ����� �ζ��� ��ũ�� �Լ��� ����.
*/
#include "stdafx.h"

/** makePoint ��ǥ�� �Է��ϸ� ����Ʈ ������ ����� ����
@author	������(wlsgks5@naver.com)
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
@author	������(wlsgks5@naver.com)
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
@author	������(wlsgks5@naver.com)
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

/** drawLine ��ǥ�� �Է¹޾� ���� �׸���.
@author	������(wlsgks5@naver.com)
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
@author	������(wlsgks5@naver.com)
@date	2015/05/12
@param	HDC ������ dc�� �ڵ�
@param	vector<POINT> �������� �����͵�
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
@author	������(wlsgks5@naver.com)
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

/** drawRectangleCenter ��ǥ�� �߽����� �簢���� �׸���.
@author	������(wlsgks5@naver.com)
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

/** drawEllipse ��ǥ�� ũ�⸦ �Է¹޾� ���� �׸���.
@author	������(wlsgks5@naver.com)
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

/** drawEllipseCenter ��ǥ�� �߽����� ���� �׸���.
@author	������(wlsgks5@naver.com)
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