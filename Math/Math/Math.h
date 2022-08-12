#pragma once

namespace Bear
{
	namespace Math
	{
		template<typename T, typename... Args>
		constexpr T Add(const Args&&... args)
		{
			return (... + (T)args);
		}

		template<typename T, typename... Args>
		constexpr T Substract(const Args&&... args)
		{
			return (... - (T)args);
		}

		template<typename T, typename... Args>
		constexpr T Multiple(const Args&&... args)
		{
			return (... * (T)args);
		}

		template<typename T, typename... Args>
		constexpr T Divide(const Args&&... args)
		{
			return (... / (T)args);
		}

		template<typename T>
		constexpr T Pow(const T& x, const T& y)
		{
			T value = (T)1;

			for (T i = 0; i < y; i++)
				value *= x;

			return value;
		}

		template<typename T>
		constexpr T Sqrt(const T& value)
		{
			T x = value / 2;
			
			T quotient = value / x;

			//TODO: Zmieniæ jeœli bêdzie Type::IsSigned(bo jeœli jest unsigned to nie trza tego absa) i dla is_floating(bo jeœli jest to jest int lub char to nie trza takiej precyzji)
			while (Abs<double>(x - quotient) > 0.000001)
			{
				x = (x + quotient) / 2;

				if (x * x == value)
					break;

				quotient = value / x;
			}
			
			return x;
		}

		template<typename T>
		constexpr T Abs(const T& value)
		{
			if (value < (T)0)
				return -value;

			return value;
		}
	}
}