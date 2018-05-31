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
		MessageBox(NULL, TEXT("��ʼ��Deskpet����ʧ��"), TEXT("DeskpetWindow"), NULL);
	}
}

DeskpetWindow::~DeskpetWindow()
{
}


/// <sumary>Nihao</sumary>
bool DeskpetWindow::Initialzation()
{
#pragma region ��ʼ���������//�������øĶ�

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

#pragma region TODO: ��һ����ʾ������Ҫ��ʼ����������

#pragma endregion

	return ShowWindow(this->Hwnd, this->CmdShow);
}
