#include "precompiled_header.hpp"

#include "win32_window.hpp"

#include "utility/event/map/win32.hpp"

#ifndef UNICODE
#define UNICODE
#endif 

namespace Custom {
	namespace Graphic {
		namespace Window {
			bool Win32Window::isRegisterWindowClass = false;

			Win32Window::Win32Window(const Property& property) : Window(property), wTitle(Utility::StringToWstring(property.title)), hWindow(nullptr) {
				if (!isRegisterWindowClass) {
					if (!RegisterWindow(hInstance)) {
						Log::Error("Initial Failed : Win32 Window registration unsuccessful.");
						return;
					}
					else {
						isRegisterWindowClass = true;
						Log::Success("Register Window Class instance success...");
					}
				}
				Initial(property);
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

						window->property.size = size;
						if (window->eventCallback) {
							window->eventCallback(event);
						}

						UpdateWindow(hWindow);
						break;
					}
					case WM_MOVE : {
						Math::Vector2<uint16_t> position(LOWORD(lParameter), HIWORD(lParameter));

						Event::WindowMove event(position);

						if (window->eventCallback) {
							window->eventCallback(event);
						}

						UpdateWindow(hWindow);
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
						Math::Vector2<float> mousePosition(LOWORD(lParameter), HIWORD(lParameter));

						Event::MouseButtonPress event(mouseState, mousePosition);

						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_LBUTTONUP : {
						Event::MouseState mouseState = Event::MouseState::Left;
						Math::Vector2<float> mousePosition(LOWORD(lParameter), HIWORD(lParameter));

						Event::MouseButtonRelease event(mouseState, mousePosition);

						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_RBUTTONDOWN : {
						Event::MouseState mouseState = Event::MouseState::Right;
						Math::Vector2<float> mousePosition(LOWORD(lParameter), HIWORD(lParameter));

						Event::MouseButtonPress event(mouseState, mousePosition);

						if (window->eventCallback) {
							window->eventCallback(event);
						}
						break;
					}
					case WM_RBUTTONUP : {
						Event::MouseState mouseState = Event::MouseState::Right;
						Math::Vector2<float> mousePosition(LOWORD(lParameter), HIWORD(lParameter));

						Event::MouseButtonRelease event(mouseState, mousePosition);

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

			void Win32Window::Initial(const Property& property) {
				Math::Vector2<uint16_t> size = property.size;
				Log::Info("Initial Win32 Window : ", property.title, ", ", size);
				hInstance = GetModuleHandle(NULL);

				hWindow = CreateWindowExW(0, L"WindowClass", wTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, size.x, size.y, NULL, NULL, hInstance, this);

				if (hWindow == NULL) {
					Log::Error("Initial Failed : Win32 Window creation unsuccessful.");
					return;
				}

				Log::Success("Initial Win32 Window successful.");
			}
			void Win32Window::Close() {
				DestroyWindow(hWindow);
			}

			void Win32Window::Update() {
				MSG message;
				BOOL result = GetMessage(&message, NULL, 0, 0);

				if (result > 0) {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}

			void* Win32Window::GetWindowHandle() {
				return hWindow;
			}

			void Win32Window::SetVisible(bool visible) {
				this->visible = visible;
				if (visible) ShowWindow(hWindow, SW_SHOW);
				else ShowWindow(hWindow, SW_HIDE);
				UpdateWindow(hWindow);
			}
			void Win32Window::Minimize() {
				ShowWindow(hWindow, SW_MINIMIZE);
				UpdateWindow(hWindow);
			}
			void Win32Window::Maximize() {
				ShowWindow(hWindow, SW_MAXIMIZE);
				UpdateWindow(hWindow);
			}
			void Win32Window::Restore() {
				ShowWindow(hWindow, SW_RESTORE);
				UpdateWindow(hWindow);
			}
			bool Win32Window::IsMaximize() const {
				return IsZoomed(hWindow);
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
		}
	}
}