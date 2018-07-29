#include "WindowInfo.h"

HMENU WindowInfo::ntiMenu = CreatePopupMenu();

WindowInfo::WindowInfo(HINSTANCE hInstance, LPCWSTR wndTitle, POINT point, SIZE wndsize, int cmdShow)
{
	// ���̵����˵�
	AppendMenu(WindowInfo::ntiMenu, MF_STRING, NTI_ABM, L"���߲���");
	AppendMenu(WindowInfo::ntiMenu, MF_STRING, NTI_QUIT, L"�˳�");


	/// info�ֶ� >>>
	this->WinName = wndTitle;
	this->ScreenPoint = point;
	this->WndSize = wndsize;
	this->wndClassName = TEXT("WindowInfo_kaakira");
	this->Hinstance = hInstance;
	this->CmdShow = cmdShow;
	/// info�ֶ� <<<
#pragma region ��ʼ��������� //�������øĶ�

	/// �������� >>>
	WNDCLASSEXW wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WindowInfo::WndProc;
	wndClass.hInstance = this->Hinstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = this->wndClassName;
	// ע�� 
	RegisterClassEx(&wndClass);
	// ���� //WS_EX_LAYERED,
	this->Hwnd = CreateWindowEx(
		// ������չ��ʽ
		WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED,
		// ��������
		this->wndClassName,
		// ���ڱ���
		this->WinName,
		// ������ʽ
		WS_POPUP | WS_VISIBLE, 
		// ���ڳ�ʼ��ĻX����
		this->ScreenPoint.x,
		// ���ڳ�ʼ��ĻY����
		this->ScreenPoint.y,
		// ���ڳ�ʼ���
		this->WndSize.cx,
		// ���ڳ�ʼ�߶�
		this->WndSize.cx,
		// ��������
		NULL,
		// �˵��ľ�������Ӵ��ڵı�ʶ��
		NULL,
		// Ӧ�ó���ʵ���ľ��
		this->Hinstance,
		// ָ�򴰿ڵĴ�������
		this
	);
	/// �������� <<<

	/// ����ͼ�� >>>
	HICON ntfIcon = (HICON)LoadImage(NULL, TEXT("Content\\meiIcon.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	TrayIcon = { 0 };
	TrayIcon.hWnd = this->Hwnd;
	TrayIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	TrayIcon.cbSize = sizeof(NOTIFYICONDATA);
	TrayIcon.uCallbackMessage = MYWM_NOTIFYICON;
	TrayIcon.uID = IDR_MAINFRAME;
	TrayIcon.hIcon = ntfIcon;
	lstrcpy(TrayIcon.szTip, TEXT("=���أ�="));
	Shell_NotifyIcon(NIM_ADD, &TrayIcon);
	/// ����ͼ�� <<<


	/// ��ʼ��hdc  ��������dc >>>
	this->clientRect = { 0,0,WndSize.cx,WndSize.cy };
	this->hdcDst = GetDC(this->Hwnd);
	hdcSrc = CreateCompatibleDC(this->hdcDst);
	HBITMAP memBitmap = ::CreateCompatibleBitmap(hdcDst, WndSize.cx, WndSize.cy);
	::SelectObject(hdcSrc, memBitmap);
	/// ��ʼ��hdc  ��������dc <<<

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
	// ����ڣ��Ա���Ӧ�¼����رյ����˵�
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
