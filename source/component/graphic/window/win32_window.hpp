#ifndef CUSTOM_WIN32_WINDOW
#define CUSTOM_WIN32_WINDOW

#include "utility/helper/win32utility.hpp"
#include "window.hpp"

namespace Custom {
	namespace Graphic {
		namespace Window {
			class Win32Window : public Window {
			public :
				Win32Window(const Property& property);
				virtual ~Win32Window();

				void Update() override;
				void SetVisible(bool visible) override;

				void* getWindowHandle() override;

				inline void SetEventCallback(const EventCallback& eventCallback) override { this->eventCallback = eventCallback; }

			private :
				static LRESULT CALLBACK WindowProcedure(HWND hWindow, UINT message, WPARAM wParameter, LPARAM lParameter);

				virtual void Initial(const Property& property);
				virtual void Close();

				std::wstring wTitle;
				EventCallback eventCallback;

				BOOL RegisterWindow(HINSTANCE hInstance);
				HWND hWindow;
				HINSTANCE hInstance;

				static bool isRegisterWindowClass;
			};
		}
	}
}

#endif