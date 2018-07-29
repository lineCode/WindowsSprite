
#include "WindowInfo.h"
#include "SpriteHandle.h"


using namespace Sprite;

// ������Ϣ�����촰�壩
WindowInfo* petWnd;
// �����ܿ�����������Ĵ��ԣ�
SpriteHandle sprite;
// ����������
bool	lbDown = false;
// ��갴��ʱ���ڴ��������
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
		/// ������ק���� >>>
	case WM_LBUTTONDOWN:
		lbDown = true;
		// �Ż��������¼����񣨶�ռ�� ,��Ҫ��ReleaseCapture()�ɶԳ���
		SetCapture(hwnd);
		TheFirstPoint = { LOWORD(lParam), HIWORD(lParam) };
		break;
	case WM_MOUSEMOVE:
		// ��ק
		if (lbDown)
		{
			sprite.SetPlayState(PlayerResult::drag);
			WindowInfo::DragWindowd(TheFirstPoint, hwnd);
		}
		break;
		/// ������ק���� <<<

	case MYWM_NOTIFYICON:
		switch (lParam) {
		case  WM_RBUTTONDOWN:
			WindowInfo::PopupNotifyMenu(hwnd);
			break;
		case WM_LBUTTONDOWN:
			MessageBox(NULL, L"������һ����ѧ��ܶණ����~", L"Mei:", MB_OK);
			break;
		}
		break;
	case WM_COMMAND:
		switch (wParam)
		{
			/// ����ͼ��˵� >>>
		case NTI_QUIT:
			PostQuitMessage(0);
			return 0;
		case NTI_ABM:
			ShellExecute(NULL, TEXT("open"), TEXT("https://kaakira.com"), NULL, NULL, SW_SHOWNORMAL);
			break;
			/// ����ͼ��˵� <<<
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


	// ����Ĭ�ϲ��� 
	int width = 128, height = 128, x = 500, y = 500;
	// ���첢����windows������Ϣ
	petWnd = new WindowInfo(hInstance, TEXT("Hello World"), POINT{ x, y }, SIZE{ width,height }, cmdShow);

	// ��ʾ����
	ShowWindow(petWnd->Hwnd, petWnd->CmdShow);

	// ���쾫�������
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

		// ���´�����Ϣ
		spriteHand.Update();
		petWnd->UpdateLayered();
		Sleep(DELAY_TIME);
	}
	// ����ͼ����ʧ
	Shell_NotifyIcon(NIM_DELETE, &petWnd->TrayIcon);
	return static_cast<int>(msg.wParam);
}
