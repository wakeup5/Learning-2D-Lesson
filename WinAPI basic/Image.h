/**
@file   Image.h
@author ������(wlsgks5@naver.com)
@date   2015/05/26
*/
#pragma once

/**
@class	Image
@author	������(wlsgks5@naver.com)
@date	2015/05/26
*/
class Image
{
private:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCES = 0, //���ҽ� �ε�
		LOAD_FILE,			//���Ϸε�
		LOAD_EMPTY,			//�ƹ��͵� ���� �̹���
		LOAD_END			//�̳ѹ��� �� Ȥ�� ����
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		int width;
		int height;
		BYTE loadType;
		
		//����ü �ʱ�ȭ
		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCES;
		};

	}IMAGE_INFO, *LPIMAGE_INFO;

	LPIMAGE_INFO _imageInfo;	//�̹��� ���
	CHAR *_fileName;			//�̹��� ��θ�
	BOOL _trans;				//����
	COLORREF _transColor;		//���� �÷�Ű	
public:
	Image();
	~Image();

	//�� ��Ʈ�� �ϳ� ����
	HRESULT initialize(int width, int height);

	//�̹��� ����(���Ϸ� �о��)
	HRESULT initialize(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	void release(void);

	//����Ű �� ����
	void setTransColor(BOOL trans, COLORREF transColor);

	//�Ϲ� ������
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int x, int y, int width, int height);

	//DC���
	inline HDC getMemDC(){ return _imageInfo->hMemDC; }
};

