#pragma once
// 去除win32很少用到的方法
#define WIN32_LEAN_AND_MEAN 
#include "SpriteHandle.h"
using namespace Sprite;

namespace D2DWindow {

	//private const int SW_HIDE = 0; 　　		//从任务栏隐藏
	//private const int SW_NORMAL = 1;			//正常弹出窗体 
	//private const int SW_MAXIMIZE = 3;		//最大化弹出窗体 
	//private const int SW_SHOWNOACTIVATE = 4;	//激活窗体/恢复窗体/还原窗体
	//private const int SW_SHOW = 5; 　　		//显示窗体，最小化时不会最大化
	//private const int SW_MINIMIZE = 6; 　　	//最小化
	//private const int SW_RESTORE = 9;
	//private const int SW_SHOWDEFAULT = 10;
	class DeskpetWindow
	{

	public:
		DeskpetWindow(HINSTANCE Hinstance,LPCWSTR wndTitle, POINT point, SIZE wndsize,int cmdShow = SW_SHOWDEFAULT);
		~DeskpetWindow();

		// 精灵总控制器（"精灵的大脑"）
		SpriteHandle spriteInstace;
		// 应用窗口句柄
		HWND Hwnd;
		// 应用窗口标题
		LPCWSTR WinName;
		// 应用实例句柄
		HINSTANCE Hinstance;
		// 窗体屏幕坐标（左上角)
		POINT ScreenPoint;
		// 窗体宽高
		SIZE WndSize;
		// 显示窗体模式
		int CmdShow = SW_SHOWDEFAULT;


		// 窗体过程响应事件方法，处理事件消息
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		// 重绘-更新窗口  
		void Update();
		// 获取窗体类名名称
		LPCWSTR GetwndClassName();
		// 显示精灵窗体
		bool ShowSpriteWindow(int cmdShow = SW_SHOWDEFAULT);

	private:
		// 窗体类名标识
		LPCWSTR wndClassName;
		 


		// 初始化窗体 
		bool Initialzation();

	};


}