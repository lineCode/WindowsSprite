#pragma once
#define ANIMATION
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

	private:


		///------------------------------
		/// 静态D2D资源 <<<
		///------------------------------
#pragma region 
		// D2D 工厂
		ID2D1Factory *				pD2DFactory;
		// WIC位图工厂
		IWICImagingFactory*			pIWICFactory;
		// 呈现器(渲染)目标
		ID2D1RenderTarget*			pRenderTarget;
		// 窗体句柄 呈现器目标
		ID2D1HwndRenderTarget*		pHwndRenderTarget;
		bool InitialzationD2DFactory(HWND hwnd) {
			HRESULT hr = NULL;
			// 初始化Direct2D（主要)工厂
			hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
			RECT rc;
			// 
			GetClientRect(hwnd, &rc);
			// 初始化Direct2D窗体句柄
			hr = pD2DFactory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right, rc.bottom)),
				&pHwndRenderTarget
			);

			//	//为了兼容win7、win10，这里采用CLSID_WICImagingFactory1
			//	hr = CoCreateInstance(
			//		CLSID_WICImagingFactory1,
			//		NULL,
			//		CLSCTX_INPROC_SERVER,
			//		IID_IWICImagingFactory,
			//		(LPVOID*)&pIWICFactory
			//	);

			// 初始化 WIC 图片工厂
			hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory));

			if (FAILED(hr))
			{
				MessageBox(NULL, TEXT("Animation 初始化D2D资源时失败，HRESULT:") + hr,TEXT("Animation"), NULL);
				return false;
			}
			return true;
		}
		bool CreateBitmapFromFile(LPCWSTR fileName)
		{
			HRESULT hr = S_OK;
			char s[] = "C:\\Users\\NET45.png";
			//创建wic（位图）解码器  
			IWICBitmapDecoder *	pDecoder;
			hr = pIWICFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
			// 解码后，获取图片第一帧
			IWICBitmapFrameDecode* pFrame;
			hr = pDecoder->GetFrame(0, &pFrame);


			// 创建图片格式化转换器
			IWICFormatConverter*		pConverter;
			hr = pIWICFactory->CreateFormatConverter(&pConverter);
			hr = pConverter->Initialize(
				pFrame,                          // 位图数据
				GUID_WICPixelFormat32bppPBGRA,   // 转换的像素格式 
				WICBitmapDitherTypeNone,         // Specified dither pattern  
				NULL,                            // Specify a particular palette   
				0.f,                             // Alpha threshold  
				WICBitmapPaletteTypeCustom       // Palette translation type  
			);
			ID2D1Bitmap* pBitmap;
			hr = pHwndRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &pBitmap);

			/*	SAFE_RELEASE(pDecoder);
				SAFE_RELEASE(pSource);
				SAFE_RELEASE(pConverter);*/
			return true;
		}
	};
#pragma endregion
	///------------------------------
	/// 静态D2D资源 <<<
	///------------------------------


	Animation::Animation()
	{

	}

	Animation::~Animation()
	{
	}
	int Animation::Play()
	{
		return 0;
	}
}