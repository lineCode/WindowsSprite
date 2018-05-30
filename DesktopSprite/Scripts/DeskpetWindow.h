#pragma once
// ȥ��win32�����õ��ķ���
#define WIN32_LEAN_AND_MEAN 
#include "SpriteHandle.h"
using namespace Sprite;

namespace D2DWindow {

	class DeskpetWindow
	{

	public:
		DeskpetWindow(LPCWSTR wndTitle, POINT point, SIZE wndsize);
		~DeskpetWindow();

		LPCWSTR GetwndClassName();

		SpriteHandle spriteInstace;




		// Ӧ�ô��ھ��
		HWND Hwnd;
		// ����������ʶ
		LPCWSTR wndClassName;
		// Ӧ�ô��ڱ���
		LPCWSTR WinName;
		// Ӧ��ʵ�����
		HINSTANCE Hinstance;
		// ������Ļ���꣨���Ͻ�)
		POINT ScreenPoint;
		// ������
		SIZE WndSize;

		/// <sumary>
		/// ���������Ӧ�¼������������¼���Ϣ
		/// </sumary>
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

		// ��ʼ������ 
		bool Initialzation(HINSTANCE hInstance, HINSTANCE prevInstance = 0, LPWSTR cmdLine = 0, int cmdShow = 0);

		/// <sumary> �ػ�-���´��� </sumary> 
		void Update(); 


	private:
		
	};
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;} 
#endif


}