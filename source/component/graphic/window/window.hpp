#ifndef CUSTOM_WINDOW
#define CUSTOM_WINDOW

#include "precompiled_header.hpp"

namespace Custom {
	namespace Graphic {
		namespace Window {
			struct Property {
				Property(const std::string& title = "Custom Engine", Math::Vector2<uint16_t> size = Math::Vector2<uint16_t>(1280, 720)) : title(title), size(size) {}

				std::string title;
				Math::Vector2<uint16_t> size;
			};

			class Window {
			public :
				using EventCallback = std::function<void(Event::Event&)>;
				Window(const Property& property) : property(property) {}
				virtual ~Window() {}

				virtual void Update() = 0;

				virtual void SetVisible(bool visible) = 0;
				virtual bool IsVisible() const { return visible; }

				virtual void Minimize() = 0;
				virtual void Maximize() = 0;
				virtual void Restore() = 0;
				virtual bool IsMaximize() const = 0;

				inline std::string GetTitle() const { return property.title; }
				inline uint16_t GetWidth() const { return property.size.x; }
				inline uint16_t GetHeight() const { return property.size.y; }
				inline Math::Vector2<uint16_t> GetSize() const { return property.size; }
				Property GetProperty() const { return property; }

				virtual void SetEventCallback(const EventCallback& eventCallback) = 0;
				virtual void* GetWindowHandle() = 0;

				static std::unique_ptr<Window> Create(const Property& property = Property());
			protected :
				Property property;

				bool visible = false;
			};
		}
	}
}

#endif