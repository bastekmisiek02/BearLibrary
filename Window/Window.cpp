#include "Window.h"

#include <Windows.h>

#include "Collections/DynamicArray/DynamicArray.h"

namespace Bear
{
	static Collections::DynamicArray<Window*> windows;

	Window* SearchWindow(const HWND& instance)
	{
		for (ULInt i = 0; i < windows.Length(); i++)
		{
			if (instance == windows[i]->GetHandle())
				return windows[i];
		}

		return nullptr;
	}

	static LInt WinProc(void* instance, UInt msg, ULInt wParam, LInt lParam)
	{
		HWND attachment = (HWND)instance;

		switch (msg)
		{
			case WM_MOUSEMOVE:
			{
				if (Window* window = SearchWindow(attachment))
				{
					if (window->OnMouseMoveCallback)
						window->OnMouseMoveCallback(window, { LOWORD(lParam), HIWORD(lParam) });
				}

				break;
			}
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_XBUTTONDOWN:
			{
				if (Window* window = SearchWindow(attachment))
				{
					if (window->OnMouseClickCallback)
						window->OnMouseClickCallback(window, (Window::MouseButton)wParam, { LOWORD(lParam), HIWORD(lParam) }, wParam & MK_CONTROL, wParam & MK_SHIFT);
				}

				break;
			}
			case WM_MOUSEWHEEL:
			{
				if (Window* window = SearchWindow(attachment))
				{
					if (window->OnMouseScrollCallback)
						window->OnMouseScrollCallback(window, (HIWORD(wParam) == WHEEL_DELTA));
				}

				break;
			}
			case WM_CHAR:
			{
				if (Window* window = SearchWindow(attachment))
				{
					if (window->OnKeyClickCallback)
						window->OnKeyClickCallback(window, (Window::KeyCode)wParam);
				}

				break;
			}
			case WM_MOVE:
			{
				if (Window* window = SearchWindow(attachment))
				{
					if (window->OnMoveCallback)
						window->OnMoveCallback(window, { LOWORD(lParam), HIWORD(lParam) });
				}

				break;
			}
			case WM_GETMINMAXINFO:
			{
				MINMAXINFO* mmi = (MINMAXINFO*)lParam;

				if (Window* window = SearchWindow(attachment))
				{
					if (window->minSize.x || window->minSize.y)
					{
						mmi->ptMinTrackSize.x = window->minSize.x;
						mmi->ptMinTrackSize.y = window->minSize.y;
					}

					if (window->maxSize.x || window->maxSize.y)
					{
						mmi->ptMaxTrackSize.x = window->maxSize.x;
						mmi->ptMaxTrackSize.y = window->maxSize.y;
					}

					window->minSize = { mmi->ptMinTrackSize.x, mmi->ptMinTrackSize.y };
					window->maxSize = { mmi->ptMaxTrackSize.x, mmi->ptMaxTrackSize.y };
				}

				break;
			}
			case WM_SIZE:
			{
				if (Window* window = SearchWindow(attachment))
				{
					if (window->OnResizeCallback)
					{
						Window::State state = Window::State::Restored;

						switch (wParam)
						{
						case SIZE_RESTORED:
						{
							state = Window::State::Restored;
							break;
						}
						case SIZE_MINIMIZED:
						{
							state = Window::State::Minimized;
							break;
						}
						case SIZE_MAXIMIZED:
						{
							state = Window::State::Maximized;
							break;
						}
						default:
							break;
						}

						window->OnResizeCallback(window, { LOWORD(lParam), HIWORD(lParam) }, state);
					}
				}

				break;
			}
			case WM_CLOSE:
			{
				const char* nameClass = nullptr;

				if (Window* window = SearchWindow(attachment))
				{
					if (window->OnCloseCallback)
						window->OnCloseCallback(window);

					nameClass = window->nameClass;
				}

				DestroyWindow(attachment);

				if (nameClass)
					UnregisterClassA(nameClass, nullptr);

				break;
			}
			case WM_DESTROY:
			{
				if (Window* window = SearchWindow(attachment))
				{
					if (window->OnDestroyCallback)
						window->OnDestroyCallback(window);

					window->destroyed = true;
				}

				bool quit = true;

				for (const auto& window : windows)
				{
					if (!window->destroyed)
					{
						quit = false;
						break;
					}
				}

				if (quit)
					PostQuitMessage(0);

				break;
			}
			default:
				return DefWindowProcA(attachment, msg, wParam, lParam);
		}

		return 0;
	}

	Window::Window(const Vector& size, const Vector& position, const char* title, const PointerType& pointerType, const Window* parent, const char* className, const char* pathToTaskBarImage, const char* pathToImage, const State& windowState, const Style& windowStyle)
		: style(windowStyle), destroyed(false), OnCloseCallback(nullptr), OnDestroyCallback(nullptr), OnKeyClickCallback(nullptr), OnMouseClickCallback(nullptr), OnMouseMoveCallback(nullptr), OnMouseScrollCallback(nullptr), OnMoveCallback(nullptr), OnResizeCallback(nullptr), minSize(), maxSize()
	{
		nameClass = !className ? title : className;

		WNDCLASSEXA wc{};
		wc.cbClsExtra = 0;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.hCursor = LoadCursor(nullptr, MAKEINTRESOURCE(pointerType));
		wc.hIcon = pathToTaskBarImage ? (HICON)LoadImageA(nullptr, pathToTaskBarImage, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED) : LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = pathToImage ? (HICON)LoadImageA(nullptr, pathToImage, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED) : LoadIcon(nullptr, IDI_APPLICATION);
		wc.hInstance = nullptr;
		wc.lpfnWndProc = (WNDPROC)WinProc;
		wc.lpszClassName = nameClass;
		wc.lpszMenuName = nullptr;
		wc.style = 0;

		if (!RegisterClassExA(&wc))
			return;

		this->handle = CreateWindowExA(0, nameClass, title, (DWORD)windowStyle, position.x, position.y, size.x, size.y, nullptr, nullptr, nullptr, nullptr);

		if (!this->handle)
			return;

		this->SetState(windowState);
		UpdateWindow((HWND)this->handle);

		windows.Add(this);

		if (parent)
			SetParent((HWND)this->handle, (HWND)parent->handle);

		this->title = title;
	}

	Window::Window(const Vector& size, const Vector& position, const char* title, const char* pointerFileName, const Window* parent, const char* className, const char* pathToTaskBarImage, const char* pathToImage, const State& windowState, const Style& windowStyle)
		: style(windowStyle), destroyed(false), OnMouseMoveCallback(nullptr), OnMouseClickCallback(nullptr), OnMouseScrollCallback(nullptr), OnKeyClickCallback(nullptr), OnMoveCallback(nullptr), OnResizeCallback(nullptr), OnCloseCallback(nullptr), OnDestroyCallback(nullptr), minSize(), maxSize()
	{
		nameClass = !className ? title : className;

		WNDCLASSEXA wc{};
		wc.cbClsExtra = 0;
		wc.cbSize = sizeof(WNDCLASSEXA);
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.hCursor = (HCURSOR)LoadCursorFromFileA(nullptr);
		wc.hIcon = pathToTaskBarImage ? (HICON)LoadImageA(nullptr, pathToTaskBarImage, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED) : LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = pathToImage ? (HICON)LoadImageA(nullptr, pathToImage, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED) : LoadIcon(nullptr, IDI_APPLICATION);
		wc.hInstance = nullptr;
		wc.lpfnWndProc = (WNDPROC)WinProc;
		wc.lpszClassName = nameClass;
		wc.lpszMenuName = nullptr;
		wc.style = 0;

		if (!RegisterClassExA(&wc))
			return;

		this->handle = CreateWindowExA(0, nameClass, title, (DWORD)windowStyle, position.x, position.y, size.x, size.y, nullptr, nullptr, nullptr, nullptr);

		if (!this->handle)
			return;

		this->SetState(windowState);
		UpdateWindow((HWND)this->handle);

		windows.Add(this);

		if (parent)
			SetParent((HWND)this->handle, (HWND)parent->handle);

		this->title = title;
	}

	Window::~Window()
	{
		destroyed = true;

		windows.Remove(this);
	}

	void* Window::GetHandle() const
	{
		return handle;
	}

	void* Window::GetInstance() const
	{
		return (HINSTANCE)GetModuleHandleA(nullptr);
	}

	const char* Window::GetTitle() const
	{
		return title;
	}

	void Window::SetTitle(const char* newTitle)
	{
		SetWindowTextA((HWND)handle, newTitle);
		title = newTitle;
	}

	Window::Vector Window::GetSize() const
	{
		RECT point;
		GetClientRect((HWND)handle, &point);

		return { point.right, point.bottom };
	}

	void Window::SetSize(const Vector& newSize)
	{
		SetWindowPos((HWND)handle, nullptr, 0, 0, newSize.x, newSize.y, SWP_NOMOVE);
	}

	Window::Vector Window::GetPosition() const
	{
		RECT point;
		GetWindowRect((HWND)handle, &point);

		return { point.left + 8, point.top + 31 };
	}

	void Window::SetPosition(const Vector& newPosition)
	{
		SetWindowPos((HWND)handle, nullptr, newPosition.x, newPosition.y, 0, 0, SWP_NOSIZE);
	}

	Window::State Window::GetState() const
	{
		WINDOWPLACEMENT windowState{};
		windowState.length = sizeof(WINDOWPLACEMENT);

		GetWindowPlacement((HWND)this->handle, &windowState);

		return (Window::State)windowState.showCmd;
	}

	void Window::SetState(const State& newState)
	{
		if (newState == State::FullScreen)
		{
			SetWindowLongA((HWND)handle, GWL_STYLE, WS_VISIBLE);
			ShowWindow((HWND)this->handle, (int)State::Maximized);
		}
		else
		{
			SetWindowLongA((HWND)handle, GWL_STYLE, (LONG)style);
			ShowWindow((HWND)this->handle, (int)newState);
		}
	}

	Window::Vector Window::GetMinSize() const
	{
		return minSize;
	}

	void Window::SetMinSize(const Vector& size)
	{
		this->minSize = size;
	}

	Window::Vector Window::GetMaxSize() const
	{
		return maxSize;
	}

	void Window::SetMaxSize(const Vector& size)
	{
		this->maxSize = size;
	}

	void Window::SetCursor(const PointerType& type)
	{
		::SetCursor(LoadCursorA(nullptr, MAKEINTRESOURCEA(type)));
	}

	void Window::SetCursor(const char* pointerFileName)
	{
		::SetCursor(LoadCursorFromFileA(pointerFileName));
	}

	void Window::SetMousePosition(const Vector& newPosition)
	{
		if (GetActiveWindow() == handle)
		{
			const Vector&& position = GetPosition();

			SetPhysicalCursorPos(position.x + newPosition.x, position.y + newPosition.y);
		}
	}

	Window::Vector Window::GetMousePosition() const
	{
		POINT point;
		GetPhysicalCursorPos(&point);

		int x = point.x - this->GetPosition().x;
		int y = point.y - this->GetPosition().y;

		if (x < 0 || (y < 0))
		{
			x = -1;
			y = -1;
		}

		const Vector&& size = this->GetSize();

		if (x >= size.x || y >= size.y)
		{
			x = -1;
			y = -1;
		}

		return { x, y };
	}

	bool Window::IsDestroyed() const
	{
		return destroyed;
	}

	void Window::PeekEvents() const
	{
		MSG msg{};

		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	void Window::WaitEvents() const
	{
		WaitMessage();

		MSG msg{};

		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	const Window::Vector Window::GetMonitorResolution()
	{
		return { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	}

	const bool Window::IsKeyDown(const char& key) const
	{
		if (GetActiveWindow() == handle)
			return GetAsyncKeyState(key);

		return false;
	}

	void Window::LockMousePosition(const Vector& position, const Vector& size) const
	{
		const Vector& windowPosition = GetPosition();
		const Vector& windowSize = GetSize();

		RECT rect{ position.x + windowPosition.x, position.y + windowPosition.y, position.x + windowPosition.x + size.x, position.y + windowPosition.y + size.y };

		if (rect.right > windowPosition.x + windowSize.x)
			rect.right = windowPosition.x + windowSize.x;

		if (rect.bottom > windowPosition.y + windowSize.y)
			rect.bottom = windowPosition.y + windowSize.y;

		ClipCursor(&rect);
	}

	void Window::HideCursor() const
	{
		::ShowCursor(false);
	}

	void Window::ShowCursor() const
	{
		::ShowCursor(true);
	}
}