#include "Animation.h"
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;} 


Animation::~Animation()
{

}


Animation::Animation(HDC * hdcSrc,RECT *rcClient)
{
	this->HwndDC = *hdcSrc;
	HRESULT hr = NULL;
	// 初始化Direct2D（主要)工厂
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	HR(pD2DFactory->CreateDCRenderTarget(
		&D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)),
		&pDCtarget));
	// 绑定dc
	this->pDCtarget->BindDC(this->HwndDC, rcClient);
	// 初始化 WIC 图片工厂
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


// 返回位图
ID2D1Bitmap* Animation::CreateBitmapFromFile(LPCWSTR fileName)
{
	HRESULT hr = S_OK;
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
	ID2D1Bitmap* pBitmap = NULL;
	HR(pDCtarget->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap));\
	return pBitmap;
}


// 获取运行时间
float Animation::GetCurrentTick()
{
	// 用QueryPerformanceCounter()来计时  微秒  
	LARGE_INTEGER  large_interger;
	double dff;
	__int64  c1;
	// 返回硬件支持的高精度计数器的频率（次每秒），返回0表示失败。
	QueryPerformanceFrequency(&large_interger);
	dff = large_interger.QuadPart;
	// 获取计数器
	QueryPerformanceCounter(&large_interger);
	c1 = large_interger.QuadPart;

	//printf("第一次计时器值%I64d 第二次计时器值%I64d 计时器差%I64d\n", c1, c2, c2 - c1);
	return  c1 * 1000 / dff;

}