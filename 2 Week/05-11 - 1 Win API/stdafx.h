// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

//MFC�� �ƴ� �������α׷��� ��쿡�� WIN32_LEAN_AND_MEAN�� ������ ���� �ð��� �����Ų��.
#define WIN32_LEAN_AND_MEAN

/* ========================================
 *  ## ������� ##
 * ======================================== */
#include <Windows.h>	//������ ���� ���
#include <stdio.h>		//ǥ�� ����� ���
#include <tchar.h>		//�����쿡�� ����� ���ڿ� ��� ���
//MBCS(Multi Byte Character Set) ������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ�
//WBCS(Widw Byte Character Set) ��� ���ڸ� 2����Ʈ�� ó��

#include <math.h>
#include <string>

/* ========================================
 *  ## ���ǹ� ##
 * ======================================== */

//������ �̸�
#define WIN_NAME (LPTSTR)(TEXT("API Window"))

//������ ��ġ ������
#define WIN_START_X 100		//x��ġ
#define WIN_START_Y 100		//y��ġ
#define WIN_SIZE_X 1000		//��
#define WIN_SIZE_Y 1000		//����

//������ ��Ÿ��
#define WIN_STYLE WS_CAPTION | WS_SYSMENU

//���� �����Ҵ� ���� ��ũ��
#define SAFE_DELETE(p)			{if (p) {delete(p); (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if (p) {delete[](p); (p)=NULL;}}
#define SAFE_RELEASE(p)			{if (p) {(p)->release(); (p) = NULL;}}


/* ========================================
 *  ## �������� ##
 * ======================================== */
extern HINSTANCE _hInstance; // ���α׷� �ν��Ͻ�
extern HWND _hWnd; // ������ �ڵ�

using namespace std;