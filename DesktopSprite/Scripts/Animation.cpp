#include "Animation.h"
using namespace D2DWindow;
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
bool Animation::InitialzationD2DFactory(HWND hwnd) {
	HRESULT hr = NULL;
	// ��ʼ��Direct2D����Ҫ)����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	RECT rc;
	// 
	GetClientRect(hwnd, &rc);
	// ��ʼ��Direct2D������
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right, rc.bottom)),
		&pHwndRenderTarget
	);

	//	//Ϊ�˼���win7��win10���������CLSID_WICImagingFactory1
	//	hr = CoCreateInstance(
	//		CLSID_WICImagingFactory1,
	//		NULL,
	//		CLSCTX_INPROC_SERVER,
	//		IID_IWICImagingFactory,
	//		(LPVOID*)&pIWICFactory
	//	);

	// ��ʼ�� WIC ͼƬ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory));

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Animation ��ʼ��D2D��Դʱʧ�ܣ�HRESULT:") + hr, TEXT("Animation"), NULL);
		return false;
	}
	return true;
}

bool Animation::CreateBitmapFromFile(LPCWSTR fileName)
{
	HRESULT hr = S_OK;
	char s[] = "C:\\Users\\NET45.png";
	//����wic��λͼ��������  
	IWICBitmapDecoder *	pDecoder;
	hr = pIWICFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
	// ����󣬻�ȡͼƬ��һ֡
	IWICBitmapFrameDecode* pFrame;
	hr = pDecoder->GetFrame(0, &pFrame);


	// ����ͼƬ��ʽ��ת����
	IWICFormatConverter*		pConverter;
	hr = pIWICFactory->CreateFormatConverter(&pConverter);
	hr = pConverter->Initialize(
		pFrame,                          // λͼ����
		GUID_WICPixelFormat32bppPBGRA,   // ת�������ظ�ʽ 
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
