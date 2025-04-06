#ifndef CUSTOM_OBJECT_PROPERTY
#define CUSTOM_OBJECT_PROPERTY

#include "precompiled_header.hpp"
#include "component/graphic/window/window.hpp"

namespace Custom {
	namespace Object {
		class Property {
		public :
			virtual ~Property() = default;
			virtual std::type_index GetType() const = 0;
			virtual std::unique_ptr<Property> Clone() const = 0;
			//virtual std::string Serialize() const = 0;
			//virtual void Deserialize(const std::string& data) = 0;
		};

		/*template <typename T, size_t N>
		class Transform : public Property {
		public :
			Transform(Math::Transform<T, N> transform) : transform(transform) {}

			std::type_index GetType() const override { return typeid(Transform); }
			std::unique_ptr<Property> Clone() const override { return std::make_unique<Transform>(*this); }
			Math::Transform<T, N> transform;
		};*/

		class Window : public Property {
		public :
			Window();

			void Create(const Graphic::Window::Property& property = Graphic::Window::Property());

			std::type_index GetType() const override;
			std::unique_ptr<Property> Clone() const override;

			void SetVisible(bool visible) {
				window->SetVisible(visible);
			}
			Graphic::Window::Window* GetWindow() {
				return window.get();
			}
		private :
			Window(const Graphic::Window::Property& property);
			std::unique_ptr<Graphic::Window::Window> window;
		};
	}
}

#endif