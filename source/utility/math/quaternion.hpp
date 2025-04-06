#ifndef CUSTOM_MATH_QUATERNION
#define CUSTOM_MATH_QUATERNION

#include "precompiledheader.hpp"

namespace Custom {
	namespace Math {
		template <typename T = float>
		class Quaternion {
		public :
			constexpr Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y) z(z) {}
			constexpr Quaternion(const Vector3<T>& axis, T angle) {
				T halfAngle = angle * 0.5f;
				T sinHalfAngle = sin(halfAngle);
				w = cos(halfAngle);
				x = axis.x * sinHalfAngle;
				y = axis.y * sinHalfAngle;
				z = axis.z * sinHalfAngle;
			}
		private :
			T w, x, y, z;
		};
	}
}

#endif