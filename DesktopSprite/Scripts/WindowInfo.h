#pragma once
// ȥ��win32�����õ��ķ���
// #define WIN32_LEAN_AND_MEAN 
#include "../resoures.h"

#define MYWM_NOTIFYICON 0x00101
#define IDR_MAINFRAME  0x00110
#define NOTIFYICONUID 0x000110



	//private const int SW_HIDE = 0; ����		//������������
	//private const int SW_NORMAL = 1;			//������������ 
	//private const int SW_MAXIMIZE = 3;		//��󻯵������� 
	//private const int SW_SHOWNOACTIVATE = 4;	//�����/�ָ�����/��ԭ����
	//private const int SW_SHOW = 5; ����		//��ʾ���壬��С��ʱ��a�����
	//private const int SW_MINIMIZE = 6; ����	//��С��
	//private const int SW_RESTORE = 9;
	//private const int SW_SHOWDEFAULT = 10;

class WindowInfo
{
public:
	WindowInfo(HINSTANCE Hinstance, LPCWSTR wndTitle, POINT point, SIZE wndsize, int cmdShow = SW_SHOWDEFAULT);
	~WindowInfo();

	// Ӧ�ô��ھ��
	HWND Hwnd;
	// Ӧ�ô��ڱ���
	LPCWSTR WinName;
	// Ӧ��ʵ�����
	HINSTANCE Hinstance;
	// ������Ļ���꣨���Ͻ�)
	POINT ScreenPoint;
	// ������
	SIZE WndSize;
	// ��ʾ����ģʽ
	int CmdShow = SW_SHOWDEFAULT;

	// ��ȡ������������
	LPCWSTR GetwndClassName();
	// 
	RECT GetClientRect();
	HDC* GetHDCSrc();
	void UpdateLayered();
	NOTIFYICONDATA TrayIcon;

	// ��ק����
	static void DragWindowd(POINT pt,HWND hwnd);
	// �������̲˵�
	static void PopupNotifyMenu(HWND hwnd );

private:
	// ���̵����˵�
	static HMENU ntiMenu;


	// ����������ʶ
	LPCWSTR wndClassName;
	//NOTIFYICONDATA
	HDC hdcSrc;
	HDC hdcDst;
	RECT rcClient;
	RECT clientRect;

	static	LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};


