#pragma once

#include "../Base.h"

namespace Bear
{
	namespace Collections
	{
		struct ConstStringIterator
		{
		};

		template<>
		struct ConstIterator<const char, ConstStringIterator>
		{
		private:
			const char* ptr;
		public:
			constexpr ConstIterator(const char* ptr)
				: ptr(ptr)
			{
			}
		public:
			constexpr const char& operator*() const
			{
				return *ptr;
			}

			constexpr ConstIterator& operator--()
			{
				ptr--;
				return *this;
			}

			constexpr ConstIterator& operator++()
			{
				ptr++;
				return *this;
			}

			constexpr bool operator==(const ConstIterator& other) const
			{
				return ptr == other.ptr;
			}

			constexpr bool operator!=(const ConstIterator& other) const
			{
				return !(*this == other);
			}
		};

		class ConstString : public ConstBase<const char>
		{
		private:
			const char* str;
		public:
			using Iterator = ConstIterator<const char, ConstStringIterator>;
		private:
			constexpr const ULInt GetLength(const char* str)
			{
				if (str == nullptr || str[0] == '\0')
					return 0;

				for (ULInt i = 1; ; i += 2)
				{
					if (str[i - 1] == '\0')
						return i - 1;

					if (str[i] == '\0')
						return i;
				}
			}
		public:
			constexpr ConstString(const char* src)
				: str(src), ConstBase(GetLength(src))
			{
			}

			constexpr ConstString(const char* src, const ULInt& offset)
				: str(src + offset), ConstBase(GetLength(src))
			{
			}

			constexpr ConstString(const ConstString& src)
				: str(src.str), ConstBase(src.length)
			{
			}
		public:
			constexpr const char* const ToCharPtr() const
			{
				return str;
			}

			constexpr const ULInt Length() const
			{
				return length;
			}
		public:
			constexpr ConstString Substr(const ULInt& first) const
			{
				return ConstString(&str[first]);
			}

			constexpr ConstString Substr(const ULInt& first, const ULInt& count) const
			{
				ConstString value(&str[first]);
				value.length = &str[first + count] - &str[first];

				return value;
			}

			template<bool FromEnd = false>
			constexpr ULInt Find(const char& element) const
			{
				if constexpr (FromEnd)
				{
					if (element == str[0])
						return 0;

					for (ULInt i = length - 1; i >= 1; i--)
					{
						if (element == str[i])
							return i;
					}
				}
				else
				{
					for (ULInt i = 0; i < length; i++)
					{
						if (element == str[i])
							return i;
					}
				}

				return 0;
			}
		public:
			constexpr Iterator begin() const
			{
				return Iterator(str);
			}

			constexpr Iterator end() const
			{
				return Iterator(str + length);
			}
		public:
			constexpr bool operator==(const ConstString& other) const
			{
				if (other.length != length)
					return false;

				for (ULInt i = 0; i < length; i++)
				{
					if (str[i] != other.str[i])
						return false;
				}

				return true;
			}

			constexpr bool operator!=(const ConstString& other) const
			{
				return !operator==(other);
			}

			constexpr const char& operator[](const ULInt& index) const
			{
				return str[index];
			}

			constexpr const bool Exist(const char& element) const
			{
				for (ULInt i = 0; i < length; i++)
				{
					if (str[i] == element)
						return true;
				}
				
				return false;
			}
		};
	}
}