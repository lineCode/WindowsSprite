
#include "WindowInfo.h"
#include "SpriteHandle.h"


using namespace Sprite;

// 窗体信息（构造窗体）
WindowInfo* petWnd;
// 精灵总控制器（精灵的大脑）
SpriteHandle sprite;
// 鼠标左键按下
bool	lbDown = false;
// 鼠标按下时，在窗体的坐标
POINT	TheFirstPoint;




LRESULT CALLBACK WindowInfo::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT pt = { 0 };
	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_RBUTTONDOWN:
		WindowInfo::PopupNotifyMenu(hwnd);
		break;
		/// 窗口拖拽处理 >>>
	case WM_LBUTTONDOWN:
		lbDown = true;
		// 优化针对鼠标事件捕获（独占） ,需要与ReleaseCapture()成对出现
		SetCapture(hwnd);
		TheFirstPoint = { LOWORD(lParam), HIWORD(lParam) };
		break;
	case WM_MOUSEMOVE:
		// 拖拽
		if (lbDown)
		{
			sprite.SetPlayState(PlayerResult::drag);
			WindowInfo::DragWindowd(TheFirstPoint, hwnd);
		}
		break;
		/// 窗口拖拽处理 <<<

	case MYWM_NOTIFYICON:
		switch (lParam) {
		case  WM_RBUTTONDOWN:
			WindowInfo::PopupNotifyMenu(hwnd);
			break;
		case WM_LBUTTONDOWN:
			MessageBox(NULL, L"将来我一定会学会很多东西的~", L"Mei:", MB_OK);
			break;
		}
		break;
	case WM_COMMAND:
		switch (wParam)
		{
			/// 托盘图标菜单 >>>
		case NTI_QUIT:
			PostQuitMessage(0);
			return 0;
		case NTI_ABM:
			ShellExecute(NULL, TEXT("open"), TEXT("https://kaakira.com"), NULL, NULL, SW_SHOWNORMAL);
			break;
			/// 托盘图标菜单 <<<
		}
		break;
	case WM_LBUTTONUP:
		lbDown = false;
		ReleaseCapture();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{


	// 窗体默认参数 
	int width = 128, height = 128, x = 500, y = 500;
	// 构造并储存windows窗体信息
	petWnd = new WindowInfo(hInstance, TEXT("Hello World"), POINT{ x, y }, SIZE{ width,height }, cmdShow);

	// 显示窗体
	ShowWindow(petWnd->Hwnd, petWnd->CmdShow);

	// 构造精灵控制器
	SpriteHandle spriteHand;
	spriteHand.StartLive(new Animation(petWnd->GetHDCSrc(), &petWnd->GetClientRect()));

	MSG msg = { 0 };
	petWnd->UpdateLayered();
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// 更新窗口信息
		spriteHand.Update();
		petWnd->UpdateLayered();
		Sleep(DELAY_TIME);
	}
	// 托盘图标消失
	Shell_NotifyIcon(NIM_DELETE, &petWnd->TrayIcon);
	return static_cast<int>(msg.wParam);
}
