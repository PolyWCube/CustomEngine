#include "property.hpp"

namespace Custom {
	namespace Object {
		Window::Window(const Graphic::Window::Property& property) {
			window = std::move(Graphic::Window::Window::Create(property));
		}
		Window::Window() {}

		void Window::Create(const Graphic::Window::Property& property) {
			window = std::move(Graphic::Window::Window::Create(property));
		}

		std::type_index Window::GetType() const { return typeid(Window); }
		std::unique_ptr<Property> Window::Clone() const {
			if (window){
				Graphic::Window::Property property = window->GetProperty();
				return std::unique_ptr<Property>(new Window(property));
			} else return std::unique_ptr<Property>(new Window());
		}
	}
}