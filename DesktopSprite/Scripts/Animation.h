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



// 动画（系列图片）播放工具类
class Animation
{
public:
	Animation(HDC * hdcSrc,RECT* rcClient);
	~Animation();

	// 播放动画
	bool Play(ID2D1Bitmap * images,float delay);
	// 创建位图
	ID2D1Bitmap* CreateBitmapFromFile(LPCWSTR fileName);
	// 获取当前时间 ms单位
	float GetCurrentTick();


private:
	// D2D 工厂
	ID2D1Factory *				pD2DFactory;
	// WIC位图工厂
	IWICImagingFactory*			pIWICFactory;
	// 呈现器(渲染)目标
	//ID2D1RenderTarget*			pRenderTarget;

	// Hwnd句柄 呈现器
	ID2D1HwndRenderTarget*		pHWNDtarget;
	// DC句柄
	ID2D1DCRenderTarget*		pDCtarget;
	HDC							HwndDC;

	// 上次播放完的时间
	float lastPlayTick;
};



