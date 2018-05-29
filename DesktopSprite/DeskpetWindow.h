#pragma once
// 去除win32很少用到的方法
#define WIN32_LEAN_AND_MEAN 
// Windows Header Files:
#include "SpriteHandle.h"
using namespace Sprite;

namespace D2DWindow {

	class DeskpetWindow
	{

	public:
		DeskpetWindow(LPCWSTR wndTitle, POINT point, SIZE wndsize);
		~DeskpetWindow();

		LPCWSTR GetwndClassName();

		SpriteHandle spriteInstace;




		/// --------------------
		/// 字段 >>>
		/// --------------------

		// 应用窗口句柄
		HWND Hwnd;
		// 窗体类名标识
		LPCWSTR wndClassName;
		// 应用窗口标题
		LPCWSTR WinName;
		// 应用实例句柄
		HINSTANCE Hinstance;
		// 窗体屏幕坐标（左上角)
		POINT ScreenPoint;
		// 窗体宽高
		SIZE WndSize;

		/// --------------------
		/// 字段 <<<
		/// --------------------


		/// --------------------
		/// 方法 >>>
		/// --------------------

		// 窗体过程响应事件方法，处理事件消息
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

		// 初始化窗体
		bool Initialzation(HINSTANCE hInstance, HINSTANCE prevInstance = 0, LPWSTR cmdLine = 0, int cmdShow = 0);
		// 重绘-更新窗口
		void Update();

		/// --------------------
		/// 方法 <<<
		/// --------------------

	private:

	};

#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;} 
	DeskpetWindow::DeskpetWindow(LPCWSTR wndTitle, POINT point, SIZE wndsize)
	{
		WinName = wndTitle;
		ScreenPoint = point;
		WndSize = wndsize;
		wndClassName = TEXT("DeskpetWindow_kaakira");
	}

	DeskpetWindow::~DeskpetWindow()
	{
	}


	bool DeskpetWindow::Initialzation(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
	{
#pragma region 初始化窗体参数//基本不用改动
		this->Hinstance = hInstance;
		UNREFERENCED_PARAMETER(prevInstance);
		UNREFERENCED_PARAMETER(cmdLine);

		WNDCLASSEXW wndClass = { 0 };
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = DeskpetWindow::WndProc;
		wndClass.hInstance = hInstance;
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
		//wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = this->wndClassName;
		if (!RegisterClassEx(&wndClass))
		{
			return false;
		}

		this->Hwnd = CreateWindowEx(
			// 窗口扩展样式
			NULL,//WS_EX_LAYERED,
				 // 窗体类名
			this->wndClassName,
			// 窗口标题
			this->WinName,
			// 窗口样式
			WS_OVERLAPPEDWINDOW,
			// 窗口初始屏幕X坐标
			this->ScreenPoint.x,
			// 窗口初始屏幕Y坐标
			this->ScreenPoint.y,
			// 窗口初始宽度
			this->WndSize.cx,
			// 窗口初始高度
			this->WndSize.cx,
			// 父窗体句柄
			NULL,
			// 菜单的句柄或是子窗口的标识符
			NULL,
			// 应用程序实例的句柄
			this->Hinstance,
			// 指向窗口的创建数据
			this
		);
		//GetClientRect(Hwnd, &ScreenPoint);
		if (!Hwnd) {
			return false;
		}
#pragma endregion
		return true;
	}

	void DeskpetWindow::Update()
	{
		//CreateD2DResource(Hwnd);
		spriteInstace.LoadAnmationResources();
		//Clear();

		UpdateWindow(Hwnd);

	}


	LPCWSTR DeskpetWindow::GetwndClassName()
	{
		return this->wndClassName;
	}
}