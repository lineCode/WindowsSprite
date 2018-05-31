#pragma once
// ȥ��win32�����õ��ķ���
#define WIN32_LEAN_AND_MEAN 
#include "SpriteHandle.h"
using namespace Sprite;

namespace D2DWindow {

	//private const int SW_HIDE = 0; ����		//������������
	//private const int SW_NORMAL = 1;			//������������ 
	//private const int SW_MAXIMIZE = 3;		//��󻯵������� 
	//private const int SW_SHOWNOACTIVATE = 4;	//�����/�ָ�����/��ԭ����
	//private const int SW_SHOW = 5; ����		//��ʾ���壬��С��ʱ�������
	//private const int SW_MINIMIZE = 6; ����	//��С��
	//private const int SW_RESTORE = 9;
	//private const int SW_SHOWDEFAULT = 10;
	class DeskpetWindow
	{

	public:
		DeskpetWindow(HINSTANCE Hinstance,LPCWSTR wndTitle, POINT point, SIZE wndsize,int cmdShow = SW_SHOWDEFAULT);
		~DeskpetWindow();

		// �����ܿ�������"����Ĵ���"��
		SpriteHandle spriteInstace;
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


		// ���������Ӧ�¼������������¼���Ϣ
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		// �ػ�-���´���  
		void Update();
		// ��ȡ������������
		LPCWSTR GetwndClassName();
		// ��ʾ���鴰��
		bool ShowSpriteWindow(int cmdShow = SW_SHOWDEFAULT);

	private:
		// ����������ʶ
		LPCWSTR wndClassName;
		 


		// ��ʼ������ 
		bool Initialzation();

	};


}