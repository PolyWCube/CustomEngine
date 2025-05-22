#include "window.hpp"

namespace Custom {
	namespace Object {
		Window::Window() : window(nullptr) {}

		void Window::Create(const Graphic::Window::Property& property) {
			window = std::move(Graphic::Window::Window::Create(property));
		}

		std::type_index Window::GetType() const { return typeid(Window); }
		std::unique_ptr<Property> Window::Clone() const {
			Window* windowProperty = new Window();
			if (window) {
				Graphic::Window::Property property = window->GetProperty();
				windowProperty->Create(property);
			}
			return std::unique_ptr<Property>(windowProperty);
		}
	}
}