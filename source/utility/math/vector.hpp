#ifndef CUSTOM_MATH_VECTOR
#define CUSTOM_MATH_VECTOR

#include "precompiled_header.hpp"
#include "general.hpp"

namespace Custom {
	namespace Math {
		template <typename T, typename U>
		class Vector {
		public :
			~Vector() = default;

			template <typename Self>
			Self operator+(this Self& self, const Self& vector) { return self.Add(vector); }
			template <typename Self>
			Self& operator+=(this Self& self, const Self& vector) { return self.AddAssign(vector); }
			template <typename Self>
			Self operator-(this Self& self, const Self& vector) { return self.Minus(vector); }
			template <typename Self>
			Self& operator-=(this Self& self, const Self& vector) { return self.MinusAssign(vector); }
			template <typename Self>
			Self operator*(this Self& self, const T& scalar) { return self.Multiply(scalar); }
			template <typename Self>
			Self& operator*=(this Self& self, const T& scalar) { return self.MultiplyAssign(scalar); }
			template <typename Self>
			Self operator/(this Self& self, const T& scalar) { return self.Divide(scalar); }
			template <typename Self>
			Self& operator/=(this Self& self, const T& scalar) { return self.DivideAssign(scalar); }
			template <typename Self>
			bool operator==(this Self& self, const Self& vector) { return self.Equal(vector); }
			template <typename Self>
			bool operator!=(this Self& self, const Self& vector) { return self.Inequal(vector); }

			template <typename Self>
			inline U Norm(this Self& self) { return self.Norm(); }

			inline virtual std::string ToString() const = 0;
		private :
			template <typename V, typename W>
			friend std::ostream& operator<<(std::ostream& os, const Vector<V, W>& vector);
		};

		template <typename T, typename U>
		std::ostream& operator<<(std::ostream& os, const Vector<T, U>& vector) {
			os << vector.ToString();
			return os;
		}

		template <typename T = float, typename U = float>
		class Vector2 : public Vector<T, U> {
		public:
			constexpr Vector2(T x, T y) : x(x), y(y) {}

			static constexpr Vector2 zero() { return Vector2(0, 0); }
			static constexpr Vector2 one() { return Vector2(1, 1); }
			static constexpr Vector2 up() { return Vector2(0, 1); }
			static constexpr Vector2 down() { return Vector2(0, -1); }
			static constexpr Vector2 left() { return Vector2(-1, 0); }
			static constexpr Vector2 right() { return Vector2(1, 0); }

			template <typename V>
			Vector2(const Vector2<V>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) {}

			T x, y;
		private :
			Vector2 Add(const Vector2& vector) const { return Vector2(x + vector.x, y + vector.y); }
			Vector2& AddAssign(const Vector2& vector) {
				x += vector.x;
				y += vector.y;
				return *this;
			}
			Vector2 Minus(const Vector2& vector) const { return Vector2(x - vector.x, y - vector.y); }
			Vector2& MinusAssign(const Vector2& vector) {
				x -= vector.x;
				y -= vector.y;
				return *this;
			}
			Vector2 Multiply(const T& scalar) const { return Vector2(x * scalar, y * scalar); }
			Vector2& MultiplyAssign(const T& scalar) {
				x *= scalar;
				y *= scalar;
				return *this;
			}
			friend Vector2 operator*(const T& scalar, const Vector2& vector) { return vector * scalar; }
			Vector2 Divide(const T& scalar) const { return Vector2(x / scalar, y / scalar);}
			Vector2& DivideAssign(const T& scalar) {
				x /= scalar;
				y /= scalar;
				return *this;
			}
			bool Equal(const Vector2& vector) const { return (x == vector.x) && (y == vector.y); }
			bool Inequal(const Vector2& vector) const { return (x != vector.x) || (y != vector.y); }

			U Norm() const { return squareRoot<U>(static_cast<U>(x * x + y * y)); }

			inline std::string ToString() const override {
				return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
			}
			friend class Vector<T, U>;
		};

		template <typename T = float, typename U = float>
		class Vector3 : public Vector<T, U> {
		public:
			constexpr Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

			static constexpr Vector3 zero() { return Vector3(0, 0, 0); }
			static constexpr Vector3 one() { return Vector3(1, 1, 1); }
			static constexpr Vector3 up() { return Vector3(0, 1, 0); }
			static constexpr Vector3 down() { return Vector3(0, -1, 0); }
			static constexpr Vector3 left() { return Vector3(-1, 0, 0); }
			static constexpr Vector3 right() { return Vector3(1, 0, 0); }
			static constexpr Vector3 forward() { return Vector3(0, 0, 1); }
			static constexpr Vector3 backward() { return Vector3(0, 0, -1); }

			Vector3 operator+(const Vector2<T>& vector) const { return Vector3(x + vector.x, y + vector.y, z); }
			Vector3& operator+=(const Vector2<T>& vector) {
				x += vector.x;
				y += vector.y;
				return *this;
			}
			Vector3 operator-(const Vector2<T>& vector) const { return Vector3(x - vector.x, y - vector.y, z); }
			Vector3& operator-=(const Vector2<T>& vector) {
				x -= vector.x;
				y -= vector.y;
				return *this;
			}
			friend Vector3 operator*(const T& scalar, const Vector3& vector) { return vector * scalar; }

			template <typename V>
			Vector3(const Vector3<V>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z)) {}
			template <typename V>
			Vector3(const Vector2<V>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(0) {}

			T x, y, z;
		private :
			Vector3 Add(const Vector3& vector) const { return Vector3(x + vector.x, y + vector.y, z + vector.z); }
			Vector3& AddAssign(const Vector3& vector) {
				x += vector.x;
				y += vector.y;
				z += vector.z;
				return *this;
			}
			Vector3 Minus(const Vector3& vector) const { return Vector3(x - vector.x, y - vector.y, z - vector.z); }
			Vector3& MinusAssign(const Vector3& vector) {
				x -= vector.x;
				y -= vector.y;
				z -= vector.z;
				return *this;
			}
			Vector3 Multiply(const T& scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
			Vector3& MultiplyAssign(const T& scalar) {
				x *= scalar;
				y *= scalar;
				z *= scalar;
				return *this;
			}
			Vector3 Divide(const T& scalar) const { return Vector3(x / scalar, y / scalar, z / scalar);}
			Vector3& DivideAssign(const T& scalar) {
				x /= scalar;
				y /= scalar;
				z /= scalar;
				return *this;
			}
			bool Equal(const Vector3& vector) const { return (x == vector.x) && (y == vector.y) && (z == vector.z); }
			bool Inequal(const Vector3& vector) const { return (x != vector.x) || (y != vector.y) || (z != vector.z); }

			inline U Norm() const { return squareRoot<U>(static_cast<U>(x * x + y * y + z * z)); }

			inline std::string ToString() const override {
				return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
			}
			friend class Vector<T, U>;
		};
	}
}

#endif