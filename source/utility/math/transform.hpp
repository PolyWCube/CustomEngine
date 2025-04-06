#ifndef CUSTOM_MATH_TRANSFORM
#define CUSTOM_MATH_TRANSFORM

#include "precompiled_header.hpp"
#include "vector.hpp"

namespace Custom {
	namespace Math {
		template <typename T, typename U, typename D>
		struct Transform {
			Vector<T, U, D> position;
			Vector<T, U, D> size;
		};

		template <typename T = float, typename U = float>
		struct Transform2 : Transform<T, U, Vector2<T, U>> {
			Vector2<T, U> pivot;
		};
	}
}

#endif