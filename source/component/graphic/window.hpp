#ifndef CUSTOM_WINDOW
#define CUSTOM_WINDOW

#include "precompiledheader.hpp"

#include "base.hpp"
#include "utility/event.hpp"
#include "utility/math/vector.hpp"

namespace Custom {
	namespace Graphic {
		namespace Window {
			struct WindowProperty {
				WindowProperty(const std::string& title = "Custom Engine", Math::Vector2<uint16_t> size = Math::Vector2<uint16_t>(1280, 720)) : title(title), size(size) {}

				std::string title;
				Math::Vector2<uint16_t> size;
			};

			class Window {
			public :
				using EventCallback = std::function<void(Event::Event&)>;

				virtual ~Window() {}

				virtual void Update() = 0;
				virtual void Show() = 0;

				virtual uint16_t getWidth() const = 0;
				virtual uint16_t getHeight() const = 0;
				virtual Math::Vector2<uint16_t> getSize() const = 0;

				virtual void SetEventCallback(const EventCallback& eventCallback) = 0;

				static Window* Create(const WindowProperty& windowProperty = WindowProperty());
			};
		}
	}
}

#endif