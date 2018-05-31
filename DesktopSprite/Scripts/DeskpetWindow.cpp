#include "DeskpetWindow.h"
using namespace D2DWindow;

DeskpetWindow::DeskpetWindow(HINSTANCE hInstance, LPCWSTR wndTitle, POINT point, SIZE wndsize, int cmdShow)
{
	this->WinName = wndTitle;
	this->ScreenPoint = point;
	this->WndSize = wndsize;
	this->wndClassName = TEXT("DeskpetWindow_kaakira");
	this->Hinstance = hInstance;
	this->CmdShow = cmdShow;
	if (this->Initialzation()) {
		MessageBox(NULL, TEXT("初始化Deskpet窗体失败"), TEXT("DeskpetWindow"), NULL);
	}
}

DeskpetWindow::~DeskpetWindow()
{
}


/// <sumary>Nihao</sumary>
bool DeskpetWindow::Initialzation()
{
#pragma region 初始化窗体参数//基本不用改动

	WNDCLASSEXW wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = DeskpetWindow::WndProc;
	wndClass.hInstance = this->Hinstance;
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
	// spriteInstace.LoadAnmationResources();
	// UpdateWindow(Hwnd);
}


LPCWSTR DeskpetWindow::GetwndClassName()
{
	return this->wndClassName;
}


bool DeskpetWindow::ShowSpriteWindow(int cmdShow)
{
	this->CmdShow = cmdShow;

#pragma region TODO: 第一次显示窗体需要初始化的配置项

#pragma endregion

	return ShowWindow(this->Hwnd, this->CmdShow);
}
