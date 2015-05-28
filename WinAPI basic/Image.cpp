#include "stdafx.h"
#include "Image.h"

#pragma comment (lib, "msimg32.lib")

Image::Image()
	:_imageInfo(NULL),
	_fileName(NULL),
	_trans(NULL),
	_transColor(RGB(0, 0, 0))
{
}


Image::~Image()
{
}

HRESULT Image::initialize(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = width / 2;
	_imageInfo->centerY = height / 2;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;
	
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//�̹��� ���ҽ��� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::initialize(const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = width / 2;
	_imageInfo->centerY = height / 2;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���ϰ���̸� ����
	int fileNameLength = strlen(fileName);
	_fileName = new CHAR[fileNameLength + 1];
	strcpy_s(_fileName, fileNameLength + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//�̹��� ���ҽ��� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::initialize(const char* fileName, float centerX, float centerY, int width, int height, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = centerX;
	_imageInfo->centerY = centerY;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���ϰ���̸� ����
	int fileNameLength = strlen(fileName);
	_fileName = new CHAR[fileNameLength + 1];
	strcpy_s(_fileName, fileNameLength + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//�̹��� ���ҽ��� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::initialize(const char* fileName, int width, int height, int frameColumn, int frameRow, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = width / 2;
	_imageInfo->centerY = height / 2;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameColumn - 1;
	_imageInfo->maxFrameY = frameRow - 1;
	_imageInfo->frameWidth = _imageInfo->width / frameColumn;
	_imageInfo->frameHeight = _imageInfo->height / frameRow;

	//���ϰ���̸� ����
	int fileNameLength = strlen(fileName);
	_fileName = new CHAR[fileNameLength + 1];
	strcpy_s(_fileName, fileNameLength + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//�̹��� ���ҽ��� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}
HRESULT Image::initialize(const char* fileName, float centerX, float centerY, int width, int height, int frameColumn, int frameRow, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = centerX;
	_imageInfo->centerY = centerY;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameColumn - 1;
	_imageInfo->maxFrameY = frameRow - 1;
	_imageInfo->frameWidth = _imageInfo->width / frameColumn;
	_imageInfo->frameHeight = _imageInfo->height / frameRow;

	//���ϰ���̸� ����
	int fileNameLength = strlen(fileName);
	_fileName = new CHAR[fileNameLength + 1];
	strcpy_s(_fileName, fileNameLength + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//�̹��� ���ҽ��� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_blendImage);
		SAFE_DELETE(_fileName);

		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

void Image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void Image::render(HDC hdc)
{
	//����ó���� �� ���
	if (_trans)
	{
		//gdi�� �� �Լ��� �ִ�. 
		GdiTransparentBlt(
			hdc,		//������ �� DC
			_imageInfo->centerX - _imageInfo->width / 2,		//��� ��ǥ X������
			_imageInfo->centerY - _imageInfo->height / 2,		//��� ��ǥ Y������
			_imageInfo->width, //�̹��� ��
			_imageInfo->height, //�̹��� ����
			_imageInfo->hMemDC,
			0, //���� ��ǥ ����
			0, //���� ��ǥ ����
			_imageInfo->width, //���� ��
			_imageInfo->height, //���� ����
			_transColor	//���翡�� ������ ����
			);
	}
	//���� ���� ���
	else
	{
		//StrechBlt�� Ȯ������Ͽ� ���� ����
		BitBlt(hdc, _imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

void Image::render(HDC hdc, int destX, int destY)
{
	//����ó���� �� ���
	if (_trans)
	{
		//gdi�� �� �Լ��� �ִ�. 
		GdiTransparentBlt(
			hdc,		//������ �� DC
			destX,		//��� ��ǥ X������
			destY,		//��� ��ǥ Y������
			_imageInfo->width, //�̹��� ��
			_imageInfo->height, //�̹��� ����
			_imageInfo->hMemDC, 
			0, //���� ��ǥ ����
			0, //���� ��ǥ ����
			_imageInfo->width, //���� ��
			_imageInfo->height, //���� ����
			_transColor	//���翡�� ������ ����
			);
	}
	//���� ���� ���
	else
	{
		//StrechBlt�� Ȯ������Ͽ� ���� ����
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

void Image::render(HDC hdc, int sourX, int sourY, int width, int height)
{
	//����ó���� �� ���
	if (_trans)
	{
		int widthSour, heightSour;
		//gdi�� �� �Լ��� �ִ�. 
		GdiTransparentBlt(
			hdc,		//������ �� DC
			_imageInfo->centerX - width / 2,
			_imageInfo->centerY - height / 2,
			width,
			height,
			_imageInfo->hMemDC,
			sourX,
			sourY,
			width,
			height,
			_transColor	//���翡�� ������ ����
			);
	}
	//���� ���� ���
	else
	{
		//StrechBlt�� Ȯ������Ͽ� ���� ����
		BitBlt(hdc, _imageInfo->centerX - width / 2, _imageInfo->centerY - height / 2, width, height, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}

}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height)
{
	//����ó���� �� ���
	if (_trans)
	{
		int widthSour, heightSour;
		//gdi�� �� �Լ��� �ִ�. 
		GdiTransparentBlt(
			hdc,		//������ �� DC
			destX,		//��� ��ǥ X������
			destY,		//��� ��ǥ Y������
			width,
			height,
			_imageInfo->hMemDC,
			sourX,
			sourY,
			width,
			height,
			_transColor	//���翡�� ������ ����
			);
	}
	//���� ���� ���
	else
	{
		//StrechBlt�� Ȯ������Ͽ� ���� ����
		BitBlt(hdc, destX, destY, width, height, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}

}

void Image::frameRender(HDC hdc)
{
	//����ó���� �� ���
	if (_trans)
	{
		int widthSour, heightSour;
		//gdi�� �� �Լ��� �ִ�. 
		GdiTransparentBlt(
			hdc,		//������ �� DC
			_imageInfo->centerX - _imageInfo->frameWidth / 2,
			_imageInfo->centerY - _imageInfo->frameHeight / 2,		//��� ��ǥ Y������
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,//
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor	//���翡�� ������ ����
			);
	}
	//���� ���� ���
	else
	{
		//StrechBlt�� Ȯ������Ͽ� ���� ����
		BitBlt(hdc,
			_imageInfo->centerX - _imageInfo->frameWidth / 2,
			_imageInfo->centerY - _imageInfo->frameHeight / 2,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}

}
void Image::frameRender(HDC hdc, int destX, int destY)
{
	//����ó���� �� ���
	if (_trans)
	{
		int widthSour, heightSour;
		//gdi�� �� �Լ��� �ִ�. 
		GdiTransparentBlt(
			hdc,		//������ �� DC
			destX - _imageInfo->frameWidth / 2,
			destY - _imageInfo->frameHeight / 2,		//��� ��ǥ Y������
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,//
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor	//���翡�� ������ ����
			);
	}
	//���� ���� ���
	else
	{
		BitBlt(hdc,
			destX - _imageInfo->frameWidth / 2,
			destY - _imageInfo->frameHeight / 2,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}

}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	//����ó���� �� ���
	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, hdc, 0, 0, SRCCOPY);
		//gdi�� �� �Լ��� �ִ�. 
		
		
		GdiTransparentBlt(
			_blendImage->hMemDC,		//������ �� DC
			_imageInfo->centerX - _imageInfo->width / 2,		//��� ��ǥ X������
			_imageInfo->centerY - _imageInfo->height / 2,		//��� ��ǥ Y������
			_imageInfo->width, //�̹��� ��
			_imageInfo->height, //�̹��� ����
			_imageInfo->hMemDC,
			0, //���� ��ǥ ����
			0, //���� ��ǥ ����
			_imageInfo->width, //���� ��
			_imageInfo->height, //���� ����
			_transColor	//���翡�� ������ ����
			);
		
		
		//return;
		AlphaBlend(hdc, _imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC,
			_imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	//���� ���� ���
	else
	{
		AlphaBlend(hdc, _imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC,
			_imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}