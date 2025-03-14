#ifndef CUSTOM_MATH_GENERAL
#define CUSTOM_MATH_GENERAL

#include "configuration.hpp"
#include <algorithm>
#include <cmath>
#include <type_traits>

namespace Custom {
	namespace Math {
		template <typename T = DEFAULT_GENERAL_OPERATION>
		T squareRoot(T number, bool castType = false) {
			if (!castType) return std::sqrt(number);
			if constexpr (std::is_same<T, long double>()) {
				return std::sqrtl(number);
			} else if constexpr (std::is_same<T, float>()) {
				return std::sqrtf(number);
			} else return std::sqrt(number);
		}
	}
}

#endif