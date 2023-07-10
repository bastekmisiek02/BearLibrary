#pragma once

#include "Bases.h"

#include "Math/GraphicsMath/Vectors/Vectors.h"

#include <math.h>

namespace Bear
{
	namespace GraphicsMath
	{
		template<typename T, UChar rows, UChar columns>
		struct Matrix
		{
		private:
			typedef Vec<T, rows> VectorType;
		public:
			Matrix();
			Matrix(const Matrix<T, rows, columns>& matrix);

			void operator+=(const T& scalar);
			Matrix operator+(const T& scalar);

			void operator-=(const T& scalar);
			Matrix operator-(const T& scalar);

			void operator+=(const Matrix& matrix);
			Matrix operator+(const Matrix& matrix);

			void operator-=(const Matrix& matrix);
			Matrix operator-(const Matrix& matrix);

			T& operator[](const UChar& index);
			const T& operator[](const UChar& index) const;
		};

		template<typename T>
		struct Matrix<T, 2, 2>
		{
		private:
			static constexpr UChar rows = 2;
			static constexpr UChar columns = 2;
		private:
			typedef Vec<T, rows> VectorType;
		private:
			VectorType data[columns];
		public:
			Matrix()
				: data{ {1, 0}, {0, 1} }
			{
			}

			Matrix(const Matrix<T, rows, columns>& matrix)
				: data{ VectorType(matrix[0]), VectorType(matrix[1]) }
			{
			}
		public:
			//+
			void operator+=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] += scalar;
			}

			Matrix operator+(const T& scalar)
			{
				Matrix matrix(*this);
				matrix += scalar;
				return matrix;
			}

			//-
			void operator-=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] -= scalar;
			}

			Matrix operator-(const T& scalar)
			{
				Matrix matrix(*this);
				matrix -= scalar;
				return matrix;
			}

			//*
			void operator*=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] *= scalar;
			}

			Matrix operator*(const T& scalar)
			{
				Matrix matrix(*this);
				matrix *= scalar;
				return matrix;
			}

			//Matrix

			//+
			void operator+=(const Matrix<T, rows, columns>& matrix)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] += matrix[i];
			}

			Matrix<T, rows, columns> operator+(const Matrix<T, rows, columns>& matrix)
			{
				Matrix<T, rows, columns> newMatrix(*this);
				newMatrix += matrix;

				return newMatrix;
			}

			//-
			void operator-=(const Matrix<T, rows, columns>& matrix)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] -= matrix[i];
			}

			Matrix<T, rows, columns> operator-(const Matrix<T, rows, columns>& matrix)
			{
				Matrix<T, rows, columns> newMatrix(*this);
				newMatrix -= matrix;

				return newMatrix;
			}

			//*

			//2
			void operator*=(const Matrix<T, 2, 2>& matrix)
			{
				const VectorType indexA[rows] = { data[0], data[1] };
				const VectorType indexB[rows] = { matrix[0], matrix[1] };

				for (char i = 0; i < rows; i++)
					data[i] = (indexA[0] * indexB[i][0]) + (indexA[1] * indexB[i][1]);
			}

			Matrix<T, 2, 2> operator*(const Matrix<T, 2, 2>& matrix)
			{
				Matrix newMatrix(*this);
				newMatrix *= matrix;

				return newMatrix;
			}

			//Vector
			Vec<T, columns> operator*(const Vec<T, columns>& vector)
			{
				return
				{
					(data[0][0] * vector[0]) + (data[0][1] * vector[1]),
					(data[1][0] * vector[0]) + (data[1][1] * vector[1])
				};
			}
		public:
			VectorType& operator[](const UChar& index)
			{
				return data[index];
			}

			const VectorType& operator[](const UChar& index) const
			{
				return data[index];
			}
		};

		template<typename T>
		struct Matrix<T, 3, 3>
		{
		private:
			static constexpr UChar rows = 3;
			static constexpr UChar columns = 3;
		private:
			typedef Vec<T, rows> VectorType;
		private:
			VectorType data[columns];
		public:
			Matrix()
				: data{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }
			{
			}

			Matrix(const Matrix<T, rows, columns>& matrix)
				: data{ VectorType(matrix[0]), VectorType(matrix[1]), VectorType(matrix[2]) }
			{
			}
		public:
			//scalar

			//+
			void operator+=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] += scalar;
			}

			Matrix operator+(const T& scalar)
			{
				Matrix matrix(*this);
				matrix += scalar;
				return matrix;
			}

			//-
			void operator-=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] -= scalar;
			}

			Matrix operator-(const T& scalar)
			{
				Matrix matrix(*this);
				matrix -= scalar;
				return matrix;
			}

			//*
			void operator*=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] *= scalar;
			}

			Matrix operator*(const T& scalar)
			{
				Matrix matrix(*this);
				matrix *= scalar;
				return matrix;
			}

			//Matrix

			//+
			void operator+=(const Matrix<T, rows, columns>& matrix)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] += matrix[i];
			}

			Matrix<T, rows, columns> operator+(const Matrix<T, rows, columns>& matrix)
			{
				Matrix<T, rows, columns> newMatrix(*this);
				newMatrix += matrix;

				return newMatrix;
			}

			//-
			void operator-=(const Matrix<T, rows, columns>& matrix)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] -= matrix[i];
			}

			Matrix<T, rows, columns> operator-(const Matrix<T, rows, columns>& matrix)
			{
				Matrix<T, rows, columns> newMatrix(*this);
				newMatrix -= matrix;

				return newMatrix;
			}

			//*

			//3
			void operator*=(const Matrix<T, 3, 3>& matrix)
			{
				const VectorType indexA[rows] = { data[0], data[1], data[2] };
				const VectorType indexB[rows] = { matrix[0], matrix[1], matrix[2] };

				for (char i = 0; i < rows; i++)
					data[i] = (indexA[0] * indexB[i][0]) + (indexA[1] * indexB[i][1]) + (indexA[2] * indexB[i][2]);
			}

			Matrix<T, 3, 3> operator*(const Matrix<T, 3, 3>& matrix)
			{
				Matrix newMatrix(*this);
				newMatrix *= matrix;

				return newMatrix;
			}

			//Vector
			Vec<T, columns> operator*(const Vec<T, columns>& vector)
			{
				return
				{
					(data[0][0] * vector[0]) + (data[0][1] * vector[1]) + (data[0][2] * vector[2]),
					(data[1][0] * vector[0]) + (data[1][1] * vector[1]) + (data[1][2] * vector[2]),
					(data[2][0] * vector[0]) + (data[2][1] * vector[1]) + (data[2][2] * vector[2])
				};
			}
		public:
			VectorType& operator[](const UChar& index)
			{
				return data[index];
			}

			const VectorType& operator[](const UChar& index) const
			{
				return data[index];
			}
		};

		template<typename T>
		struct Matrix<T, 4, 4>
		{
		private:
			static constexpr UChar rows = 4;
			static constexpr UChar columns = 4;
		private:
			typedef Vec<T, rows> VectorType;
		private:
			VectorType data[columns];
		public:
			Matrix()
				: data{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }
			{
			}
		public:
			//scalar

			//+
			void operator+=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] += scalar;
			}

			Matrix operator+(const T& scalar)
			{
				Matrix matrix(*this);
				matrix += scalar;
				return matrix;
			}

			//-
			void operator-=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] -= scalar;
			}

			Matrix operator-(const T& scalar)
			{
				Matrix matrix(*this);
				matrix -= scalar;
				return matrix;
			}

			//*
			void operator*=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] *= scalar;
			}

			Matrix operator*(const T& scalar)
			{
				Matrix matrix(*this);
				matrix *= scalar;
				return matrix;
			}

			//Matrix

			//+
			void operator+=(const Matrix<T, rows, columns>& matrix)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] += matrix[i];
			}

			Matrix<T, rows, columns> operator+(const Matrix<T, rows, columns>& matrix)
			{
				Matrix<T, rows, columns> newMatrix(*this);
				newMatrix += matrix;

				return newMatrix;
			}

			//-
			void operator-=(const Matrix<T, rows, columns>& matrix)
			{
				for (UChar i = 0; i < rows; i++)
					data[i] -= matrix[i];
			}

			Matrix<T, rows, columns> operator-(const Matrix<T, rows, columns>& matrix)
			{
				Matrix<T, rows, columns> newMatrix(*this);
				newMatrix -= matrix;

				return newMatrix;
			}

			//*

			//4
			void operator*=(const Matrix<T, 4, 4>& matrix)
			{
				const VectorType indexA[rows] = { data[0], data[1], data[2], data[3] };
				const VectorType indexB[rows] = { matrix[0], matrix[1], matrix[2], matrix[3] };

				for (char i = 0; i < rows; i++)
					data[i] = (indexA[0] * indexB[i][0]) + (indexA[1] * indexB[i][1]) + (indexA[2] * indexB[i][2]) + (indexA[3] * indexB[i][3]);
			}

			Matrix<T, 4, 4> operator*(const Matrix<T, 4, 4>& matrix)
			{
				Matrix newMatrix(*this);
				newMatrix *= matrix;

				return newMatrix;
			}

			//Vector
			Vec<T, columns> operator*(const Vec<T, columns>& vector)
			{
				return
				{
					(data[0][0] * vector[0]) + (data[0][1] * vector[1]) + (data[0][2] * vector[2]) + (data[0][3] * vector[3]),
					(data[1][0] * vector[0]) + (data[1][1] * vector[1]) + (data[1][2] * vector[2]) + (data[1][3] * vector[3]),
					(data[2][0] * vector[0]) + (data[2][1] * vector[1]) + (data[2][2] * vector[2]) + (data[2][3] * vector[3]),
					(data[3][0] * vector[0]) + (data[3][1] * vector[1]) + (data[3][2] * vector[2]) + (data[3][3] * vector[3])
				};
			}

			//Translate
			static Matrix<T, rows, columns> TranslateS(const Matrix<T, rows, columns>& m, const Vec<T, 3>& v)
			{
				Matrix<T, rows, columns> matrix(m);
				matrix[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];

				return matrix;
			}

			void Translate(const Vec<T, 3>& vector)
			{
				data[3] = data[0] * vector[0] + data[1] * vector[1] + data[2] * vector[2] + data[3];
			}

			//Rotation
			static Matrix<T, rows, columns> RotateS(const Matrix<T, rows, columns>& m, const T& angle, const Vec<T, 3>& v)
			{
				const T c = ::cos(angle * 0.01745329f);
				const T s = ::sin(angle * 0.01745329f);

				Vec<T, 3> axis(v);
				axis.Normalize();
				Vec<T, 3> temp(axis * (T(1) - c));

				Matrix rotate;
				rotate[0][0] = c + temp[0] * axis[0];
				rotate[0][1] = temp[0] * axis[1] + s * axis[2];
				rotate[0][2] = temp[0] * axis[2] - s * axis[1];

				rotate[1][0] = temp[1] * axis[0] - s * axis[2];
				rotate[1][1] = c + temp[1] * axis[1];
				rotate[1][2] = temp[1] * axis[2] + s * axis[0];

				rotate[2][0] = temp[2] * axis[0] + s * axis[1];
				rotate[2][1] = temp[2] * axis[1] - s * axis[0];
				rotate[2][2] = c + temp[2] * axis[2];

				Matrix result;
				result[0] = m[0] * rotate[0][0] + m[1] * rotate[0][1] + m[2] * rotate[0][2];
				result[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
				result[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
				result[3] = m[3];

				return result;
			}

			void Rotate(const T& angle, const Vec<T, 3>& vector)
			{
				*this = RotateS(*this, angle, vector);
			}

			//Scale
			static Matrix<T, rows, columns> ScaleS(const Matrix<T, rows, columns>& m, const Vec<T, 3>& vector)
			{
				Matrix<T, rows, columns> matrix;

				for (UChar i = 0; i < 3; i++)
					matrix[i] = m[i] * vector[i];

				matrix[3] = m[3];

				return matrix;
			}

			void Scale(const Vec<T, 3>& vector)
			{
				for (UChar i = 0; i < 3; i++)
					data[i] = data[i] * vector[i];
			}

			//LookAt
			static Matrix<T, 4, 4> LookAt(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
			{
				Vec<T, 3> f(center - eye);
				f.Normalize();

				Vec<T, 3> s(f);
				s = s.Cross(up);
				s.Normalize();

				Vec<T, 3> u(s);
				u = u.Cross(f);

				Matrix<T, 4, 4> result;
				result[0][0] = s.x;
				result[1][0] = s.y;
				result[2][0] = s.z;
				result[0][1] = u.x;
				result[1][1] = u.y;
				result[2][1] = u.z;
				result[0][2] = -f.x;
				result[1][2] = -f.y;
				result[2][2] = -f.z;
				result[3][0] = -s.Dot(eye);
				result[3][1] = -u.Dot(eye);
				result[3][2] = f.Dot(eye);

				return result;
			}

			static Matrix<T, 4, 4> Ortho(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far)
			{
				Matrix<T, 4, 4> result;
				result[0][0] = (T)2 / (right - left);
				result[1][1] = (T)2 / (top - bottom);
				result[2][2] = -(T)1;
				result[3][0] = -(right + left) / (right - left);
				result[3][1] = -(top + bottom) / (top - bottom);
				return result;
			}

			static Matrix<T, 4, 4> Perspective(const T& fov, const T& aspect, const T& near, const T& far)
			{
				const T halfFovTan = ::tan((fov) / (T)2);

				Matrix<T, 4, 4> matrix = ScaleS(Matrix<T, 4, 4>(), { (T)0, (T)0, (T)0 });
				matrix[3] = 0.0f;

				matrix[0][0] = (T)1 / (aspect * halfFovTan);
				matrix[1][1] = (T)1 / halfFovTan;
				matrix[2][2] = far / (near - far);
				matrix[2][3] = -1;
				matrix[3][2] = -(far * near) / (far - near);

				return matrix;
			}
		public:
			VectorType& operator[](const UChar& index)
			{
				return data[index];
			}

			const VectorType& operator[](const UChar& index) const
			{
				return data[index];
			}
		};

		//char
		//Mat2
		typedef Matrix<char, 2, 2> CMat2;
		//typedef Matrix<char, 2, 3> CMat2x3;
		//typedef Matrix<char, 2, 4> CMat2x4;

		//Mat3
		//typedef Matrix<char, 3, 2> CMat3x2;
		typedef Matrix<char, 3, 3> CMat3;
		//typedef Matrix<char, 3, 4> CMat3x4;

		//Mat4
		//typedef Matrix<char, 4, 2> CMat4x2;
		//typedef Matrix<char, 4, 3> CMat4x3;
		typedef Matrix<char, 4, 4> CMat4;

		//UChar
		//Mat2
		typedef Matrix<UChar, 2, 2> UCMat2;
		//typedef Matrix<UChar, 2, 3> UCMat2x3;
		//typedef Matrix<UChar, 2, 4> UCMat2x4;

		//Mat3
		//typedef Matrix<UChar, 3, 2> UCMat3x2;
		typedef Matrix<UChar, 3, 3> UCMat3;
		//typedef Matrix<UChar, 3, 4> UCMat3x4;

		//Mat4
		//typedef Matrix<UChar, 4, 2> UCMat4x2;
		//typedef Matrix<UChar, 4, 3> UCMat4x3;
		typedef Matrix<UChar, 4, 4> UCMat4;

		//SInt
		//Mat2
		typedef Matrix<SInt, 2, 2> SIMat2;
		//typedef Matrix<SInt, 2, 3> SIMat2x3;
		//typedef Matrix<SInt, 2, 4> SIMat2x4;

		//Mat3
		//typedef Matrix<SInt, 3, 2> SIMat3x2;
		typedef Matrix<SInt, 3, 3> SIMat3;
		//typedef Matrix<SInt, 3, 4> SIMat3x4;

		//Mat4
		//typedef Matrix<SInt, 4, 2> SIMat4x2;
		//typedef Matrix<SInt, 4, 3> SIMat4x3;
		typedef Matrix<SInt, 4, 4> SIMat4;

		//USInt
		//Mat2
		typedef Matrix<USInt, 2, 2> USIMat2;
		//typedef Matrix<USInt, 2, 3> USIMat2x3;
		//typedef Matrix<USInt, 2, 4> USIMat2x4;

		//Mat3
		//typedef Matrix<USInt, 3, 2> USIMat3x2;
		typedef Matrix<USInt, 3, 3> USIMat3;
		//typedef Matrix<USInt, 3, 4> USIMat3x4;

		//Mat4
		//typedef Matrix<USInt, 4, 2> USIMat4x2;
		//typedef Matrix<USInt, 4, 3> USIMat4x3;
		typedef Matrix<USInt, 4, 4> USIMat4;

		//int
		//Mat2
		typedef Matrix<int, 2, 2> IMat2;
		//typedef Matrix<int, 2, 3> IMat2x3;
		//typedef Matrix<int, 2, 4> IMat2x4;

		//Mat3
		//typedef Matrix<int, 3, 2> IMat3x2;
		typedef Matrix<int, 3, 3> IMat3;
		//typedef Matrix<int, 3, 4> IMat3x4;

		//Mat4
		//typedef Matrix<int, 4, 2> IMat4x2;
		//typedef Matrix<int, 4, 3> IMat4x3;
		typedef Matrix<int, 4, 4> IMat4;

		//UInt
		//Mat2
		typedef Matrix<UInt, 2, 2> UIMat2;
		//typedef Matrix<UInt, 2, 3> UIMat2x3;
		//typedef Matrix<UInt, 2, 4> UIMat2x4;

		//Mat3
		//typedef Matrix<UInt, 3, 2> UIMat3x2;
		typedef Matrix<UInt, 3, 3> UIMat3;
		//typedef Matrix<UInt, 3, 4> UIMat3x4;

		//Mat4
		//typedef Matrix<UInt, 4, 2> UIMat4x2;
		//typedef Matrix<UInt, 4, 3> UIMat4x3;
		typedef Matrix<UInt, 4, 4> UIMat4;

		//float
		//Mat2
		typedef Matrix<float, 2, 2> Mat2;
		//typedef Matrix<float, 2, 3> Mat2x3;
		//typedef Matrix<float, 2, 4> Mat2x4;

		//Mat3
		//typedef Matrix<float, 3, 2> Mat3x2;
		typedef Matrix<float, 3, 3> Mat3;
		//typedef Matrix<float, 3, 4> Mat3x4;

		//Mat4
		//typedef Matrix<float, 4, 2> Mat4x2;
		//typedef Matrix<float, 4, 3> Mat4x3;
		typedef Matrix<float, 4, 4> Mat4;

		//double
		//Mat2
		typedef Matrix<double, 2, 2> DMat2;
		//typedef Matrix<double, 2, 3> DMat2x3;
		//typedef Matrix<double, 2, 4> DMat2x4;

		//Mat3
		//typedef Matrix<double, 3, 2> DMat3x2;
		typedef Matrix<double, 3, 3> DMat3;
		//typedef Matrix<double, 3, 4> DMat3x4;

		//Mat4
		//typedef Matrix<double, 4, 2> DMat4x2;
		//typedef Matrix<double, 4, 3> DMat4x3;
		typedef Matrix<double, 4, 4> DMat4;

		//LInt
		//Mat2
		typedef Matrix<LInt, 2, 2> LIMat2;
		//typedef Matrix<LInt, 2, 3> LIMat2x3;
		//typedef Matrix<LInt, 2, 4> LIMat2x4;

		//Mat3
		//typedef Matrix<LInt, 3, 2> LIMat3x2;
		typedef Matrix<LInt, 3, 3> LIMat3;
		//typedef Matrix<LInt, 3, 4> LIMat3x4;

		//Mat4
		//typedef Matrix<LInt, 4, 2> LIMat4x2;
		//typedef Matrix<LInt, 4, 3> LIMat4x3;
		typedef Matrix<LInt, 4, 4> LIMat4;

		//ULInt
		//Mat2
		typedef Matrix<ULInt, 2, 2> ULIMat2;
		//typedef Matrix<ULInt, 2, 3> ULIMat2x3;
		//typedef Matrix<ULInt, 2, 4> ULIMat2x4;

		//Mat3
		//typedef Matrix<ULInt, 3, 2> ULIMat3x2;
		typedef Matrix<ULInt, 3, 3> ULIMat3;
		//typedef Matrix<ULInt, 3, 4> ULIMat3x4;

		//Mat4
		//typedef Matrix<ULInt, 4, 2> ULIMat4x2;
		//typedef Matrix<ULInt, 4, 3> ULIMat4x3;
		typedef Matrix<ULInt, 4, 4> ULIMat4;
	}
}