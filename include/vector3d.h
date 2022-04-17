
#ifndef __VECTOR_3D_H__
#define __VECTOR_3D_H__ 1

#include <math.h>
#include <string>

template<typename T>
class Vector3 {

public:
				Vector3() : x(0), y(0), z(0), w(1) {};
				Vector3(T n) : x(n), y(n), z(n), w(1) {};
				Vector3(T x1, T y1, T z1) : x(x1), y(y1), z(z1), w(1) {};
				~Vector3() {};

				// Variables:
				union {
								T data[3];
								struct {
												T x;
												T y;
												T z;
								};
				};

				// Hideen W Proj Calculation Component
				T w;


				// Inline Methods:
				inline Vector3& perspectiveDivide() {
								x /= w;
								y /= w;
								z /= w;
								return *this;
				}


				inline float triangleAreaSquared(const Vector3& b, const Vector3& c) {
								float x1 = b.x - x;
								float y1 = b.y - y;

								float x2 = c.x - x;
								float y2 = c.y - y;

								return (x1 * y2 - x2 * y1);
				}

				inline Vector3 operator-() const {
								return Vector3(-x, -y, -z);
				}

				inline Vector3 operator*(const T v) const {
								return Vector3(x * v, y * v, z * v);
				}

				inline Vector3 operator+(const T v) const {
								return Vector3(x + v, y + v, z + v);
				}

				inline Vector3 operator-(const Vector3& v) const {
								return Vector3(x - v.x, y - v.y, z - v.z);
				}

				inline Vector3 operator+(const Vector3& v) const {
								return Vector3(x + v.x, y + v.y, z + v.z);
				}

				inline void operator+=(const Vector3& v) {
								x += v.x;
								y += v.y;
								z += v.z;
				}

				inline void operator-=(const Vector3& v) {
								x -= v.x;
								y -= v.y;
								z -= v.z;
				}

				inline Vector3 operator*(const Vector3& v) const {
								return Vector3(x * v.x, y * v.y, z * v.z);
				}

				inline Vector3 crossProduct(const Vector3& v) const {
								return Vector3((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x));
				}

				inline T dotProduct(const Vector3& v) const {
								return x * v.x + y * v.y + z * v.z;
				}

				inline T dot2D(const Vector3& v) const {
								return x * v.x + y * v.y;
				}

				inline T sqrLength() const {
								return (x * x) + (y * y) + (z * z);
				}

				inline T length() const {
								return powf(sqrLength(), 0.5f);
				}

				inline Vector3& normalized() {
								T factor = 1.0f / length();
								x *= factor;
								y *= factor;
								z *= factor;

								return *this;
				}

				inline static Vector3 reflect(const Vector3& i, const Vector3& n) {
								return i - ((n * i.dotProduct(n)) * 2.0f);
				}

				inline void print() const {

								std::string out;
								if (typeid(T) == typeid(float)) {
												out = "Vector3f(%f, %f, %f)\n";
								}

								if (typeid(T) == typeid(int)) {
												out = "Vector3i(%d, %d, %d)\n";
								}

								printf(out.c_str(), x, y, z);
				}

				inline void zero() {
								x = 0;
								y = 0;
								z = 0;
				}
};

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

#endif

