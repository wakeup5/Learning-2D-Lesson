#include "stdafx.h"
#include "GameStudy.h"

//�ʱ�ȭ
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	_center.x = WIN_SIZE_X / 2;
	_center.y = WIN_SIZE_Y / 2;

	return S_OK;
}

//����
void GameStudy::release(void)
{
	GameNode::release();
}

//ȭ�鰻��
void GameStudy::update(void)
{
	GameNode::update();

	timer = time(NULL);
	localtime_s(&t, &timer);

	_hour = t.tm_hour;
	_minite = t.tm_min;
	_second = t.tm_sec;

	//��ħ ���ڸ� ��ǥ
	double secondRadian = ((_second / 60 * 360) - 90) * M_PI / 180;
	_sp.x = _center.x + LENGTH_SECOND * cos(secondRadian);
	_sp.y = _center.y + LENGTH_SECOND * sin(secondRadian);

	//��ħ ���ڸ� ��ǥ
	double miniteRadian = (((_minite / 60 * 360) - 90) * M_PI / 180) + secondRadian / 60;
	_mp.x = _center.x + LENGTH_MINITE * cos(miniteRadian);
	_mp.y = _center.y + LENGTH_MINITE * sin(miniteRadian);

	//��ħ ���ڸ� ��ǥ
	double hourRadian = (((_hour / 12 * 360) - 90) * M_PI / 180) + miniteRadian / 60;
	_hp.x = _center.x + LENGTH_HOUR * cos(hourRadian);
	_hp.y = _center.y + LENGTH_HOUR * sin(hourRadian);

}

//ȭ�����
void GameStudy::render(HDC hdc)
{
	//�ð� �����ڸ� ���
	drawEllipseCenter(hdc, _center, WATCH_SIZE, WATCH_SIZE);
	drawEllipseCenter(hdc, _center, 5, 5);

	HPEN p;

	//��ħ
	p = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 5, RGB(0, 0, 0)));
	drawLine(hdc, _center.x, _center.y, _hp.x, _hp.y);
	//��ħ
	p = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 0)));
	drawLine(hdc, _center.x, _center.y, _mp.x, _mp.y);
	//��ħ
	p = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 0, 0)));
	drawLine(hdc, _center.x, _center.y, _sp.x, _sp.y);
	//SelectObject(hdc, p);
	//DeleteObject(p);


	TCHAR time[128];
	sprintf_s(time, "%0.0f : %0.0f : %0.0f", _hour, _minite, _second);
	TextOut(hdc, 10, 10, time, _tcslen(time));
}
