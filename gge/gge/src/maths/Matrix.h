#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Mathematics.h"

namespace gge
{
	namespace maths
	{
		struct Matrix {
			union {
				float elements[4 * 4];
				Vector4 column[4];
			};

			Matrix();
			Matrix(float diagonal);

			static Matrix identity();

			Matrix& multiply(const Matrix& other);
			friend Matrix operator*(Matrix left, const Matrix& right);
			Matrix& operator*=(const Matrix& other);

			Vector3 multiply(const Vector3& other) const;
			friend Vector3 operator*(const Matrix& left, const Vector3& right);

			Vector4 multiply(const Vector4& other) const;
			friend Vector4 operator*(const Matrix& left, const Vector4& right);

			static Matrix orthographic(float left, float right, float bottom, float top,
				float near, float far);
			static Matrix perspective(float fov, float aspectRatio, float near, float far);

			static Matrix translation(const maths::Vector3& translation);
			static Matrix rotation(float angle, const maths::Vector3& axis);
			static Matrix scale(const maths::Vector3& scale);
		};
	}
}