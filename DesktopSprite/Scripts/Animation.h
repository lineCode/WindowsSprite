#pragma once
#include "resoures.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include <dxgi.h>
//#include <dxguid.h>
//#include <windowscodecs.h>
//
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

using namespace std;
namespace D2DWindow {
	// 动画（系列图片）播放工具类
	class Animation
	{
	public:
		Animation();
		~Animation();
		
		// 播放动画
		int Play();
		// 创建位图
		ID2D1Bitmap* CreateBitmapFromFile(LPCWSTR fileName);
	private:


#pragma region 静态D2D资源 <<<
		// D2D 工厂
		ID2D1Factory *				pD2DFactory;
		// WIC位图工厂
		IWICImagingFactory*			pIWICFactory;
		// 呈现器(渲染)目标
		ID2D1RenderTarget*			pRenderTarget;
		// 窗体句柄 呈现器目标
		ID2D1HwndRenderTarget*		pHwndRenderTarget;
		
		// 初始化D2D常驻设备资源
		bool InitialzationD2DFactory(HWND hwnd);
	};
#pragma endregion



}