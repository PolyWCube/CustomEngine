#ifndef CUSTOM_WINDOW_WINDOWS
#define CUSTOM_WINDOW_WINDOWS

#include "component/graphic/window.hpp"

namespace Custom {
	namespace Graphic {
		namespace Window {
			class Win32Window : public Window {
			public :
				Win32Window(const WindowProperty& windowProperty);
				virtual ~Win32Window();

				void Update() override;
				void Show() override;

				inline uint16_t getWidth() const override { return size.x; }
				inline uint16_t getHeight() const override { return size.y; }
				inline Math::Vector2<uint16_t> getSize() const override { return size; }

				inline void SetEventCallback(const EventCallback& eventCallback) override { this->eventCallback = eventCallback; }

				static LRESULT CALLBACK WindowProcedure(HWND hWindow, UINT message, WPARAM wParameter, LPARAM lParameter);
			private :
				virtual void Initial(const WindowProperty& windowProperty);
				virtual void Close();

				std::wstring StringToWstring(const std::string& utf8);

				std::wstring title;
				Math::Vector2<uint16_t> size;
				EventCallback eventCallback;

				BOOL RegisterWindow(HINSTANCE hInstance);
				HWND hWindow;
				HINSTANCE hInstance;
			};
		}
	}
}

#endif