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
		float centerX;
		float centerY;
		int width;
		int height;
		BYTE loadType;
		RECT boundingBox;
		
		//����ü �ʱ�ȭ
		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			centerX = 0;
			centerY = 0;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCES;
			boundingBox = makeRect(0, 0, 0, 0);
		};

	}IMAGE_INFO, *LPIMAGE_INFO;

	LPIMAGE_INFO _imageInfo;	//�̹��� ���
	CHAR *_fileName;			//�̹��� ��θ�
	BOOL _trans;				//����
	COLORREF _transColor;		//���� �÷�Ű	

	inline void setBoundingBox()
	{
		_imageInfo->boundingBox = makeRectCenter(_imageInfo->centerX, _imageInfo->centerY, _imageInfo->width, _imageInfo->height);
	}
public:
	Image();
	~Image();

	//�� ��Ʈ�� �ϳ� ����
	HRESULT initialize(int width, int height);

	//�̹��� ����(���Ϸ� �о��)
	HRESULT initialize(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initialize(const char* fileName, float centerX, float centerY, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	void release(void);

	//����Ű �� ����
	void setTransColor(BOOL trans, COLORREF transColor);

	//�Ϲ� ������
	void render(HDC hdc);
	void render(HDC hdc, int sourX, int sourY, int width, int height);

	//�̹��� ��ü�� �߽� ��ǥ�� �����ϰ� ���ϴ� ��ǥ�� �׸� �� �ִ�.
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height);

	//DC���
	inline HDC getMemDC(){ return _imageInfo->hMemDC; }

	//��ǥ x
	inline void setX(float x){ _imageInfo->centerX = x; setBoundingBox(); }
	inline float getX(){ return _imageInfo->centerX; }

	//��ǥ y
	inline void setY(float y){ _imageInfo->centerY = y; setBoundingBox(); }
	inline float getY(){ return _imageInfo->centerY; }

	//��ǥ x, y
	inline void setCenter(float x, float y){ _imageInfo->centerX = x; _imageInfo->centerY = y; setBoundingBox(); }

	//���� �ػ�
	inline int getWidth(){ return _imageInfo->width; }

	//���� �ػ�
	inline int getHeight(){ return _imageInfo->height; }

	//�ٿ�� �ڽ�
	inline RECT boundingBox(){ return _imageInfo->boundingBox; }
	
};

