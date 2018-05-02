#include "Vector3.h"

/* Reference (Cherno, 2018) full ref found in report */
namespace gge
{
	namespace maths
	{
		Vector3::Vector3() {
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		Vector3::Vector3(const float& x, const float& y, const float& z) 
		: x(x), y(y), z(z) { }

		Vector3& Vector3::Add(const Vector3 & other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3& Vector3::Subtract(const Vector3 & other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3& Vector3::Multiply(const Vector3 & other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		Vector3& Vector3::Divide(const Vector3 & other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		Vector3 & Vector3::operator+=(const Vector3 & other) {
			return Add(other);
		}

		Vector3 & Vector3::operator-=(const Vector3 & other) {
			return Subtract(other);
		}

		Vector3 & Vector3::operator*=(const Vector3 & other) {
			return Multiply(other);
		}

		Vector3 & Vector3::operator/=(const Vector3 & other) {
			return Divide(other);
		}

		Vector3 operator+(Vector3 left, const Vector3 & right) {
			return left.Add(right);
		}

		Vector3 operator-(Vector3 left, const Vector3 & right) {
			return left.Subtract(right);
		}

		Vector3 operator*(Vector3 left, const Vector3 & right) {
			return left.Multiply(right);
		}

		Vector3 operator/(Vector3 left, const Vector3 & right) {
			return left.Divide(right);
		}

		bool Vector3::operator==(const Vector3 & other) {
			return x == other.x && y == other.y && z == other.z;
		}

		bool Vector3::operator!=(const Vector3 & other) {
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector3& vector) {
			stream << "Vector3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
	}
}