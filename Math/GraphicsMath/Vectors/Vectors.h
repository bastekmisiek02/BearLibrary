#pragma once

#include "Bases.h"

#include "Math/Math/Math.h"

namespace Bear
{
	namespace GraphicsMath
	{
		/*Base*/
		template<typename T, char ElementsCount>
		struct Vec
		{
			Vec& operator-();

			//Scalar
			Vec operator+(const T& scalar) const;
			Vec operator-(const T& scalar) const;
			Vec operator*(const T& scalar) const;
			Vec operator/(const T& scalar) const;

			Vec& operator+=(const T& scalar);
			Vec& operator-=(const T& scalar);
			Vec& operator*=(const T& scalar);
			Vec& operator/=(const T& scalar);

			//Vector
			Vec operator+(const Vec& other) const;
			Vec operator-(const Vec& other) const;
			Vec operator*(const Vec& other) const;

			Vec& operator+=(const Vec& other);
			Vec& operator-=(const Vec& other);
			Vec& operator*=(const Vec& other);

			//Other
			const float Length() const;
			const float LengthSqr() const;
			void Normalize();
			T Dot(const Vec& other) const;
			T& operator[](const char& index);

			//Count
			constexpr char Count() const;
		};

		template<typename T>
		struct Vec<T, 2>
		{
			union
			{
				struct
				{
					T x, y;
				};
		
				struct
				{
					T r, g;
				};
		
				struct
				{
					T s, t;
				};
			};
		
			Vec() : x((T)0.0), y((T)0.0) {}
			Vec(const T& value) : x(value), y(value) {}
			Vec(const T& x, const T& y) : x(x), y(y) {}
			Vec(const Vec<T, 2>& other) : x(other.x), y(other.y) {}
			Vec(const Vec<T, 3>& other) : x(other.x), y(other.y) {}
			Vec(const Vec<T, 4>& other) : x(other.x), y(other.y) {}
		
			Vec<T, 2>& operator-()
			{
				x = -x;
				y = -y;
				return *this;
			}
		
			T& operator[](const char& index)
			{
				switch (index)
				{
				case 0:
					return x;
				case 1:
					return y;
				default:
					throw "Out of range";
				}
			}
		
			//scalar
			Vec<T, 2> operator+(const T& scalar) const
			{
				return { x + scalar, y + scalar };
			}
		
			Vec<T, 2> operator-(const T& scalar) const
			{
				return { x - scalar, y - scalar };
			}
		
			Vec<T, 2> operator*(const T& scalar) const
			{
				return { x * scalar, y * scalar };
			}
		
			Vec<T, 2> operator/(const T& scalar) const
			{
				if (!scalar)
					throw "Can't division by 0";
		
				return { x / scalar, y / scalar };
			}
		
			Vec<T, 2>& operator+=(const T& scalar)
			{
				x += scalar;
				y += scalar;
				return *this;
			}
		
			Vec<T, 2>& operator-=(const T& scalar)
			{
				x -= scalar;
				y -= scalar;
				return *this;
			}
		
			Vec<T, 2>& operator*=(const T& scalar)
			{
				x *= scalar;
				y *= scalar;
				return *this;
			}
		
			Vec<T, 2>& operator/=(const T& scalar)
			{
				if (!scalar)
					throw "Can't division by 0";
		
				x /= scalar;
				y /= scalar;
				return *this;
			}
		
			//Vec2
			Vec<T, 2> operator+(const Vec<T, 2>& other) const
			{
				return { x + other.x, y + other.y };
			}
		
			Vec<T, 2> operator-(const Vec<T, 2>& other) const
			{
				return { x - other.x, y - other.y };
			}
		
			Vec<T, 2> operator*(const Vec<T, 2>& other) const
			{
				return { x * other.x, y * other.y };
			}
		
			Vec<T, 2>& operator+=(const Vec<T, 2>& other)
			{
				x += other.x;
				y += other.y;
				return *this;
			}
		
			Vec<T, 2>& operator-=(const Vec<T, 2>& other)
			{
				x -= other.x;
				y -= other.y;
				return *this;
			}
		
			Vec<T, 2>& operator*=(const Vec<T, 2>& other)
			{
				x *= other.x;
				y *= other.y;
				return *this;
			}

			//Vec3
			Vec<T, 2> operator+(const Vec<T, 3>& other) const
			{
				return { x + other.x, y + other.y };
			}

			Vec<T, 2> operator-(const Vec<T, 3>& other) const
			{
				return { x - other.x, y - other.y };
			}

			Vec<T, 2> operator*(const Vec<T, 3>& other) const
			{
				return { x * other.x, y * other.y };
			}

			Vec<T, 2>& operator+=(const Vec<T, 3>& other)
			{
				x += other.x;
				y += other.y;
				return *this;
			}

			Vec<T, 2>& operator-=(const Vec<T, 3>& other)
			{
				x -= other.x;
				y -= other.y;
				return *this;
			}

			Vec<T, 2>& operator*=(const Vec<T, 3>& other)
			{
				x *= other.x;
				y *= other.y;
				return *this;
			}

			//Vec4
			Vec<T, 2> operator+(const Vec<T, 4>& other) const
			{
				return { x + other.x, y + other.y };
			}

			Vec<T, 2> operator-(const Vec<T, 4>& other) const
			{
				return { x - other.x, y - other.y };
			}

			Vec<T, 2> operator*(const Vec<T, 4>& other) const
			{
				return { x * other.x, y * other.y };
			}

			Vec<T, 2>& operator+=(const Vec<T, 4>& other)
			{
				x += other.x;
				y += other.y;
				return *this;
			}

			Vec<T, 2>& operator-=(const Vec<T, 4>& other)
			{
				x -= other.x;
				y -= other.y;
				return *this;
			}

			Vec<T, 2>& operator*=(const Vec<T, 4>& other)
			{
				x *= other.x;
				y *= other.y;
				return *this;
			}
		
			//Length
			const T Length() const
			{
				return Math::Sqrt<T>((x * x) + (y * y));
			}
		
			const T LengthSqr() const
			{
				return (x * x) + (y * y);
			}
		
			//Normalize
			void Normalize()
			{
				const T length = Length();
		
				if (length == (T)1.0)
					return;
		
				x /= length;
				y /= length;
			}
		
			//Dot product
			T Dot(const Vec<T, 2>& other) const
			{
				return (x * other.x) + (y * other.y);
			}

			//Cast operator
			Vec<T, 3> ToVec3() const
			{
				return { x, y, (T)0.0 };
			}

			Vec<T, 4> ToVec4() const
			{
				return { x, y, (T)0.0, (T)0.0};
			}

			//Count
			constexpr char Count() const
			{
				return 2;
			}
		};

		template<typename T>
		struct Vec<T, 3>
		{
			union
			{
				struct
				{
					T x, y, z;
				};

				struct
				{
					T r, g, b;
				};

				struct
				{
					T s, t, p;
				};
			};

			Vec() : x((T)0.0), y((T)0.0), z((T)0.0) {}
			Vec(const T& value) : x(value), y(value), z(value) {}
			Vec(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}
			Vec(const Vec<T, 2>& other) : x(other.x), y(other.y), z((T)0.0) {}
			Vec(const Vec<T, 3>& other) : x(other.x), y(other.y), z(other.z) {}
			Vec(const Vec<T, 4>& other) : x(other.x), y(other.y), z(other.z) {}

			Vec<T, 3>& operator-()
			{
				x = -x;
				y = -y;
				z = -z;
				return *this;
			}

			T& operator[](const char& index)
			{
				switch (index)
				{
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				default:
					throw "Out of range";
				}
			}

			//scalar
			Vec<T, 3> operator+(const T& scalar) const
			{
				return { x + scalar, y + scalar, z + scalar };
			}

			Vec<T, 3> operator-(const T& scalar) const
			{
				return { x - scalar, y - scalar, z - scalar };
			}

			Vec<T, 3> operator*(const T& scalar) const
			{
				return { x * scalar, y * scalar, z * scalar };
			}

			Vec<T, 3> operator/(const T& scalar) const
			{
				if (!scalar)
					throw "Can't division by 0";

				return { x / scalar, y / scalar, z / scalar };
			}

			Vec<T, 3>& operator+=(const T& scalar)
			{
				x += scalar;
				y += scalar;
				z += scalar;
				return *this;
			}

			Vec<T, 3>& operator-=(const T& scalar)
			{
				x -= scalar;
				y -= scalar;
				z -= scalar;
				return *this;
			}

			Vec<T, 3>& operator*=(const T& scalar)
			{
				x *= scalar;
				y *= scalar;
				z *= scalar;
				return *this;
			}

			Vec<T, 3>& operator/=(const T& scalar)
			{
				if (!scalar)
					throw "Can't division by 0";

				x /= scalar;
				y /= scalar;
				z /= scalar;
				return *this;
			}

			//Vec2
			Vec<T, 3> operator+(const Vec<T, 2>& other) const
			{
				return { x + other.x, y + other.y, z };
			}

			Vec<T, 3> operator-(const Vec<T, 2>& other) const
			{
				return { x - other.x, y - other.y, z };
			}

			Vec<T, 3> operator*(const Vec<T, 2>& other) const
			{
				return { x * other.x, y * other.y, z };
			}

			Vec<T, 3>& operator+=(const Vec<T, 2>& other)
			{
				x += other.x;
				y += other.y;
				return *this;
			}

			Vec<T, 3>& operator-=(const Vec<T, 2>& other)
			{
				x -= other.x;
				y -= other.y;
				return *this;
			}

			Vec<T, 3>& operator*=(const Vec<T, 2>& other)
			{
				x *= other.x;
				y *= other.y;
				return *this;
			}

			//Vec3
			Vec<T, 3> operator+(const Vec<T, 3>& other) const
			{
				return { x + other.x, y + other.y, z + other.z };
			}

			Vec<T, 3> operator-(const Vec<T, 3>& other) const
			{
				return { x - other.x, y - other.y, z - other.z};
			}

			Vec<T, 3> operator*(const Vec<T, 3>& other) const
			{
				return { x * other.x, y * other.y, z * other.z };
			}

			Vec<T, 3>& operator+=(const Vec<T, 3>& other)
			{
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}

			Vec<T, 3>& operator-=(const Vec<T, 3>& other)
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}

			Vec<T, 3>& operator*=(const Vec<T, 3>& other)
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}

			//Vec4
			Vec<T, 3> operator+(const Vec<T, 4>& other) const
			{
				return { x + other.x, y + other.y, z + other.z };
			}

			Vec<T, 3> operator-(const Vec<T, 4>& other) const
			{
				return { x - other.x, y - other.y, z - other.z };
			}

			Vec<T, 3> operator*(const Vec<T, 4>& other) const
			{
				return { x * other.x, y * other.y, z * other.z };
			}

			Vec<T, 3>& operator+=(const Vec<T, 4>& other)
			{
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}

			Vec<T, 3>& operator-=(const Vec<T, 4>& other)
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}

			Vec<T, 3>& operator*=(const Vec<T, 4>& other)
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}

			//Length
			const T Length() const
			{
				return Math::Sqrt<T>((x * x) + (y * y) + (z * z));
			}

			const T LengthSqr() const
			{
				return (x * x) + (y * y) + (z * z);
			}

			//Normalize
			void Normalize()
			{
				const T length = Length();

				if (length == (T)1.0)
					return;

				x /= length;
				y /= length;
				z /= length;
			}

			//Dot product
			T Dot(const Vec<T, 3>& other) const
			{
				return (x * other.x) + (y * other.y) + (z * other.z);
			}

			//Cross product
			Vec<T, 3> Cross(const Vec<T, 3>& other)
			{
				return { (y * other.z) - (z * other.y), (z * other.x) - (x * other.z), (x * other.y) - (y * other.x) };
			}
			
			//Cast operator
			Vec<T, 2> ToVec2() const
			{
				return { x, y };
			}

			Vec<T, 4> ToVec4() const
			{
				return { x, y, z, (T)0.0 };
			}

			//Count
			constexpr char Count() const
			{
				return 3;
			}
		};

		template<typename T>
		struct Vec<T, 4>
		{
			union
			{
				struct
				{
					T x, y, z, w;
				};

				struct
				{
					T r, g, b, a;
				};

				struct
				{
					T s, t, p, q;
				};
			};

			Vec() : x((T)0.0), y((T)0.0), z((T)0.0), w((T)0.0) {}
			Vec(const T& value) : x(value), y(value), z(value), w(value) {}
			Vec(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}
			Vec(const Vec<T, 2>& other) : x(other.x), y(other.y), z((T)0.0), w((T)0.0) {}
			Vec(const Vec<T, 3>& other) : x(other.x), y(other.y), z(other.z), w((T)0.0) {}
			Vec(const Vec<T, 4>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

			Vec<T, 4>& operator-()
			{
				x = -x;
				y = -y;
				z = -z;
				w = -w;
				return *this;
			}

			T& operator[](const char& index)
			{
				switch (index)
				{
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				case 3:
					return w;
				default:
					throw "Out of range";
				}
			}

			//scalar
			Vec<T, 4> operator+(const T& scalar) const
			{
				return { x + scalar, y + scalar, z + scalar, w + scalar };
			}

			Vec<T, 4> operator-(const T& scalar) const
			{
				return { x - scalar, y - scalar, z - scalar, w - scalar };
			}

			Vec<T, 4> operator*(const T& scalar) const
			{
				return { x * scalar, y * scalar, z * scalar, w * scalar };
			}

			Vec<T, 4> operator/(const T& scalar) const
			{
				if (!scalar)
					throw "Can't division by 0";

				return { x / scalar, y / scalar, z / scalar, w / scalar };
			}

			Vec<T, 4>& operator+=(const T& scalar)
			{
				x += scalar;
				y += scalar;
				z += scalar;
				w += scalar;
				return *this;
			}

			Vec<T, 4>& operator-=(const T& scalar)
			{
				x -= scalar;
				y -= scalar;
				z -= scalar;
				w -= scalar;
				return *this;
			}

			Vec<T, 4>& operator*=(const T& scalar)
			{
				x *= scalar;
				y *= scalar;
				z *= scalar;
				w -= scalar;
				return *this;
			}

			Vec<T, 4>& operator/=(const T& scalar)
			{
				if (!scalar)
					throw "Can't division by 0";

				x /= scalar;
				y /= scalar;
				z /= scalar;
				w /= scalar;
				return *this;
			}

			//Vec2
			Vec<T, 4> operator+(const Vec<T, 2>& other) const
			{
				return { x + other.x, y + other.y, z, w };
			}

			Vec<T, 4> operator-(const Vec<T, 2>& other) const
			{
				return { x - other.x, y - other.y, z, w };
			}

			Vec<T, 4> operator*(const Vec<T, 2>& other) const
			{
				return { x * other.x, y * other.y, z, w };
			}

			Vec<T, 4>& operator+=(const Vec<T, 2>& other)
			{
				x += other.x;
				y += other.y;
				return *this;
			}

			Vec<T, 4>& operator-=(const Vec<T, 2>& other)
			{
				x -= other.x;
				y -= other.y;
				return *this;
			}

			Vec<T, 4>& operator*=(const Vec<T, 2>& other)
			{
				x *= other.x;
				y *= other.y;
				return *this;
			}

			//Vec3
			Vec<T, 4> operator+(const Vec<T, 3>& other) const
			{
				return { x + other.x, y + other.y, z + other.z, w };
			}

			Vec<T, 4> operator-(const Vec<T, 3>& other) const
			{
				return { x - other.x, y - other.y, z - other.z, w };
			}

			Vec<T, 4> operator*(const Vec<T, 3>& other) const
			{
				return { x * other.x, y * other.y, z * other.z, w };
			}

			Vec<T, 4>& operator+=(const Vec<T, 3>& other)
			{
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}

			Vec<T, 4>& operator-=(const Vec<T, 3>& other)
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}

			Vec<T, 4>& operator*=(const Vec<T, 3>& other)
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}

			//Vec4
			Vec<T, 4> operator+(const Vec<T, 4>& other) const
			{
				return { x + other.x, y + other.y, z + other.z, w + other.w };
			}

			Vec<T, 4> operator-(const Vec<T, 4>& other) const
			{
				return { x - other.x, y - other.y, z - other.z. w - other.w };
			}

			Vec<T, 4> operator*(const Vec<T, 4>& other) const
			{
				return { x * other.x, y * other.y, z * other.z, w * other.w };
			}

			Vec<T, 4>& operator+=(const Vec<T, 4>& other)
			{
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;
				return *this;
			}

			Vec<T, 4>& operator-=(const Vec<T, 4>& other)
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;
				return *this;
			}

			Vec<T, 4>& operator*=(const Vec<T, 4>& other)
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				w *= other.w;
				return *this;
			}

			//Length
			const T Length() const
			{
				return Math::Sqrt<T>((x * x) + (y * y) + (z * z) + (w * w));
			}

			const T LengthSqr() const
			{
				return (x * x) + (y * y) + (z * z) + (w * w);
			}

			//Normalize
			void Normalize()
			{
				const T length = Length();

				if (length == (T)1.0)
					return;

				x /= length;
				y /= length;
				z /= length;
				w /= length;
			}

			//Dot product
			T Dot(const Vec<T, 4>& other) const
			{
				return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
			}

			//Cast operator
			Vec<T, 2> ToVec2() const
			{
				return { x, y };
			}

			Vec<T, 3> ToVec3() const
			{
				return { x, y, z };
			}

			//Count
			constexpr char Count() const
			{
				return 4;
			}
		};

		//char
		typedef Vec<char, 2> CVec2;
		typedef Vec<char, 3> CVec3;
		typedef Vec<char, 4> CVec4;

		//UChar
		typedef Vec<UChar, 2> UCVec2;
		typedef Vec<UChar, 3> UCVec3;
		typedef Vec<UChar, 4> UCVec4;

		//SInt
		typedef Vec<SInt, 2> SIVec2;
		typedef Vec<SInt, 3> SIVec3;
		typedef Vec<SInt, 4> SIVec4;

		//USInt
		typedef Vec<USInt, 2> USIVec2;
		typedef Vec<USInt, 3> USIVec3;
		typedef Vec<USInt, 4> USIVec4;

		//int
		typedef Vec<int, 2> IVec2;
		typedef Vec<int, 3> IVec3;
		typedef Vec<int, 4> IVec4;

		//UInt
		typedef Vec<UInt, 2> UIVec2;
		typedef Vec<UInt, 3> UIVec3;
		typedef Vec<UInt, 4> UIVec4;

		//float
		typedef Vec<float, 2> Vec2;
		typedef Vec<float, 3> Vec3;
		typedef Vec<float, 4> Vec4;

		//double
		typedef Vec<double, 2> DVec2;
		typedef Vec<double, 3> DVec3;
		typedef Vec<double, 4> DVec4;

		//LInt
		typedef Vec<LInt, 2> LIVec2;
		typedef Vec<LInt, 3> LIVec3;
		typedef Vec<LInt, 4> LIVec4;

		//ULInt
		typedef Vec<ULInt, 2> ULIVec2;
		typedef Vec<ULInt, 3> ULIVec3;
		typedef Vec<ULInt, 4> ULIVec4;
	}
}