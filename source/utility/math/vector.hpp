#ifndef CUSTOM_MATH_VECTOR
#define CUSTOM_MATH_VECTOR

#include "general.hpp"
#include <stdexcept>
#include <numeric>
#include <ostream>
#include <type_traits>
#include <format>

namespace Custom {
	namespace Math {
		template <typename T = DEFAULT_VECTOR_TYPE>
		class Vector2 {
		public:
			Vector2(T x, T y) : x(x), y(y) {}

			static constexpr Vector2 zero() { return Vector2(0, 0); }
			static constexpr Vector2 up() { return Vector2(0, 1); }
			static constexpr Vector2 down() { return Vector2(0, -1); }
			static constexpr Vector2 left() { return Vector2(-1, 0); }
			static constexpr Vector2 right() { return Vector2(1, 0); }

			Vector2 operator+(const Vector2& vector) const { return Vector2(x + vector.x, y + vector.y); }
			Vector2& operator+=(const Vector2& vector) {
				x += vector.x;
				y += vector.y;
				return *this;
			}
			Vector2 operator-(const Vector2& vector) const { return Vector2(x - vector.x, y - vector.y); }
			Vector2& operator-=(const Vector2& vector) {
				x -= vector.x;
				y -= vector.y;
				return *this;
			}

			Vector2 operator*(const T& scalar) const { return Vector2(x * scalar, y * scalar);}
			Vector2& operator*=(const T& scalar) {
				x *= scalar;
				y *= scalar;
				return *this;
			}
			friend Vector2 operator*(const T& scalar, const Vector2& vector) { return vector * scalar; }
			Vector2 operator/(const T& scalar) const { return Vector2(x / scalar, y / scalar);}
			Vector2& operator/=(const T& scalar) {
				x /= scalar;
				y /= scalar;
				return *this;
			}

			template <typename U = DEFAULT_GENERAL_OPERATION>
			U magnitude() const { return squareRoot<U>(static_cast<U>(x * x + y * y)); }

			template <typename U>
			Vector2(const Vector2<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

			friend std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
				os << std::format("({}, {})", vector.x, vector.y);
				return os;
			}
			T x, y;
		};

		template <typename T = DEFAULT_VECTOR_TYPE>
		class Vector3 {
		public:
			Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

			static constexpr Vector3 zero() { return Vector3(0, 0, 0); }
			static constexpr Vector3 up() { return Vector3(0, 1, 0); }
			static constexpr Vector3 down() { return Vector3(0, -1, 0); }
			static constexpr Vector3 left() { return Vector3(-1, 0, 0); }
			static constexpr Vector3 right() { return Vector3(1, 0, 0); }
			static constexpr Vector3 forward() { return Vector3(0, 0, 1); }
			static constexpr Vector3 backward() { return Vector3(0, 0, 1); }

			Vector3 operator+(const Vector3& vector) const { return Vector3(x + vector.x, y + vector.y, z + vector.z); }
			Vector3 operator+(const Vector2<T>& vector) const { return Vector3(x + vector.x, y + vector.y, z); }
			Vector3& operator+=(const Vector3& vector) {
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
			Vector3 operator-(const Vector3& vector) const { return Vector3(x - vector.x, y - vector.y, z - vector.z); }
			Vector3 operator-(const Vector2<T>& vector) const { return Vector3(x - vector.x, y - vector.y, z); }
			Vector3& operator-=(const Vector3& vector) {
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

			Vector3 operator*(const T& scalar) const { return Vector3(x * scalar, y * scalar, z * scalar);}
			Vector3& operator*=(const T& scalar) {
				x *= scalar;
				y *= scalar;
				z *= scalar;
				return *this;
			}
			friend Vector3 operator*(const T& scalar, const Vector3& vector) { return vector * scalar; }
			Vector3 operator/(const T& scalar) const { return Vector3(x / scalar, y / scalar, z / scalar);}
			Vector3& operator/=(const T& scalar) {
				x /= scalar;
				y /= scalar;
				z /= scalar;
				return *this;
			}

			template <typename U = DEFAULT_GENERAL_OPERATION>
			U magnitude() const { return squareRoot<U>(static_cast<U>(x * x + y * y + z * z)); }

			template <typename U>
			Vector3(const Vector3<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}
			template <typename U>
			Vector3(const Vector2<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(0) {}

			friend std::ostream& operator<<(std::ostream& os, const Vector3& vector) {
				os << std::format("({}, {}, {})", vector.x, vector.y, vector.z);
				return os;
			}
			T x, y, z;
		};
	}
}

#endif

		/*
		template <typename T, size_t N>
		class Vector {
		private:
			std::array<T, N> data;

		public:
			Vector() = default;
			Vector(std::initializer_list<T> list) {
				if (list.size() != N) { throw std::invalid_argument("Initializer list size does not match vector dimension"); }
				std::copy(list.begin(), list.end(), data.begin());
			}
			Vector(const std::array<T, N>& array): data(array) {}

			constexpr size_t size() const { return N; }
			T& operator[](size_t index) {
				if (index >= N) {
					throw std::out_of_range("Vector index out of range");
				}
				return data[index];
			}
			const T& operator[](size_t index) const {
				if (index >= N) {
					throw std::out_of_range("Vector index out of range");
				}
				return data[index];
			}

			template <typename U = T, std::enable_if_t<(N >= 2), int> = void>
			U& x() { return data[0]; }
			template <typename U = T, std::enable_if_t<(N >= 2), int> = void>
			const U& x() const { return data[0]; }

			template <typename U = T, std::enable_if_t<(N >= 2), int> = void>
			U& y() { return data[1]; }
			template <typename U = T, std::enable_if_t<(N >= 2), int> = void>
			const U& y() const { return data[1]; }
		
			template <typename U = T, std::enable_if_t<(N >= 3), int> = void>
			U& z() { return data[2]; }
			template <typename U = T, std::enable_if_t<(N >= 3), int> = void>
			const U& z() const { return data[2]; }
		
			template <typename U = T, std::enable_if_t<(N >= 4), int> = void>
			U& w() { return data[3]; }
			template <typename U = T, std::enable_if_t<(N >= 4), int> = void>
			const U& w() const { return data[3]; }

			Vector operator+(const Vector& other) const {
				if (size() != other.size()) {
					throw std::invalid_argument("Vectors must have the same size for addition");
				}
				Vector result;
				std::transform(data.begin(), data.end(), other.data.begin(), result.data.begin(), std::plus<T>());
				return result;
			}

			Vector operator-(const Vector& other) const {
				if (size() != other.size()) {
					throw std::invalid_argument("Vectors must have the same size for addition");
				}
				Vector result;
				std::transform(data.begin(), data.end(), other.data.begin(), result.data.begin(), std::minus<T>());
				return result;
			}

			Vector operator*(T scalar) const {
				Vector result(size());
				std::transform(data.begin(), data.end(), result.data.begin(), [scalar](T val){ return val * scalar; });
				return result;
			}
			
			Vector operator/(T scalar) const {
				if (scalar == 0) {
					throw std::invalid_argument("Cannot divide by zero.");
				}
				Vector result(size());
				std::transform(data.begin(), data.end(), result.data.begin(), [scalar](T val){ return val / scalar; });
				return result;
			}

			T dot(const Vector& other) const {
				if (size() != other.size()) {
					throw std::invalid_argument("Vectors must have the same size for dot product");
				}
				return std::inner_product(data.begin(), data.end(), other.data.begin(), T{0});
			}

			template <typename U = double>
			U magnitude() const {
				return squareRoot<U>(this->dot(*this));
			}

			template <typename U = double>
			U distance(const Vector& other) const {
				return (*this - other).template magnitude<U>();
			}

			template<typename U, size_t M>
			friend Vector<U, M> operator*(U scalar, const Vector<U, M>& vector);

			friend std::ostream& operator<<(std::ostream& os, const Vector<T, N>& v) {
				os << "(";
				for (size_t i = 0; i < N; ++i) {
					os << v[i];
					if (i < N - 1) {
					os << ", ";
					}
				}
				os << ")";
				return os;
			}
		};

		template<typename U, size_t M>
		Vector<U, M> operator*(U scalar, const Vector<U, M>& vector) {
			return vector * scalar;
		};

		template <typename T = float> 
		class Vector2 : public Vector<T, 2> {
			Vector2(T x, T y) : Vector<T, 2>({x, y}) {}
		};

		template <typename T = float> 
		class Vector3 : public Vector<T, 3> {
			Vector3(T x, T y, T z) : Vector<T, 3>({x, y, z}) {}
		};

		template <typename T = float> 
		class Vector4 : public Vector<T, 4> {
			Vector4(T x, T y, T z, T w) : Vector<T, 4>({x, y, z, w}) {}
		};

		template <typename T> Vector2(T, T) -> Vector2<T>;
		template <typename T> Vector3(T, T, T) -> Vector3<T>;
		template <typename T> Vector4(T, T, T, T) -> Vector4<T>;
		*/