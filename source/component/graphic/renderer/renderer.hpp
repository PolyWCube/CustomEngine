#ifndef CUSTOM_RENDERER
#define CUSTOM_RENDERER

#include "precompiled_header.hpp"
#include "component/graphic/color.hpp"
#include "utility/object/buffer.hpp"

namespace Custom {
	namespace Graphic {
		class Renderer {
		public :
			~Renderer() = default;

			virtual void BeginFrame() = 0;
			virtual void EndFrame() = 0;

			virtual void SetBuffer(const std::span<RGBAColor<uint8_t, float>>& bufferData, size_t width, size_t height) = 0;
			virtual void SwapBuffer() = 0;

			virtual void* GetWindowHandle() const = 0;

			static std::unique_ptr<Renderer> Create(void* windowHandle);
		protected :
			
		};
	}
}

#endif