/**
 * @file	Window.cpp
 * @brief	ウィンドウクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Window.h"

#include "..\Debugger\Debugger.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Global Function
	//----------------------------------------------------------------------
	LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
	{
		switch (_message)
		{
		case WM_CLOSE:
			DestroyWindow(_hwnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;
		case WM_KEYDOWN:
			switch (static_cast<CHAR>(_wParam))
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				return 0;
				break;
			}
			break;
		}

		return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	Window::Window() :
		m_hWnd(nullptr)
	{
	}
	
	Window::~Window()
	{
	}
	
	
	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool Window::Initialize(
		LPCTSTR _pWindowName,
		int _windowWidth,
		int _windowHeight,
		DWORD _style)
	{
		// ウィンドウクラスの設定と登録.
		WNDCLASSEX WindowClass;
		WindowClass.cbSize			= sizeof(WindowClass);
		WindowClass.style			= CS_HREDRAW | CS_VREDRAW;
		WindowClass.lpfnWndProc		= WindowProc;
		WindowClass.cbClsExtra		= 0;
		WindowClass.cbWndExtra		= 0;
		WindowClass.hInstance		= GetModuleHandle(nullptr);
		WindowClass.hIcon			= LoadIcon(nullptr, IDI_APPLICATION);
		WindowClass.hCursor			= LoadCursor(nullptr, IDC_ARROW);
		WindowClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
		WindowClass.lpszMenuName	= nullptr;
		WindowClass.lpszClassName	= _pWindowName;
		WindowClass.hIconSm			= LoadIcon(nullptr, IDI_APPLICATION);
		RegisterClassEx(&WindowClass);
	
		// ウィンドウの生成.
		m_hWnd = CreateWindow(
			_pWindowName,
			_pWindowName,
			_style,
			0,
			0,
			_windowWidth,
			_windowHeight,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			nullptr);
	
		if (m_hWnd == nullptr)
		{
			OutputErrorLog("ウィンドウの作成に失敗しました");
			return false;
		}
	
		UpdateWindow(m_hWnd);
	
		ZeroMemory(&m_WindowMsg, sizeof(m_WindowMsg));

		return true;
	}

	void Window::Finalize()
	{
		if (m_hWnd != nullptr)	SendMessage(m_hWnd, WM_CLOSE, 0, 0);
	}

	bool Window::Update()
	{
		if (m_WindowMsg.message != WM_QUIT)
		{
			if (PeekMessage(&m_WindowMsg, nullptr, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&m_WindowMsg);
				DispatchMessage(&m_WindowMsg);
			}

			return false;
		}

		m_hWnd = nullptr;

		return true;
	}
}

