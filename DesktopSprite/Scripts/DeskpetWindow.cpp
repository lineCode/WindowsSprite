#include "DeskpetWindow.h"
using namespace D2DWindow;

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


/// <sumary>Nihao</sumary>
bool DeskpetWindow::Initialzation(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
#pragma region ��ʼ���������//�������øĶ�
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
		// ������չ��ʽ
		NULL,//WS_EX_LAYERED,
			 // ��������
		this->wndClassName,
		// ���ڱ���
		this->WinName,
		// ������ʽ
		WS_OVERLAPPEDWINDOW,
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