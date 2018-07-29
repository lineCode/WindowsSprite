#include "Animation.h"
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;} 


Animation::~Animation()
{

}


Animation::Animation(HDC * hdcSrc,RECT *rcClient)
{
	this->HwndDC = *hdcSrc;
	HRESULT hr = NULL;
	// ��ʼ��Direct2D����Ҫ)����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	HR(pD2DFactory->CreateDCRenderTarget(
		&D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)),
		&pDCtarget));
	// ��dc
	this->pDCtarget->BindDC(this->HwndDC, rcClient);
	// ��ʼ�� WIC ͼƬ����
	HR(CoInitialize(NULL));
	HR(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory)));
}


bool Animation::Play(ID2D1Bitmap* images, float delay)
{
	if (GetCurrentTick() - lastPlayTick >= delay)
	{
		//ID2D1SolidColorBrush* gBrush;
		pDCtarget->BeginDraw();
		pDCtarget->Clear();
		pDCtarget->DrawBitmap(images);

	/*	pDCtarget->CreateSolidColorBrush(D2D1::ColorF(0x12385123, 1.0), &gBrush);
		pDCtarget->DrawLine(D2D1::Point2F(200, 200), D2D1::Point2F(300, 300), gBrush, 50);
		pDCtarget->DrawRectangle(
			D2D1::RectF(100.f, 100.f, 500.f, 500.f),
			gBrush
		);
*/
		pDCtarget->EndDraw();
		lastPlayTick = GetCurrentTick();
		return true;
	}
	else {
		return false;
	}
}


// ����λͼ
ID2D1Bitmap* Animation::CreateBitmapFromFile(LPCWSTR fileName)
{
	HRESULT hr = S_OK;
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
	ID2D1Bitmap* pBitmap = NULL;
	HR(pDCtarget->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap));\
	return pBitmap;
}


// ��ȡ����ʱ��
float Animation::GetCurrentTick()
{
	// ��QueryPerformanceCounter()����ʱ  ΢��  
	LARGE_INTEGER  large_interger;
	double dff;
	__int64  c1;
	// ����Ӳ��֧�ֵĸ߾��ȼ�������Ƶ�ʣ���ÿ�룩������0��ʾʧ�ܡ�
	QueryPerformanceFrequency(&large_interger);
	dff = large_interger.QuadPart;
	// ��ȡ������
	QueryPerformanceCounter(&large_interger);
	c1 = large_interger.QuadPart;

	//printf("��һ�μ�ʱ��ֵ%I64d �ڶ��μ�ʱ��ֵ%I64d ��ʱ����%I64d\n", c1, c2, c2 - c1);
	return  c1 * 1000 / dff;

}