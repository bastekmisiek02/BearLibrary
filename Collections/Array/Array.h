#pragma once

#include "../Base.h"

namespace Bear
{
	namespace Collections
	{
		struct ArrayIterator
		{
		};

		template<typename T>
		struct ConstIterator<T, ArrayIterator>
		{
		private:
			const T* ptr;
		public:
			constexpr ConstIterator(const T* ptr)
				: ptr(ptr)
			{
			}
		public:
			constexpr const T& operator*() const
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

		template<typename T, ULInt size>
		class Array : ConstBase<T>
		{
		public:
			using Iterator = ConstIterator<T, ArrayIterator>;
		private:
			T data[size];
		public:
			template<typename... Args>
			constexpr Array(const Args&&... args)
				: ConstBase<T>(size), data{args...}
			{
			}

			constexpr Iterator begin() const
			{
				return Iterator(data);
			}

			constexpr Iterator end() const
			{
				return Iterator(data + size);
			}
		};
	}
}