#ifndef CUSTOM_OBJECT_WINDOW_PROPERTY
#define CUSTOM_OBJECT_WINDOW_PROPERTY

#include "property.hpp"

namespace Custom {
	namespace Object {
		class Window : public Property {
		public :
			Window();

			void Create(const Graphic::Window::Property& property = Graphic::Window::Property());

			std::type_index GetType() const override;
			std::unique_ptr<Property> Clone() const override;

			void SetVisible(bool visible) {
				window->SetVisible(visible);
			}
			void SetEventCallback(std::function<void(Event::Event&)> callback) {
				window->SetEventCallback(callback);
			}
			Graphic::Window::Window* Get() {
				return window.get();
			}
		private :
			std::unique_ptr<Graphic::Window::Window> window;
		};
	}
}

#endif