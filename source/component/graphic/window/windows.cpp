#include "precompiledheader.hpp"
#include "windows.hpp"
#include "component/log.hpp"
#include "utility/event/window.hpp"
#include "utility/event/key.hpp"
#include "utility/event/mouse.hpp"
#include "utility/event/map/windows.hpp"
#include "utility/math/vector.hpp"

#ifndef UNICODE
#define UNICODE
#endif 

namespace Custom {
	namespace Graphic {
		namespace Window {
			Window* Window::Create(const WindowProperty& windowProperty) {
				return new Win32Window(windowProperty);
			}

			Win32Window::Win32Window(const WindowProperty& windowProperty) : title(StringToWstring(windowProperty.title)), size(windowProperty.size), hWindow(nullptr) {
				Initial(windowProperty);
			}
			Win32Window::~Win32Window() {
				Close();
			}

			LRESULT CALLBACK Win32Window::WindowProcedure(HWND hWindow, UINT message, WPARAM wParameter, LPARAM lParameter) {
				Win32Window* window = nullptr;
				
				if (message == WM_CREATE) {
					CREATESTRUCT* pcs = (CREATESTRUCT*)lParameter;
					window = (Win32Window*)pcs->lpCreateParams;
					SetWindowLongPtr(hWindow, GWLP_USERDATA, (LONG_PTR)window);
				} else window = (Win32Window*)GetWindowLongPtr(hWindow, GWLP_USERDATA);

				if (window) {
					switch (message) {
					case WM_SIZE : {
						Math::Vector2<uint16_t> size(LOWORD(lParameter), HIWORD(lParameter));
						Event::WindowResize event(size);

						window->size = size;
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}

					case WM_KEYDOWN : {
						Event::KeyState keyState = Event::MapVirtualKeyToKeyState(wParameter);
						UINT repeatCount = lParameter & 0xFFFF;
						Event::KeyPress event(keyState, repeatCount);
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_KEYUP : {
						Event::KeyState keyState = Event::MapVirtualKeyToKeyState(wParameter);
						Event::KeyRelease event(keyState);
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}

					case WM_LBUTTONDOWN : {
						Event::MouseState mouseState = Event::MouseState::Left;
						Event::MouseButtonPress event(mouseState);
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_LBUTTONUP : {
						Event::MouseState mouseState = Event::MouseState::Left;
						Event::MouseButtonRelease event(mouseState);
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_RBUTTONDOWN : {
						Event::MouseState mouseState = Event::MouseState::Right;
						Event::MouseButtonPress event(mouseState);
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_RBUTTONUP : {
						Event::MouseState mouseState = Event::MouseState::Right;
						Event::MouseButtonRelease event(mouseState);
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_MOUSEMOVE : {
						Math::Vector2<float> mousePosition(LOWORD(lParameter), HIWORD(lParameter));
						Event::MouseMove event(mousePosition);
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_MOUSEWHEEL: {
						int delta = GET_WHEEL_DELTA_WPARAM(wParameter);
						float offsetValue = static_cast<float>(delta) / WHEEL_DELTA;
						Event::MouseScroll event(Math::Vector2<float>(0.0f, offsetValue));
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_MOUSEHWHEEL: {
						int delta = GET_WHEEL_DELTA_WPARAM(wParameter);
						float offsetValue = static_cast<float>(delta) / WHEEL_DELTA;
						Event::MouseScroll event(Math::Vector2<float>(offsetValue, 0.0f));
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}

					case WM_CLOSE : {
						Event::WindowClose event;
						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_DESTROY :
						PostQuitMessage(0);
						return 0;
					default :
						return DefWindowProcW(hWindow, message, wParameter, lParameter);
					}
				}
				return DefWindowProcW(hWindow, message, wParameter, lParameter);
			}

			void Win32Window::Initial(const WindowProperty& windowProperty) {
				Log::Info("Initial Win32 Window : ", windowProperty.title, ", ", windowProperty.size);
				hInstance = GetModuleHandle(NULL);

				if (!RegisterWindow(hInstance)) {
					Log::Error("Initial Failed : Win32 Window registration unsuccessful.");
					return;
				}

				hWindow = CreateWindowExW(0, L"WindowClass", title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, size.x, size.y, NULL, NULL, hInstance, this);

				if (hWindow == NULL) {
					Log::Error("Initial Failed : Win32 Window creation unsuccessful.");
					return;
				}

				//SetLayeredWindowAttributes(hWindow, 0, 128, LWA_ALPHA);
				Log::Success("Initial Win32 Window successful.");
			}
			void Win32Window::Close() {
				if (hWindow) DestroyWindow(hWindow);
			}

			void Win32Window::Update() {
				MSG message;
				BOOL result = GetMessage(&message, NULL, 0, 0);

				if (result > 0) {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
			void Win32Window::Show() {
				ShowWindow(hWindow, SW_SHOW);
				UpdateWindow(hWindow);
			}

			BOOL Win32Window::RegisterWindow(HINSTANCE hInstance) {
				WNDCLASSEXW windowClass;

				windowClass.cbSize = sizeof(windowClass);
				windowClass.style = CS_HREDRAW | CS_VREDRAW;
				windowClass.lpfnWndProc = WindowProcedure;
				windowClass.cbClsExtra = 0;
				windowClass.cbWndExtra = 0;
				windowClass.hInstance = hInstance;
				windowClass.hIcon = NULL;
				windowClass.hCursor = NULL;
				windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
				windowClass.lpszMenuName = L"Main";
				windowClass.lpszClassName = L"WindowClass";
				windowClass.hIconSm = NULL;

				return RegisterClassExW(&windowClass);
			}

			std::wstring Win32Window::StringToWstring(const std::string& utf8) {
				if (utf8.empty()) return std::wstring();

				int size = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
				if (size == 0) return std::wstring();

				std::wstring utf16(size - 1, L'\0');
				MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &utf16[0], size);
				for (wchar_t c : utf16) {
					Log::Info("Character: ", static_cast<int>(c));
				}

				return utf16;
			}
		}
	}
}