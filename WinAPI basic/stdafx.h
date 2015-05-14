/**
@file	stdafx.h
@author	������(wakeup5, wlsgks5@naver.com)
@date	2015/05/08
@brief	��� ���� ����Ʈ
*/
#pragma once
#include "targetver.h"

//MFC�� �ƴ� �������α׷��� ��쿡�� WIN32_LEAN_AND_MEAN�� ������ ���� �ð��� �����Ų��.
#define WIN32_LEAN_AND_MEAN

/* ========================================
*  ## ������� ##
* ======================================== */
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

//�ʿ信 ���� �⺻ ���̺귯�� ��� �߰�
#include <math.h>
#include <string>
#include <vector>
#include <time.h>

//��ũ�� ���
#include "commonMacroFunction.h"

//����� ���� ���
#include "RandomFunction.h"
#include "GameStudy.h"
#include "KeyManager.h"

/* ========================================
*  ## ���ǹ� ##
* ======================================== */

//������ �̸�
#define WIN_NAME		(LPTSTR)(TEXT("API Window"))

//������ ��ġ ������
#define WIN_START_X		100		//x��ġ
#define WIN_START_Y		100		//y��ġ
#define WIN_SIZE_X		500		//��
#define WIN_SIZE_Y		500		//����

//������ ��Ÿ��
#define WIN_STYLE		WS_CAPTION | WS_SYSMENU

//���� �����Ҵ� ���� ��ũ��
#define SAFE_DELETE(p)			{if (p) {delete(p); (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if (p) {delete[](p); (p)=NULL;}}
#define SAFE_RELEASE(p)			{if (p) {(p)->release(); (p) = NULL;}}

//class RandomFunction
#define RANDOM RandomFunction::getSingleton()

//class KeyManager
#define KEYMANAGER KeyManager::getSingleton()

/* ========================================
*  ## �������� ##
* ======================================== */
extern HINSTANCE _hInstance; // ���α׷� �ν��Ͻ�
extern HWND _hWnd; // ������ �ڵ�

extern POINT _mousePoint;