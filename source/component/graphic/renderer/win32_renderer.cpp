#include "win32_renderer.hpp"

namespace Custom {
	namespace Graphic {
		Win32Renderer::Win32Renderer(void* windowHandle) : hWindow(static_cast<HWND>(windowHandle)), hDeviceContext(nullptr), hOffscreenDeviceContext(nullptr), currentWidth(0), currentHeight(0) {
			Log::Debug("Win32Renderer created with window handle: ", hWindow);
			bytes.reserve(1920 * 1080 * 4);
		}
		Win32Renderer::~Win32Renderer() {
			if (hOffscreenBitmap) DeleteObject(hOffscreenBitmap);
			if (hOffscreenDeviceContext) DeleteDC(hOffscreenDeviceContext);
			if (hDeviceContext) {
				ReleaseDC(hWindow, hDeviceContext);
			}
			Log::Debug("Win32Renderer renderer destroyed!");
		}

		bool Win32Renderer::ResizeBuffer(size_t width, size_t height) {
			if (width != currentWidth || height != currentHeight) {
				if (hOffscreenBitmap) {
					DeleteObject(hOffscreenBitmap);
					hOffscreenBitmap = nullptr;
				}
				if (hOffscreenDeviceContext) {
					DeleteDC(hOffscreenDeviceContext);
					hOffscreenDeviceContext = nullptr;
				}

				hOffscreenDeviceContext = CreateCompatibleDC(hDeviceContext);
				if (!hOffscreenDeviceContext) return false;

				hOffscreenBitmap = CreateCompatibleBitmap(hDeviceContext, width, height);
				if (!hOffscreenBitmap) {
					DeleteDC(hOffscreenDeviceContext);
					hOffscreenDeviceContext = nullptr;
					return false;
				}

				SelectObject(hOffscreenDeviceContext, hOffscreenBitmap);
				currentWidth = width;
				currentHeight = height;
				bytes.resize(width * height * 4);
			}
			return true;
		}
	}
}