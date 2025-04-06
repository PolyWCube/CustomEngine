#ifndef CUSTOM_MATH_VECTOR
#define CUSTOM_MATH_VECTOR

#include "precompiled_header.hpp"
#include "general.hpp"

namespace Custom {
	namespace Math {
		template <typename T, typename U, typename D>
		class Vector {
		public :
			D operator+(const D& vector) const { return static_cast<D const&>(*this).Add(vector); }
			D& operator+=(const D& vector) { return static_cast<D&>(*this).AddAssign(vector); }
			D operator-(const D& vector) const { return static_cast<D const&>(*this).Minus(vector); }
			D& operator-=(const D& vector) { return static_cast<D&>(*this).MinusAssign(vector); }
			D operator*(const T& scalar) const { return static_cast<D const&>(*this).Multiply(scalar); }
			D& operator*=(const T& scalar) { return static_cast<D&>(*this).MultiplyAssign(scalar); }
			D operator/(const T& scalar) const { return static_cast<D const&>(*this).Divide(scalar); }
			D& operator/=(const T& scalar) { return static_cast<D&>(*this).DivideAssign(scalar); }

			U norm() const { return static_cast<D const&>(*this).CalculateNorm(); }

			virtual D Add(const D& vector) const = 0;
			virtual D& AddAssign(const D& vector) = 0;
			virtual D Minus(const D& vector) const = 0;
			virtual D& MinusAssign(const D& vector) = 0;
			virtual D Multiply(const T& scalar) const = 0;
			virtual D& MultiplyAssign(const T& scalar) = 0;
			virtual D Divide(const T& scalar) const = 0;
			virtual D& DivideAssign(const T& scalar) = 0;

			virtual U CalculateNorm() const = 0;

			friend std::ostream& operator<<(std::ostream& os, const Vector<T, U, D>& vector) {
				os << vector.toString();
				return os;
			}
		protected :
			virtual std::string toString() const = 0;
		};

		template <typename T = float, typename U = float>
		class Vector2 : public Vector<T, U, Vector2<T, U>> {
		public:
			constexpr Vector2(T x, T y) : x(x), y(y) {}

			static constexpr Vector2 zero() { return Vector2(0, 0); }
			static constexpr Vector2 one() { return Vector2(1, 1); }
			static constexpr Vector2 up() { return Vector2(0, 1); }
			static constexpr Vector2 down() { return Vector2(0, -1); }
			static constexpr Vector2 left() { return Vector2(-1, 0); }
			static constexpr Vector2 right() { return Vector2(1, 0); }

			Vector2 Add(const Vector2& vector) const override { return Vector2(x + vector.x, y + vector.y); }
			Vector2& AddAssign(const Vector2& vector) override {
				x += vector.x;
				y += vector.y;
				return *this;
			}
			Vector2 Minus(const Vector2& vector) const override { return Vector2(x - vector.x, y - vector.y); }
			Vector2& MinusAssign(const Vector2& vector) override {
				x -= vector.x;
				y -= vector.y;
				return *this;
			}
			Vector2 Multiply(const T& scalar) const override { return Vector2(x * scalar, y * scalar); }
			Vector2& MultiplyAssign(const T& scalar) override {
				x *= scalar;
				y *= scalar;
				return *this;
			}
			friend Vector2 operator*(const T& scalar, const Vector2& vector) { return vector * scalar; }
			Vector2 Divide(const T& scalar) const override { return Vector2(x / scalar, y / scalar);}
			Vector2& DivideAssign(const T& scalar) override {
				x /= scalar;
				y /= scalar;
				return *this;
			}

			U CalculateNorm() const override { return squareRoot<U>(static_cast<U>(x * x + y * y)); }

			template <typename V>
			Vector2(const Vector2<V>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) {}

			inline std::string toString() const override {
				return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
			}
			T x, y;
		};

		template <typename T = float, typename U = float>
		class Vector3 : Vector<T, U, Vector3<T, U>> {
		public:
			constexpr Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

			static constexpr Vector3 zero() { return Vector3(0, 0, 0); }
			static constexpr Vector3 one() { return Vector3(1, 1, 1); }
			static constexpr Vector3 up() { return Vector3(0, 1, 0); }
			static constexpr Vector3 down() { return Vector3(0, -1, 0); }
			static constexpr Vector3 left() { return Vector3(-1, 0, 0); }
			static constexpr Vector3 right() { return Vector3(1, 0, 0); }
			static constexpr Vector3 forward() { return Vector3(0, 0, 1); }
			static constexpr Vector3 backward() { return Vector3(0, 0, 1); }

			Vector3 Add(const Vector3& vector) const override { return Vector3(x + vector.x, y + vector.y, z + vector.z); }
			Vector3 operator+(const Vector2<T>& vector) const { return Vector3(x + vector.x, y + vector.y, z); }
			Vector3& AddAssign(const Vector3& vector) override {
				x += vector.x;
				y += vector.y;
				z += vector.z;
				return *this;
			}
			Vector3& operator+=(const Vector2<T>& vector) {
				x += vector.x;
				y += vector.y;
				return *this;
			}
			Vector3 Minus(const Vector3& vector) const override { return Vector3(x - vector.x, y - vector.y, z - vector.z); }
			Vector3 operator-(const Vector2<T>& vector) const { return Vector3(x - vector.x, y - vector.y, z); }
			Vector3& MinusAssign(const Vector3& vector) override {
				x -= vector.x;
				y -= vector.y;
				z -= vector.z;
				return *this;
			}
			Vector3& operator-=(const Vector2<T>& vector) {
				x -= vector.x;
				y -= vector.y;
				return *this;
			}

			Vector3 Multiply(const T& scalar) const override { return Vector3(x * scalar, y * scalar, z * scalar); }
			Vector3& MultiplyAssign(const T& scalar) override {
				x *= scalar;
				y *= scalar;
				z *= scalar;
				return *this;
			}
			friend Vector3 operator*(const T& scalar, const Vector3& vector) { return vector * scalar; }
			Vector3 Divide(const T& scalar) const override { return Vector3(x / scalar, y / scalar, z / scalar);}
			Vector3& DivideAssign(const T& scalar) override {
				x /= scalar;
				y /= scalar;
				z /= scalar;
				return *this;
			}

			U CalculateNorm() const { return squareRoot<U>(static_cast<U>(x * x + y * y + z * z)); }

			template <typename V>
			Vector3(const Vector3<V>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z)) {}
			template <typename V>
			Vector3(const Vector2<V>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(0) {}

			inline std::string toString() override {
				return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
			}
			T x, y, z;
		};
	}
}

#endif