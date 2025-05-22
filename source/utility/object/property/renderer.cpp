#include "renderer.hpp"

namespace Custom {
	namespace Object {
		Renderer::Renderer() : renderer(nullptr) {}

		void Renderer::Create(void* windowHandle) {
			renderer = std::move(Graphic::Renderer::Create(windowHandle));
		}

		std::type_index Renderer::GetType() const { return typeid(Renderer); }
		std::unique_ptr<Property> Renderer::Clone() const {
			Renderer* property = new Renderer();
			if (renderer) {
				void* windowHandle = renderer->GetWindowHandle();
				property->Create(windowHandle);
			}
			return std::unique_ptr<Property>(property);
		}
	}
}