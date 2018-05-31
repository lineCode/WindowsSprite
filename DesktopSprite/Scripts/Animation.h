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
		// ����λͼ
		ID2D1Bitmap* CreateBitmapFromFile(LPCWSTR fileName);
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
		
		// ��ʼ��D2D��פ�豸��Դ
		bool InitialzationD2DFactory(HWND hwnd);
	};
#pragma endregion



}