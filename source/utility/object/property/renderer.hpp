#ifndef CUSTOM_OBJECT_RENDERER_PROPERTY
#define CUSTOM_OBJECT_RENDERER_PROPERTY

#include "property.hpp"

namespace Custom {
	namespace Object {
		class Renderer : public Property {
		public :
			Renderer();

			void Create(void* windowHandle);

			inline void BeginFrame() const { renderer->BeginFrame(); }
			inline void EndFrame() const { renderer-> EndFrame(); }

			template <typename Buffer>
			inline void SetBuffer(const Buffer& buffer, size_t width, size_t height) { renderer->SetBuffer(buffer, width, height); }

			inline void SwapBuffer() const { renderer->SwapBuffer(); }

			std::type_index GetType() const override;
			std::unique_ptr<Property> Clone() const override;

			Graphic::Renderer* Get() {
				return renderer.get();
			}
			private :
			std::unique_ptr<Graphic::Renderer> renderer;
		};
	}
}

#endif