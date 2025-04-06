#ifndef CUSTOM_WINDOW_MANAGER
#define CUSTOM_WINDOW_MANAGER

#ifdef CUSTOM_PLATFORM_WINDOWS
	#include "win32_window.hpp"
#endif

namespace Custom {
	namespace Graphic {
		namespace Window {
			std::unique_ptr<Window> Window::Create(const Property& property) {
			#ifdef CUSTOM_PLATFORM_WINDOWS
				return std::make_unique<Win32Window>(property);
			#else
				return nullptr;
			#endif
			}
		}
	}
}

#endif