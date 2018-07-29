#pragma once
// 去除win32很少用到的方法
// #define WIN32_LEAN_AND_MEAN 
#include "../resoures.h"

#define MYWM_NOTIFYICON 0x00101
#define IDR_MAINFRAME  0x00110
#define NOTIFYICONUID 0x000110



	//private const int SW_HIDE = 0; 　　		//从任务栏隐藏
	//private const int SW_NORMAL = 1;			//正常弹出窗体 
	//private const int SW_MAXIMIZE = 3;		//最大化弹出窗体 
	//private const int SW_SHOWNOACTIVATE = 4;	//激活窗体/恢复窗体/还原窗体
	//private const int SW_SHOW = 5; 　　		//显示窗体，最小化时不a会最大化
	//private const int SW_MINIMIZE = 6; 　　	//最小化
	//private const int SW_RESTORE = 9;
	//private const int SW_SHOWDEFAULT = 10;

class WindowInfo
{
public:
	WindowInfo(HINSTANCE Hinstance, LPCWSTR wndTitle, POINT point, SIZE wndsize, int cmdShow = SW_SHOWDEFAULT);
	~WindowInfo();

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

	// 获取窗体类名名称
	LPCWSTR GetwndClassName();
	// 
	RECT GetClientRect();
	HDC* GetHDCSrc();
	void UpdateLayered();
	NOTIFYICONDATA TrayIcon;

	// 拖拽窗口
	static void DragWindowd(POINT pt,HWND hwnd);
	// 弹出托盘菜单
	static void PopupNotifyMenu(HWND hwnd );

private:
	// 托盘弹出菜单
	static HMENU ntiMenu;


	// 窗体类名标识
	LPCWSTR wndClassName;
	//NOTIFYICONDATA
	HDC hdcSrc;
	HDC hdcDst;
	RECT rcClient;
	RECT clientRect;

	static	LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};


