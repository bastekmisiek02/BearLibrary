#pragma once

#include "Collections/String/ConstString.h"

namespace Bear
{
	template<typename T>
	class Type
	{
	private:
		static constexpr ULInt Max(const ULInt& first, const ULInt& second)
		{
			if (first > second)
				return first;

			return second;
		}

		static constexpr Collections::ConstString _GetFullName()
		{
			constexpr Collections::ConstString funcName = __FUNCSIG__;

			constexpr ULInt begin = funcName.Find<true>('<') + 1;
			constexpr ULInt end = funcName.Find<true>('>');

			return funcName.Substr(begin, end - begin);
		}

		static constexpr Collections::ConstString _GetName()
		{
			constexpr Collections::ConstString funcName = __FUNCSIG__;

			constexpr Collections::ConstString functionName(funcName.Substr(0, funcName.Find<true>('>') + 1));

			constexpr ULInt first = functionName.Find<true>(':') + 1;
			constexpr ULInt second = functionName.Find<true>('<') + 1;
			constexpr ULInt end = functionName.Find<true>('>');

			constexpr ULInt begin = Max(first, second);

			return functionName.Substr(begin, end - begin);
		}

		static constexpr ULInt _GetID()
		{
			constexpr Collections::ConstString name = _GetName();

			ULInt value = 0;

			for (ULInt i = 0; i < name.Length(); i++)
				value += (name[i] + (1 << i));

			return value;
		}

		template <typename T1, typename T2>
		struct _IsSame
		{
			static constexpr bool value = false;
		};

		template<typename T1>
		struct _IsSame<T1, T1>
		{
			static constexpr bool value = true;
		};

		template<typename Type>
		struct _IsPointer
		{
			static constexpr bool value = false;
		};

		template<typename Type>
		struct _IsPointer<Type*>
		{
			static constexpr bool value = true;
		};
	public:
		static Collections::String GetFullName()
		{
			constexpr Collections::ConstString fullName(_GetFullName());

			Collections::String value(fullName.ToCharPtr());
			value[fullName.Length()] = '\0';

			return value;
		}

		static Collections::String GetName()
		{
			constexpr Collections::ConstString name(_GetName());

			Collections::String value(name.ToCharPtr());
			value[name.Length()] = '\0';
			
			return value;
		}

		template<typename Arg>
		static constexpr bool IsSame(const Arg& arg)
		{
			return _IsSame<T, Arg>::value;
		}

		template<typename Arg>
		static constexpr bool IsSame()
		{
			return _IsSame<T, Arg>::value;
		}

		static constexpr bool IsPointer()
		{
			return _IsPointer<T>::value;
		}

		static constexpr ULInt GetID()
		{
			constexpr ULInt id = _GetID();

			return id;
		}
	};
}