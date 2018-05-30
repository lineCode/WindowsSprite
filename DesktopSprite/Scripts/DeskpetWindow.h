#pragma once
// 去除win32很少用到的方法
#define WIN32_LEAN_AND_MEAN 
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

		/// <sumary>
		/// 窗体过程响应事件方法，处理事件消息
		/// </sumary>
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

		// 初始化窗体 
		bool Initialzation(HINSTANCE hInstance, HINSTANCE prevInstance = 0, LPWSTR cmdLine = 0, int cmdShow = 0);

		/// <sumary> 重绘-更新窗口 </sumary> 
		void Update(); 


	private:
		
	};
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;} 
#endif


}