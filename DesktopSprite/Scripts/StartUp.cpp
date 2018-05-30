
#include "DeskpetWindow.h"
using namespace D2DWindow;
DeskpetWindow* petWnd;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{

	int width = 600, height = 600, x = 100, y = 100;

	// ���쾫�鴰��
	petWnd = new DeskpetWindow(
		TEXT("Hello World"),
		POINT{ x, y },
		SIZE{ width,height }
	);

	// ��ʼ��wnd����
	if (!petWnd->Initialzation(hInstance))
	{
		MessageBox(NULL, TEXT("��������ʧ��"), TEXT("ʧ��"), NULL);
		return 0;
	}

	// ��ʾ����
	ShowWindow(petWnd->Hwnd, cmdShow);
	// ���е�һ��Ĭ�� ����
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
			// ���и���  
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

