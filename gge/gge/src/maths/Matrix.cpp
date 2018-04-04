#include "Matrix.h"

namespace gge
{
	namespace maths
	{
		Matrix::Matrix() {
			memset(elements, 0, 4 * 4 * sizeof(float));
		}

		Matrix::Matrix(float diagonal) {
			memset(elements, 0, 4 * 4 * sizeof(float));
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		Matrix Matrix::identity() {
			return Matrix(1.0f);
		}

		Matrix& Matrix::multiply(const Matrix& other) {
			float data[16];
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					float sum = 0.0f;
					for (int e = 0; e < 4; e++) {
						sum += elements[e + y * 4] * other.elements[x + e * 4];
					}
					data[x + y * 4] = sum;
				}
			}
			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}

		Matrix operator*(Matrix left, const Matrix& right) {
			return left.multiply(right);
		}

		Matrix& Matrix::operator*=(const Matrix& other) {
			return multiply(other);
		}

		Vector3 Matrix::multiply(const Vector3& other) const {
			return Vector3(
				column[0].x * other.x + column[1].x * other.y + column[2].x * other.z + column[3].x,
				column[0].y * other.x + column[1].y * other.y + column[2].y * other.z + column[3].y,
				column[0].z * other.x + column[1].z * other.y + column[2].z * other.z + column[3].z
			);
		}

		Vector3 operator*(const Matrix& left, const Vector3& right) {
			return left.multiply(right);
		}

		Vector4 Matrix::multiply(const Vector4& other) const {
			return Vector4(
				column[0].x * other.x + column[1].x * other.y + column[2].x * other.z + column[3].x * other.w,
				column[0].y * other.x + column[1].y * other.y + column[2].y * other.z + column[3].y * other.w,
				column[0].z * other.x + column[1].z * other.y + column[2].z * other.z + column[3].z * other.w,
				column[0].w * other.x + column[1].w * other.y + column[2].w * other.z + column[3].w * other.w
			);
		}

		Vector4 operator*(const Matrix& left, const Vector4& right) {
			return left.multiply(right);
		}

		Matrix Matrix::orthographic(float left, float right, float bottom, float top,
			float near, float far) {
			Matrix result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);

			return result;
		}

		Matrix Matrix::perspective(float fov, float aspectRatio, float near, float far) {
			Matrix result(1.0f);
			float q = 1.0f / tan(ToRadians(0.5f * fov));
			float a = q / aspectRatio;
			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1;
			result.elements[2 + 3 * 4] = c;

			return result;
		}

		Matrix Matrix::translation(const maths::Vector3& translation) {
			Matrix result(1.0f);
			result.elements[3 + 0 * 4] = translation.x;
			result.elements[3 + 1 * 4] = translation.y;
			result.elements[3 + 2 * 4] = translation.z;
			return result;
		}

		Matrix Matrix::rotation(float angle, const maths::Vector3& axis) {
			Matrix result(1.0f);
			float r = ToRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			result.elements[0 + 0 * 4] = axis.x * axis.x * omc + c;
			result.elements[0 + 1 * 4] = axis.y * axis.x * omc + axis.z * s;
			result.elements[0 + 2 * 4] = axis.x * axis.z * omc - axis.y * s;

			result.elements[1 + 0 * 4] = axis.x * axis.y * omc - axis.z * s;
			result.elements[1 + 1 * 4] = axis.y * axis.y * omc + c;
			result.elements[1 + 2 * 4] = axis.y * axis.z * omc + axis.x * s;

			result.elements[2 + 0 * 4] = axis.x * axis.z * omc + axis.y * s;
			result.elements[2 + 1 * 4] = axis.y * axis.z * omc - axis.x * s;
			result.elements[2 + 2 * 4] = axis.z * axis.z * omc + c;

			return result;
		}

		Matrix Matrix::scale(const maths::Vector3& scale) {
			Matrix result(1.0f);
			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;
			return result;
		}
	}
}