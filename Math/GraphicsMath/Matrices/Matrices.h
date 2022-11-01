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
			Matrix();

			void operator+=(const T& scalar);
			Matrix operator+(const T& scalar);

			void operator-=(const T& scalar);
			Matrix operator-(const T& scalar);

			void operator+=(const Matrix& matrix);
			Matrix operator+(const Matrix& matrix);

			void operator-=(const Matrix& matrix);
			Matrix operator-(const Matrix& matrix);

			T* operator[](const UChar& index);
		};

		template<typename T>
		struct Matrix<T, 2, 2>
		{
		private:
			static constexpr UChar rows = 2;
			static constexpr UChar columns = 2;
		private:
			T data[rows][columns];
		public:
			Matrix()
				: data{ {1, 0}, {0, 1} }
			{
			}
		public:
			//scalar

			//+
			void operator+=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] += scalar;
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] -= scalar;
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] *= scalar;
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] += matrix.data[i][j];
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] -= matrix.data[i][j];
				}
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
				const T index0 = data[0][0];
				const T index1 = data[1][0];

				data[0][0] = (index0 * matrix.data[0][0]) + (data[0][1] * matrix.data[1][0]);
				data[0][1] = (index0 * matrix.data[0][1]) + (data[0][1] * matrix.data[1][1]);

				data[1][0] = (index1 * matrix.data[0][0]) + (data[1][1] * matrix.data[1][0]);
				data[1][1] = (index1 * matrix.data[0][1]) + (data[1][1] * matrix.data[1][1]);
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
					(data[0][0] * vector.x) + (data[0][1] * vector.y),
					(data[1][0] * vector.x) + (data[1][1] * vector.y)
				};
			}
		public:
			T* operator[](const UChar& index)
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
			T data[rows][columns];
		public:
			Matrix()
				: data{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }
			{
			}
		public:
			//scalar

			//+
			void operator+=(const T& scalar)
			{
				for (UChar i = 0; i < rows; i++)
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] += scalar;
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] -= scalar;
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] *= scalar;
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] += matrix.data[i][j];
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] -= matrix.data[i][j];
				}
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
				const T tmp[rows][columns] =
				{
					data[0][0], data[0][1], data[0][2],
					data[1][0], data[1][1], data[1][2],
					data[2][0], data[2][1], data[2][2]
				};

				for (UChar i = 0; i < rows; i++)
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] = (tmp[i][0] * matrix.data[0][j]) + (tmp[i][1] * matrix.data[1][j]) + (tmp[i][2] * matrix.data[2][j]);
				}
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
					(data[0][0] * vector.x) + (data[0][1] * vector.y) + (data[0][2] * vector.z),
					(data[1][0] * vector.x) + (data[1][1] * vector.y) + (data[1][2] * vector.z),
					(data[2][0] * vector.x) + (data[2][1] * vector.y) + (data[2][2] * vector.z)
				};
			}
		public:
			T* operator[](const UChar& index)
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
			T data[rows][columns];
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] += scalar;
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] -= scalar;
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] *= scalar;
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] += matrix.data[i][j];
				}
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
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] -= matrix.data[i][j];
				}
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
				const T tmp[rows][columns] =
				{
					data[0][0], data[0][1], data[0][2], data[0][3],
					data[1][0], data[1][1], data[1][2], data[1][3],
					data[2][0], data[2][1], data[2][2], data[2][3],
					data[3][0], data[3][1], data[3][2], data[3][3]
				};

				for (UChar i = 0; i < rows; i++)
				{
					for (UChar j = 0; j < columns; j++)
						data[i][j] = (tmp[i][0] * matrix.data[0][j]) + (tmp[i][1] * matrix.data[1][j]) + (tmp[i][2] * matrix.data[2][j]) + (tmp[i][3] * matrix.data[3][j]);
				}
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
					(data[0][0] * vector.x) + (data[0][1] * vector.y) + (data[0][2] * vector.z) + (data[0][3] * vector.w),
					(data[1][0] * vector.x) + (data[1][1] * vector.y) + (data[1][2] * vector.z) + (data[1][3] * vector.w),
					(data[2][0] * vector.x) + (data[2][1] * vector.y) + (data[2][2] * vector.z) + (data[2][3] * vector.w),
					(data[3][0] * vector.x) + (data[3][1] * vector.y) + (data[3][2] * vector.z) + (data[3][3] * vector.w)
				};
			}

			//Translate
			static Matrix<T, rows, columns> Translate(const Vec<T, 2>& vector)
			{
				Matrix<T, columns, rows> matrix;
				matrix.data[0][3] = vector.x;
				matrix.data[1][3] = vector.y;
				matrix.data[2][3] = 0;
			
				return matrix;
			}
			
			static Matrix<T, rows, columns> Translate(const Vec<T, 3>& vector)
			{
				Matrix<T, columns, rows> matrix;
				matrix.data[0][3] = vector.x;
				matrix.data[1][3] = vector.y;
				matrix.data[2][3] = vector.z;

				return matrix;
			}
			
			static Matrix<T, rows, columns> Translate(const Vec<T, 4>& vector)
			{
				Matrix<T, columns, rows> matrix;
				matrix.data[0][0] = vector.x;
				matrix.data[1][1] = vector.y;
				matrix.data[2][2] = vector.z;
			
				return matrix;
			}
			
			//Rotation			
			static Matrix<T, rows, columns> RotateX(const T& angle)
			{
				const T sin = ::sin(angle);
				const T cos = ::cos(angle);

				Matrix<T, columns, rows> matrix;
				matrix.data[1][1] = cos;
				matrix.data[1][2] = -sin;

				matrix.data[2][1] = sin;
				matrix.data[2][2] = cos;
			
				return matrix;
			}

			static Matrix<T, rows, columns> RotateY(const T& angle)
			{
				const T sin = ::sin(angle);
				const T cos = ::cos(angle);

				Matrix<T, columns, rows> matrix;
				matrix.data[0][0] = cos;
				matrix.data[0][2] = sin;

				matrix.data[2][0] = -sin;
				matrix.data[2][2] = cos;

				return matrix;
			}

			static Matrix<T, rows, columns> RotateZ(const T& angle)
			{
				const T sin = ::sin(angle);
				const T cos = ::cos(angle);

				Matrix<T, columns, rows> matrix;
				matrix.data[0][0] = cos;
				matrix.data[0][1] = -sin;

				matrix.data[1][0] = sin;
				matrix.data[1][1] = cos;

				return matrix;
			}
			
			//Scale
			static Matrix<T, rows, columns> Scale(const Vec<T, 2>& vector)
			{
				Matrix<T, columns, rows> matrix;
				matrix.data[0][0] = vector.x;
				matrix.data[1][1] = vector.y;

				return matrix;
			}

			static Matrix<T, rows, columns> Scale(const Vec<T, 3>& vector)
			{
				Matrix<T, columns, rows> matrix;
				matrix.data[0][0] = vector.x;
				matrix.data[1][1] = vector.y;
				matrix.data[2][2] = vector.z;

				return matrix;
			}

			static Matrix<T, rows, columns> Scale(const Vec<T, 4>& vector)
			{
				Matrix<T, columns, rows> matrix;
				matrix.data[0][0] = vector.x;
				matrix.data[1][1] = vector.y;
				matrix.data[2][2] = vector.z;
				matrix.data[3][3] = vector.w;

				return matrix;
			}
		public:
			T* operator[](const UChar& index)
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