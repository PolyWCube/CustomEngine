#ifndef CUSTOM_RENDERER_MANAGER
#define CUSTOM_RENDERER_MANAGER

#ifdef CUSTOM_PLATFORM_WINDOWS
	#include "win32_renderer.hpp"
#endif

namespace Custom {
	namespace Graphic {
		std::unique_ptr<Renderer> Renderer::Create(void* windowHandle) {
		#ifdef CUSTOM_PLATFORM_WINDOWS
			return std::make_unique<Win32Renderer>(windowHandle);
		#else
			return nullptr;
		#endif
		}
	}
}

#endif