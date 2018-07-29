#pragma once
#include "../resoures.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include <dxgi.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

using namespace std;



// ������ϵ��ͼƬ�����Ź�����
class Animation
{
public:
	Animation(HDC * hdcSrc,RECT* rcClient);
	~Animation();

	// ���Ŷ���
	bool Play(ID2D1Bitmap * images,float delay);
	// ����λͼ
	ID2D1Bitmap* CreateBitmapFromFile(LPCWSTR fileName);
	// ��ȡ��ǰʱ�� ms��λ
	float GetCurrentTick();


private:
	// D2D ����
	ID2D1Factory *				pD2DFactory;
	// WICλͼ����
	IWICImagingFactory*			pIWICFactory;
	// ������(��Ⱦ)Ŀ��
	//ID2D1RenderTarget*			pRenderTarget;

	// Hwnd��� ������
	ID2D1HwndRenderTarget*		pHWNDtarget;
	// DC���
	ID2D1DCRenderTarget*		pDCtarget;
	HDC							HwndDC;

	// �ϴβ������ʱ��
	float lastPlayTick;
};



