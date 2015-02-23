#include "window.h"

#include "../../blowbox/logging.h"
#include "../../blowbox/input/keyboard.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Window::Window() :
		started_(false),
		instance_(NULL),
		handle_(NULL)
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Window::Create(std::string name, int width, int height)
	{
		WNDCLASSA wndclass;
		instance_ = GetModuleHandle(0);
		ZeroMemory(&wndclass, sizeof(WNDCLASSA));
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wndclass.lpfnWndProc = WndProc;
		wndclass.hInstance = instance_;
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wndclass.lpszClassName = name.c_str();
		wndclass.cbWndExtra = sizeof(void*);
		wndclass.cbClsExtra = sizeof(WNDCLASSA);

		BLOW_ASSERT(RegisterClassA(&wndclass), "Failed registering window class!");

		int style = WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_SIZEBOX;

		RECT client_rect;
		client_rect.left = client_rect.top = 0;
		client_rect.right = width;
		client_rect.bottom = height;

		AdjustWindowRect(&client_rect, style, FALSE);
		int actualWidth = client_rect.right - client_rect.left;
		int actualHeight = client_rect.bottom - client_rect.top;
		int x = GetSystemMetrics(SM_CXSCREEN) / 2 - actualWidth / 2;
		int y = GetSystemMetrics(SM_CYSCREEN) / 2 - actualHeight / 2;

		handle_ = CreateWindowA(wndclass.lpszClassName, name.c_str(), style, x, y, actualWidth, actualHeight, GetDesktopWindow(), NULL, wndclass.hInstance, this);

		BLOW_ASSERT(handle_, "Failed creating window!");

		ShowWindow(handle_, SW_SHOWNORMAL);

		started_ = true;
	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnClose()
	{
		SetStarted(false);
	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnSetFocus()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnKillFocus()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnMouseDbl(MouseButton button)
	{
		MouseButtonData buttonEvent;
		buttonEvent.button = button;
		buttonEvent.type = MouseButtonEvent::MouseDblEvent;

		Mouse::Instance()->ReceiveEvent(buttonEvent);
	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnMouseDown(MouseButton button)
	{
		MouseButtonData buttonEvent;
		buttonEvent.button = button;
		buttonEvent.type = MouseButtonEvent::MouseDownEvent;

		Mouse::Instance()->ReceiveEvent(buttonEvent);
	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnMouseUp(MouseButton button)
	{
		MouseButtonData buttonEvent;
		buttonEvent.button = button;
		buttonEvent.type = MouseButtonEvent::MouseUpEvent;

		Mouse::Instance()->ReceiveEvent(buttonEvent);
	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnMouseMove(float x, float y)
	{
		MouseMoveEvent moveEvent;
		moveEvent.x = x;
		moveEvent.y = y;

		Mouse::Instance()->ReceiveEvent(moveEvent);
	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnWheel(LPARAM lParam, WPARAM wParam)
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnKeyDown(LPARAM lParam, WPARAM wParam)
	{
		KeyData evt;
		evt.type = KeyEvent::Pressed;
		evt.key = static_cast<Key>(wParam);

		Keyboard::Instance()->ReceiveEvent(evt);
	}

	//------------------------------------------------------------------------------------------------------
	void Window::OnKeyUp(LPARAM lParam, WPARAM wParam)
	{
		KeyData evt;
		evt.type = KeyEvent::Released;
		evt.key = static_cast<Key>(wParam);

		Keyboard::Instance()->ReceiveEvent(evt);
	}

	//------------------------------------------------------------------------------------------------------
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_CREATE)
		{
			SetWindowLongPtrA(hWnd, GWLP_USERDATA, (LONG_PTR)(((LPCREATESTRUCT)lParam)->lpCreateParams));
			return DefWindowProcA(hWnd, message, wParam, lParam);
		}
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtrA(hWnd, GWLP_USERDATA));

		POINT p;
		if (GetCursorPos(&p))
		{
			ScreenToClient(hWnd, &p);
		}

		switch (message)
		{
		case WM_CLOSE:
			window->OnClose();
			break;
		case WM_SETFOCUS:
			window->OnSetFocus();
			break;
		case WM_KILLFOCUS:
			window->OnKillFocus();
			break;
		case WM_LBUTTONDBLCLK:
			window->OnMouseDbl(MouseLeft);
			break;
		case WM_LBUTTONDOWN:
			window->OnMouseDown(MouseLeft);
			break;
		case WM_LBUTTONUP:
			window->OnMouseUp(MouseLeft);
			break;
		case WM_RBUTTONDBLCLK:
			window->OnMouseDbl(MouseRight);
			break;
		case WM_RBUTTONDOWN:
			window->OnMouseDown(MouseRight);
			break;
		case WM_RBUTTONUP:
			window->OnMouseUp(MouseRight);
			break;
		case WM_MBUTTONDBLCLK:
			window->OnMouseDbl(MouseMiddle);
			break;
		case WM_MBUTTONDOWN:
			window->OnMouseDown(MouseMiddle);
			break;
		case WM_MBUTTONUP:
			window->OnMouseUp(MouseMiddle);
			break;
		case WM_MOUSEMOVE:
			window->OnMouseMove(static_cast<float>(p.x), static_cast<float>(p.y));
			break;
		case WM_KEYDOWN:
			window->OnKeyDown(lParam, wParam);
			break;
		case WM_KEYUP:
			window->OnKeyUp(lParam, wParam);
			break;
		case WM_MOUSEWHEEL:
			window->OnWheel(lParam, wParam);
			break;
		}
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}

	//------------------------------------------------------------------------------------------------------
	void Window::ProcessMessages()
	{
		if (handle_ != nullptr)
		{
			HWND hwnd = static_cast<HWND>(handle_);
			MSG msg;

			while (PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}
	}

	//------------------------------------------------------------------------------------------------------
	bool Window::GetStarted()
	{
		return started_;
	}

	//------------------------------------------------------------------------------------------------------
	void Window::SetStarted(bool val)
	{
		started_ = val;
	}

	//------------------------------------------------------------------------------------------------------
	HINSTANCE Window::getInstance()
	{
		return instance_;
	}

	//------------------------------------------------------------------------------------------------------
	HWND Window::getHandle()
	{
		return handle_;
	}

	//------------------------------------------------------------------------------------------------------
	Window::~Window()
	{

	}
}