#pragma once

#include "../Base.h"

#ifndef BEAR_STRING_SIZE
	#define BEAR_STRING_SIZE 1023
#endif

#if BEAR_STRING_SIZE < 1
	#error "String size can't be less than 1"
#endif

namespace Bear
{
	namespace Collections
	{
		struct StringIterator
		{
		};

		class String : public Base<char>
		{
		private:
			char strStack[BEAR_STRING_SIZE + 1];
			char* strHeap;

			char* str;
		public:
			using Iterator = Iterator<char, StringIterator>;
		public:
			void Copy(char* src);
		public:
			String();
			String(const char* src);
			String(char* src);
			String(const String& other);
			~String();
		public:
			Iterator begin();
			Iterator end();

			const Iterator begin() const;
			const Iterator end() const;
		public:
			const LInt ToInt() const;
			const ULInt ToUInt() const;
			const float ToFloat() const;
			const double ToDouble() const;
		public:
			const char* const ToCharPtr() const;
		public:
			void Clear() override;
		public:
			const bool Exist(const char& element, ULInt* index = nullptr) const;
			void Add(const char& element);
		public:
			template<typename Collection>
			void AddCollection(const Collection& elements)
			{
				char* newStr = new char[this->length + elements.Length()];

				ULInt i = 0;

				for (i = 0; i < this->length; i++)
					newStr[i] = str[i];

				for (auto& it : elements)
				{
					newStr[i] = it;
					i++;
				}

				delete[] str;

				str = newStr;

				this->length += elements.Length();

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, (void*)&elements, TypeOfCallback::Add);
			}

			template<typename Collection>
			void RemoveCollection(const Collection& elements, const bool& removeAll = false)
			{
				if (!str || !this->length)
					return;

				if (removeAll)
				{
					ULInt removeElements = 0;

					for (ULInt i = 0; i < this->length; i++)
					{
						bool found = false;

						for (auto& it : elements)
						{
							if (str[i] == it)
							{
								found = true;
								break;
							}
						}

						if (found)
							removeElements++;
						else
						{
							char element = str[i];

							str[i] = str[i - removeElements];
							str[i - removeElements] = element;
						}
					}

					if (removeElements)
					{
						this->length -= removeElements;

						char* array = new char[this->length];

						for (ULInt i = 0; i < this->length; i++)
							array[i] = str[i];

						delete[] str;

						str = array;
					}
				}
				else
				{
					bool* notRemoved = new bool[elements.Length()];

					ULInt removeElements = 0;

					for (ULInt i = 0; i < this->length; i++)
					{
						bool found = false;

						ULInt j = 0;
						for (auto& it : elements)
						{
							if (notRemoved[j] && (str[i] == it))
							{
								notRemoved[j] = false;
								found = true;
								break;
							}

							j++;
						}

						if (found)
							removeElements++;
						else
						{
							char element = str[i];

							str[i] = str[i - removeElements];
							str[i - removeElements] = element;
						}
					}

					if (removeElements)
					{
						this->length -= removeElements;

						char* array = new char[this->length];

						for (ULInt i = 0; i < this->length; i++)
							array[i] = str[i];

						delete[] str;

						str = array;
					}

					delete[] notRemoved;
				}

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Remove);
			}
		public:
			bool operator==(const String& other) const;
			bool operator!=(const String& other) const;
		public:
			void operator+=(const char& other);
			void operator+=(char* other);
			void operator+=(const char* other);
			void operator+=(const String& other);
		public:
			String operator+(const char& other);
			String operator+(char* other);
			String operator+(const char* other);
			String operator+(const String& other);
		public:
			virtual char& operator[](const ULInt& index) const override;
		public:
			static ULInt GetLength(char* src);
			static ULInt GetLength(const char* src);

			static void Copy(const char* src, char* dst);

			static bool Compare(char* first, char* second);
			static bool Compare(const char* first, char* second);
			static bool Compare(char* first, const char* second);
			static bool Compare(const char* first, const char* second);

			template<typename T>
			static const T ConvertTo(char* value);

			template<typename T>
			static const T ConvertTo(const char* value);
		public:
			template<typename T>
			static String ToString(const T& value);
		};

		template<>
		struct Iterator<char, StringIterator>
		{
		private:
			char* ptr;
		public:
			Iterator(char* ptr);
		public:
			char& operator*();
			const char& operator*() const;

			Iterator& operator--();

			Iterator& operator++();

			Iterator& operator-=(const ULInt& offset);

			Iterator& operator+=(const ULInt& offset);

			bool operator==(const Iterator& other);

			const bool operator==(const Iterator& other) const;

			bool operator!=(const Iterator& other);

			const bool operator!=(const Iterator& other) const;
		};
	}
}