#ifndef CUSTOM_COLOR
#define CUSTOM_COLOR

#include "precompiled_header.hpp"

namespace Custom {
	namespace Graphic {
		template <typename T, typename U, typename D>
		class ColorSpace {
		public :
			~ColorSpace() = default;

			template <typename Self>
			D operator+(this const Self& self, const D& color) { return self.Add(color); }
			template <typename Self>
			D& operator+=(this Self& self, const D& color) { return self.AddAssign(color); }
			template <typename Self>
			D operator-(this const Self& self, const D& color) { return self.Minus(color); }
			template <typename Self>
			D& operator-=(this Self& self, const D& color) { return self.MinusAssign(color); }
			template <typename Self>
			D operator*(this const Self& self, const U& scalar) { return self.Multiply(scalar); }
			template <typename Self>
			D& operator*=(this Self& self, const U& scalar) { return self.MultiplyAssign(scalar); }
			template <typename Self>
			D operator/(this const Self& self, const U& scalar) { return self.Divide(scalar); }
			template <typename Self>
			D& operator/=(this Self& self, const U& scalar) { return self.DivideAssign(scalar); }

			inline virtual std::string ToString() const = 0;
		private :
			template <typename A, typename B, typename C>
			friend std::ostream& operator<<(std::ostream& os, const ColorSpace<A, B, C>& color);
		};

		template <typename T, typename U, typename D>
		std::ostream& operator<<(std::ostream& os, const ColorSpace<T, U, D>& color) {
			os << color.ToString();
			return os;
		}

		template <typename T = uint16_t, typename U = float>
		class RGBColor : public ColorSpace<T, U, RGBColor<T, U>> {
		public :
			RGBColor(T r, T g, T b) : r(r), g(g), b(b) { Limit(); }
			RGBColor() {}

			RGBColor Add(const RGBColor& color) const { return RGBColor(r + color.r, g + color.g, b + color.b).Limit(); }
			RGBColor& AddAssign(const RGBColor& color) {
				r += color.r;
				g += color.g;
				b += color.b;
				return Limit();
			}
			RGBColor Minus(const RGBColor& color) const { return RGBColor(r - color.r, g - color.g, b - color.b).Limit(); }
			RGBColor& MinusAssign(const RGBColor& color) {
				r -= color.r;
				g -= color.g;
				b -= color.b;
				return Limit();
			}
			RGBColor Multiply(const U& scalar) const { return RGBColor(r * scalar, g * scalar, b * scalar).Limit(); }
			RGBColor& MultiplyAssign(const U& scalar) {
				r *= scalar;
				g *= scalar;
				b *= scalar;
				return Limit();
			}
			RGBColor Divide(const U& scalar) const { return RGBColor(r / scalar, g / scalar, b / scalar); }
			RGBColor& DivideAssign(const U& scalar) {
				r /= scalar;
				g /= scalar;
				b /= scalar;
				return *this;
			}

			RGBColor& Limit() {
				if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>) {
					r = Math::Limit<T>(r, 0.0f, 1.0f);
					g = Math::Limit<T>(g, 0.0f, 1.0f);
					b = Math::Limit<T>(b, 0.0f, 1.0f);
				} else {
					r = Math::Limit<T>(r, 0, 255);
					g = Math::Limit<T>(g, 0, 255);
					b = Math::Limit<T>(b, 0, 255);
				}
				return *this;
			}

			std::string ToString() const override {
				return "RGBColor(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
			}

			T r = 0, g = 0, b = 0;
		};

		template <typename T = uint16_t, typename U = float>
		class RGBAColor : public ColorSpace<T, U, RGBAColor<T, U>> {
		public :
			RGBAColor(T r, T g, T b, T a) : r(r), g(g), b(b), a(a) { Limit(); }
			RGBAColor() {}

			RGBAColor Add(const RGBAColor& color) const { return RGBAColor(r + color.r, g + color.g, b + color.b, a).Limit(); }
			RGBAColor& AddAssign(const RGBAColor& color) {
				r += color.r;
				g += color.g;
				b += color.b;
				return Limit();
			}
			RGBAColor Minus(const RGBAColor& color) const { return RGBAColor(r - color.r, g - color.g, b - color.b, a).Limit(); }
			RGBAColor& MinusAssign(const RGBAColor& color) {
				r -= color.r;
				g -= color.g;
				b -= color.b;
				return Limit();
			}
			RGBAColor Multiply(const U& scalar) const { return RGBAColor(r * scalar, g * scalar, b * scalar, a).Limit(); }
			RGBAColor& MultiplyAssign(const U& scalar) {
				r *= scalar;
				g *= scalar;
				b *= scalar;
				return Limit();
			}
			RGBAColor Divide(const U& scalar) const { return RGBAColor(r / scalar, g / scalar, b / scalar, a); }
			RGBAColor& DivideAssign(const U& scalar) {
				r /= scalar;
				g /= scalar;
				b /= scalar;
				return *this;
			}

			RGBAColor& Limit() {
				if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>) {
					r = Math::Limit<T>(r, 0.0f, 1.0f);
					g = Math::Limit<T>(g, 0.0f, 1.0f);
					b = Math::Limit<T>(b, 0.0f, 1.0f);
					a = Math::Limit<T>(a, 0.0f, 1.0f);
				} else {
					r = Math::Limit<T>(r, 0, 255);
					g = Math::Limit<T>(g, 0, 255);
					b = Math::Limit<T>(b, 0, 255);
					a = Math::Limit<T>(a, 0, 255);
				}
				return *this;
			}

			std::string ToString() const override {
				return "RGBAColor(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
			}

			T r = 0, g = 0, b = 0, a = 0;
		};
	}
}

#endif