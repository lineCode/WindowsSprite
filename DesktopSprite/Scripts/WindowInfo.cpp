#include "WindowInfo.h"

HMENU WindowInfo::ntiMenu = CreatePopupMenu();

WindowInfo::WindowInfo(HINSTANCE hInstance, LPCWSTR wndTitle, POINT point, SIZE wndsize, int cmdShow)
{
	// 托盘弹出菜单
	AppendMenu(WindowInfo::ntiMenu, MF_STRING, NTI_ABM, L"作者博客");
	AppendMenu(WindowInfo::ntiMenu, MF_STRING, NTI_QUIT, L"退出");


	/// info字段 >>>
	this->WinName = wndTitle;
	this->ScreenPoint = point;
	this->WndSize = wndsize;
	this->wndClassName = TEXT("WindowInfo_kaakira");
	this->Hinstance = hInstance;
	this->CmdShow = cmdShow;
	/// info字段 <<<
#pragma region 初始化窗体参数 //基本不用改动

	/// 创建窗体 >>>
	WNDCLASSEXW wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WindowInfo::WndProc;
	wndClass.hInstance = this->Hinstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = this->wndClassName;
	// 注册 
	RegisterClassEx(&wndClass);
	// 创建 //WS_EX_LAYERED,
	this->Hwnd = CreateWindowEx(
		// 窗口扩展样式
		WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED,
		// 窗体类名
		this->wndClassName,
		// 窗口标题
		this->WinName,
		// 窗口样式
		WS_POPUP | WS_VISIBLE, 
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
	/// 创建窗体 <<<

	/// 托盘图标 >>>
	HICON ntfIcon = (HICON)LoadImage(NULL, TEXT("Content\\meiIcon.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	TrayIcon = { 0 };
	TrayIcon.hWnd = this->Hwnd;
	TrayIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	TrayIcon.cbSize = sizeof(NOTIFYICONDATA);
	TrayIcon.uCallbackMessage = MYWM_NOTIFYICON;
	TrayIcon.uID = IDR_MAINFRAME;
	TrayIcon.hIcon = ntfIcon;
	lstrcpy(TrayIcon.szTip, TEXT("=￣ω￣="));
	Shell_NotifyIcon(NIM_ADD, &TrayIcon);
	/// 托盘图标 <<<


	/// 初始化hdc  创建兼容dc >>>
	this->clientRect = { 0,0,WndSize.cx,WndSize.cy };
	this->hdcDst = GetDC(this->Hwnd);
	hdcSrc = CreateCompatibleDC(this->hdcDst);
	HBITMAP memBitmap = ::CreateCompatibleBitmap(hdcDst, WndSize.cx, WndSize.cy);
	::SelectObject(hdcSrc, memBitmap);
	/// 初始化hdc  创建兼容dc <<<

#pragma endregion
}

WindowInfo::~WindowInfo()
{
	
}

LPCWSTR WindowInfo::GetwndClassName()
{
	return this->wndClassName;
}

RECT WindowInfo::GetClientRect()
{
	return this->clientRect;
}

HDC *WindowInfo::GetHDCSrc()
{
	return &this->hdcSrc;
}

void WindowInfo::UpdateLayered()
{
	/*GetWindowRect(this->Hwnd, &this->rcClient);
	this->ScreenPoint = { rcClient.left,rcClient.top };*/
	POINT ptSrc = { 0 };
	BLENDFUNCTION bf;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = 255;
	::UpdateLayeredWindow(this->Hwnd, this->hdcDst, NULL, &this->WndSize, this->hdcSrc, &ptSrc, NULL, &bf, ULW_ALPHA);
}


void WindowInfo::PopupNotifyMenu(HWND hwnd)
{
	POINT pt;
	GetCursorPos(&pt);
	// 激活窗口，以便响应事件，关闭弹出菜单
	SetForegroundWindow(hwnd);
	TrackPopupMenu(ntiMenu, TPM_RIGHTBUTTON, pt.x, pt.y, NULL, hwnd, NULL);
}

void WindowInfo::DragWindowd(POINT pt, HWND hwnd)
{
	POINT cursor;
	GetCursorPos(&cursor);
	cursor.x -= pt.x;
	cursor.y -= pt.y;
	SetWindowPos(hwnd, NULL, cursor.x, cursor.y, NULL, NULL, SWP_NOREDRAW | SWP_NOSIZE | SWP_NOZORDER);
}
