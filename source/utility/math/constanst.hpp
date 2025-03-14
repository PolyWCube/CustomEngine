#ifndef CUSTOM_MATH_CONSTANT
#define CUSTOM_MATH_CONSTANT

#include <numbers>

namespace Custom {
	namespace Math {
		template <typename T>
		constexpr T pi() {
			if constexpr (std::is_same_v<T, double> || std::is_same_v<T, float> || std::is_same_v<T, long double>) {
				return static_cast<T>(std::numbers::pi);
			} else return T{};
		}

		template <typename T>
		constexpr T phi() {
			if constexpr (std::is_same_v<T, double> || std::is_same_v<T, float> || std::is_same_v<T, long double>) {
				return static_cast<T>(std::numbers::phi);
			} else return T{};
		}

		template <typename T>
		constexpr T e() {
			if constexpr (std::is_same_v<T, double> || std::is_same_v<T, float> || std::is_same_v<T, long double>) {
				return static_cast<T>(std::numbers::e);
			} else return T{};
		}
	}
}

#endif