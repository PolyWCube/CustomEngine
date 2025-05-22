#ifndef CUSTOM_OBJECT_PROPERTY
#define CUSTOM_OBJECT_PROPERTY

#include "precompiled_header.hpp"
#include "component/graphic/window/window.hpp"
#include "component/graphic/renderer/renderer.hpp"

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
	}
}

#endif