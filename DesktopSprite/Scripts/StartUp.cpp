
#include "DeskpetWindow.h"
using namespace D2DWindow;
DeskpetWindow* petWnd;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{

	int width = 600, height = 600, x = 100, y = 100;

	// 构造精灵窗体
	petWnd = new DeskpetWindow(
		TEXT("Hello World"),
		POINT{ x, y },
		SIZE{ width,height }
	);

	// 初始化wnd窗体
	if (!petWnd->Initialzation(hInstance))
	{
		MessageBox(NULL, TEXT("创建窗体失败"), TEXT("失败"), NULL);
		return 0;
	}

	// 显示窗体
	ShowWindow(petWnd->Hwnd, cmdShow);
	// 进行第一次默认 更新
	petWnd->Update();
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 进行更新  
			petWnd->Update();
		}

		//Cleanup();
		Sleep(50);
	}

	return static_cast<int>(msg.wParam);
}


LRESULT CALLBACK DeskpetWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;
	//DeskpetWindow* petWnd = (DeskpetWindow *)GetWindowLong(hwnd, GWLP_USERDATA);
	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		petWnd->Update();
		EndPaint(hwnd, &paintStruct);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

