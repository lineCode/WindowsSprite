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
	// ������ϵ��ͼƬ�����Ź�����
	class Animation
	{
	public:
		Animation();
		~Animation();
		// ���Ŷ���
		int Play();

	private:


#pragma region ��̬D2D��Դ <<<
		// D2D ����
		ID2D1Factory *				pD2DFactory;
		// WICλͼ����
		IWICImagingFactory*			pIWICFactory;
		// ������(��Ⱦ)Ŀ��
		ID2D1RenderTarget*			pRenderTarget;
		// ������ ������Ŀ��
		ID2D1HwndRenderTarget*		pHwndRenderTarget;
		bool InitialzationD2DFactory(HWND hwnd);
		bool CreateBitmapFromFile(LPCWSTR fileName);
	};
#pragma endregion



}