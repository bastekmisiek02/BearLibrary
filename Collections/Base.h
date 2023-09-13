#pragma once

#include "Bases.h"

#include <initializer_list>

#ifndef BEAR_DEFAULT_CAPACITY
	#define BEAR_DEFAULT_CAPACITY 10
#endif

namespace Bear
{
	namespace Collections
	{
		enum class TypeOfCallback : char
		{
			Add = 0,
			Remove = 1,
			Resize = 2,
			Swap = 3,
			Destroy = 4
		};

		template<typename T, typename IteratorType>
		struct Iterator
		{
		public:
			T& operator*();
			const T& operator*() const;

			IteratorType& operator--();

			IteratorType& operator++();

			IteratorType& operator-=(const ULInt& offset);

			IteratorType& operator+=(const ULInt& offset);

			bool operator==(const IteratorType& other);
			const bool operator==(const IteratorType& other) const;

			bool operator!=(const IteratorType& other);
			const bool operator!=(const IteratorType& other) const;
		};

		template<typename T, typename IteratorType>
		struct ConstIterator
		{
		public:
			constexpr T& operator*() const;

			constexpr IteratorType& operator--();

			constexpr IteratorType& operator++();

			constexpr IteratorType& operator-=(const ULInt& offset);

			constexpr IteratorType& operator+=(const ULInt& offset);

			constexpr bool operator==(const IteratorType& other) const;

			constexpr bool operator!=(const IteratorType& other) const;
		};

		template<typename T>
		class ConstBase
		{
		protected:
			ULInt length;
		protected:
			constexpr ConstBase()
				: length(0)
			{
			}

			constexpr ConstBase(const ULInt& length)
				: length(length)
			{
			}
		public:
			static constexpr ULInt GetMaxLength()
			{
				#ifdef WIN32
					return 2147483647;
				#else
					return 0xffffffffffffffffui64;
				#endif
			}
		};

		template<typename T>
		class Base
		{
		public:
			typedef void(*OnCollectionLengthChanged)(Base<T>* collection, void* element, const TypeOfCallback&& type);
		protected:
			OnCollectionLengthChanged onCollectionLengthChanged;
		protected:
			ULInt length;
			ULInt capacity;
		protected:
			Base()
				: length(0), capacity(BEAR_DEFAULT_CAPACITY), onCollectionLengthChanged(nullptr)
			{
			}

			Base(const ULInt& capacity)
				: length(0), capacity(capacity), onCollectionLengthChanged(nullptr)
			{
			}
		public:
			virtual const ULInt Length() const
			{
				return this->length;
			}

			const ULInt Capacity() const
			{
				return this->capacity;
			}
		public:
			void SetOnCollectionLengthChanged(const OnCollectionLengthChanged& callback)
			{
				onCollectionLengthChanged = callback;
			}

			const OnCollectionLengthChanged& GetOnCollectionLengthChanged() const
			{
				return onCollectionLengthChanged;
			}
		public:
			T& GetFromIndex(const ULInt& index) const
			{
				if (index > this->length - 1)
					throw CollectionExceptions::OutOfRange;

				if (index < 0)
					throw CollectionExceptions::IndexLower;

				if (!this->length)
					throw CollectionExceptions::CollectionClear;

				return this->operator[](index);
			}
		public:
			virtual void Clear() = 0;
			virtual T& operator[](const ULInt& index) const = 0;
		public:
			static constexpr ULInt GetMaxLength()
			{
				#ifdef WIN32
					return 2147483647;
				#else
					return 0xffffffffffffffffui64;
				#endif
			}
		};
	}
}