#pragma once

namespace Bear
{
	namespace Math
	{
		template<typename T>
		constexpr T Abs(const T& value)
		{
			if (value < (T)0)
				return -value;

			return value;
		}

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
		
		constexpr double Sqrt(const double& value)
		{
			double x = value * 0.5;
			
			double quotient = value / x;

			while (Abs<double>(x - quotient) > 0.000001)
			{
				x = 0.5 * (x + quotient);

				if (x * x == value)
					break;

				quotient = value / x;
			}
			
			return x;
		}
	}
}