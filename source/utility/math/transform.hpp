#ifndef CUSTOM_MATH_TRANSFORM
#define CUSTOM_MATH_TRANSFORM

#include "precompiled_header.hpp"
#include "vector.hpp"

namespace Custom {
	namespace Math {
		template <typename P, typename S, typename R>
		struct Transform {
			P position;
			S size;
			R rotation;
		};
	}
}

#endif