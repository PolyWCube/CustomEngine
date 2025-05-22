#ifndef CUSTOM_WIN32_RENDERER
#define CUSTOM_WIN32_RENDERER

#include "renderer.hpp"

namespace Custom {
	namespace Graphic {
		class Win32Renderer : public Renderer {
		public :
			Win32Renderer(void* windowHandle);
			~Win32Renderer();

			inline void BeginFrame() override {
				hDeviceContext = GetDC(hWindow);
				if (!hDeviceContext) {
					Log::Error("Device context unknown...");
				}
			}
			inline void EndFrame() override {
				if (hDeviceContext) {
					ReleaseDC(hWindow, hDeviceContext);
					hDeviceContext = nullptr;
				}
			}
			inline void SwapBuffer() override {
				if (hDeviceContext && hOffscreenDeviceContext) {
					BitBlt(hDeviceContext, 0, 0, currentWidth, currentHeight, hOffscreenDeviceContext, 0, 0, SRCCOPY);
					InvalidateRect(hWindow, NULL, FALSE);
				}
			}

			inline void* GetWindowHandle() const override { return hWindow; }

			inline void SetBuffer(const std::span<RGBAColor<uint8_t, float>>& bufferData, size_t width, size_t height) override {
				if (!hDeviceContext) return;

				if (!ResizeBuffer(width, height)) return;

				uint8_t* dest = bytes.data();
				for (const Graphic::RGBAColor<uint8_t, float>& color : bufferData) {
					*dest++ = static_cast<uint8_t>(color.b);
					*dest++ = static_cast<uint8_t>(color.g);
					*dest++ = static_cast<uint8_t>(color.r);
					*dest++ = static_cast<uint8_t>(color.a);
				}

				/*
				auto rgbaToBgraBytes = [](const Graphic::RGBAColor<uint8_t, float>& color) -> std::vector<uint8_t> {
					return {
						static_cast<uint8_t>(color.b),
						static_cast<uint8_t>(color.g),
						static_cast<uint8_t>(color.r),
						static_cast<uint8_t>(color.a)
					};
				};
				std::vector<uint8_t> bufferBytes;
				size_t totalBytes = 0;
				for (const auto& color : bufferData) {
					std::vector<uint8_t> convertedBytes = rgbaToBgraBytes(color);
					bufferBytes.insert(bufferBytes.end(), convertedBytes.begin(), convertedBytes.end());
					totalBytes += convertedBytes.size();
				}
				bufferBytes.resize(totalBytes);
				*/

				BITMAPINFO bitmapInfo = {};
				bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
				bitmapInfo.bmiHeader.biWidth = static_cast<LONG>(width);
				bitmapInfo.bmiHeader.biHeight = -static_cast<LONG>(height);
				bitmapInfo.bmiHeader.biPlanes = 1;
				bitmapInfo.bmiHeader.biBitCount = 32;
				bitmapInfo.bmiHeader.biCompression = BI_RGB;

				SetDIBitsToDevice(hOffscreenDeviceContext, 0, 0, width, height, 0, 0, 0, height, bytes.data(), &bitmapInfo, DIB_RGB_COLORS);
			}
		private :
			HWND hWindow = nullptr;
			HDC hDeviceContext = nullptr, hOffscreenDeviceContext = nullptr;
			HBITMAP hOffscreenBitmap = nullptr;
			size_t currentWidth = 0, currentHeight = 0;
			std::vector<uint8_t> bytes;

			bool ResizeBuffer(size_t width, size_t height);

			friend class Renderer;
		};
	}
}

#endif