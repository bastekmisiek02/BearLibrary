#pragma once

#include "../Base.h"

#include <vector>

namespace Bear
{
	namespace Collections
	{
		struct DynamicArrayIterator
		{
		};

		template <typename T>
		class DynamicArray : public Bear::Collections::Base<T>
		{
		private:
			/// <summary>
			/// Array of items in list
			/// </summary>
			T* items;
		public:
			using Iterator = Iterator<T, DynamicArrayIterator>;
		public:
			/// <summary>
			/// Create dynamicArray from std::initializer_list
			/// </summary>
			/// <param name="list"></param>
			DynamicArray(const std::initializer_list<T>& list)
			{
				this->length = list.size();

				items = new T[this->length];

				auto it = list.begin();
				for (ULInt i = 0; i < this->length; i++)
				{
					items[i] = *it;
					it++;
				}
			}

			/// <summary>
			/// Create dynamic array with this->length of Elements.Length() and copy data from "Elements" to this->items
			/// </summary>
			/// <param name="Elements">- DynamicArray from where will be copy data</param>
			DynamicArray(const DynamicArray<T>& elements)
			{
				this->length = elements.length;

				items = new T[elements.length];

				for (ULInt i = 0; i < elements.length; i++)
					items[i] = elements[i];
			}

			/// <summary>
			/// Create empty dynamic array with Length
			/// </summary>
			/// <param name="Length">- Length of elements</param>
			DynamicArray(const ULInt& length)
			{
				this->length = length;

				items = new T[this->length];
			}

			/// <summary>
			/// Create list with this->length of Length and copy data from "Array" to this->items
			/// </summary>
			/// <param name="Array">- Array from where will be copy data</param>
			/// <param name="Length">- Length of elements</param>
			DynamicArray(const T* array, const ULInt& length)
			{
				this->length = length;

				items = new T[this->length];

				for (ULInt i = 0; i < this->length; i++)
					items[i] = array[i];
			}

			/// <summary>
			/// Create dynamic array with this->length "Length" and set all items to "Value"
			/// </summary>
			/// <param name="Length">- Dynamic array size</param>
			/// <param name="Value">- All items will be the same "Value"</param>
			DynamicArray(const ULInt& length, const T& value)
			{
				Resize(length, value);
			}

			/// <summary>
			/// Create an empty dynamic array of size 0
			/// </summary>
			DynamicArray()
				: items(nullptr)
			{
			}

			~DynamicArray()
			{
				Clear();
			}
		public:
			/// <summary>
			/// Check if element exists and if "Index" isn't null "Index" will be index of search element
			/// </summary>
			/// <param name="Element">- Search element</param>
			/// <param name="FromEnd">- If true search will be from end</param>
			/// <param name="Index">- If isn't null return index of search element</param>
			/// <returns>Return true if element exist in list, otherwise return false</returns>
			bool Exist(const T& element, ULInt* index = nullptr) const
			{
				for (ULInt i = 0; i < this->length; i++)
				{
					if (items[i] == element)
					{
						if (index)
							*index = i;

						return true;
					}
				}

				return false;
			}

			/// <summary>
			/// Add elements from "Elements" and Length += Elements.Length()
			/// </summary>
			/// <param name="Elements">- DynamicArray from where will be add items</param>
			void AddCollection(const DynamicArray<T>& elements)
			{
				T* array = new T[this->length + elements.length];

				ULInt i = 0;

				for (i = 0; i < this->length; i++)
					array[i] = items[i];

				for (; i < this->length + elements.length; i++)
					array[i] = elements.items[i - this->length];

				delete[] items;

				items = array;

				this->length += elements.length;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, (void*)&elements, TypeOfCallback::Add);
			}

			template<typename Collection>
			void AddCollection(const Collection& elements)
			{
				T* array = new T[this->length + elements.Length()];

				ULInt i = 0;

				for (i = 0; i < this->length; i++)
					array[i] = items[i];

				for (auto& it : elements)
				{
					array[i] = it;
					i++;
				}

				delete[] items;

				items = array;

				this->length += elements.Length();

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, (void*)&elements, TypeOfCallback::Add);
			}

			void AddCollection(const std::initializer_list<T>& elements)
			{
				T* array = new T[this->length + elements.size()];

				ULInt i = 0;

				for (i = 0; i < this->length; i++)
					array[i] = items[i];

				for (auto& it : elements)
				{
					array[i] = it;
					i++;
				}

				delete[] items;

				items = array;

				this->length += elements.size();

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, (void*)&elements, TypeOfCallback::Add);
			}

			/// <summary>
			/// Add "Element" to dynamic array
			/// </summary>
			/// <param name="Element">- Added element</param>
			void Add(const T& element)
			{
				T* array = new T[this->length + 1];

				for (ULInt i = 0; i < this->length; i++)
					array[i] = this->items[i];

				array[this->length] = element;

				delete[] this->items;

				this->items = array;

				this->length++;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, (void*)&element, TypeOfCallback::Add);
			}

			/// <summary>
			/// Removing "Elements" from dynamic array
			/// </summary>
			/// <param name="Elements">- Removed elements</param>
			/// <param name="removeAll">- If true removing all elements where Elements[n] == items[i], otherwise remove first element where Elements[n] == items[i]</param>
			template<bool RemoveAll = false>
			void RemoveCollection(const DynamicArray<T>& elements)
			{
				if (!items || !this->length)
					return;

				if constexpr(RemoveAll)
				{
					ULInt removeElements = 0;

					for (ULInt i = 0; i < this->length; i++)
					{
						bool found = false;

						for (ULInt j = 0; j < elements.length; j++)
						{
							if (items[i] == elements.items[j])
							{
								found = true;
								break;
							}
						}

						if (found)
							removeElements++;
						else
						{
							T element = items[i];

							items[i] = items[i - removeElements];
							items[i - removeElements] = element;
						}
					}

					if (removeElements)
					{
						this->length -= removeElements;

						T* array = new T[this->length];

						for (ULInt i = 0; i < this->length; i++)
							array[i] = items[i];

						delete[] items;

						items = array;
					}
				}
				else
				{
					bool* notRemoved = new bool[elements.length];

					ULInt removeElements = 0;

					for (ULInt i = 0; i < this->length; i++)
					{
						bool found = false;

						for (ULInt j = 0; j < elements.length; j++)
						{
							if ((items[i] == elements.items[j]) && (notRemoved[j]))
							{
								notRemoved[j] = false;
								found = true;
								break;
							}
						}

						if (found)
							removeElements++;
						else
						{
							T element = items[i];

							items[i] = items[i - removeElements];
							items[i - removeElements] = element;
						}
					}

					if (removeElements)
					{
						this->length -= removeElements;

						T* array = new T[this->length];

						for (ULInt i = 0; i < this->length; i++)
							array[i] = items[i];

						delete[] items;

						items = array;
					}

					delete[] notRemoved;
				}

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Remove);
			}

			template<typename Collection, bool RemoveAll = false>
			void RemoveCollection(const Collection& elements)
			{
				if (!items || !this->length)
					return;

				if constexpr (RemoveAll)
				{
					ULInt removeElements = 0;

					for (ULInt i = 0; i < this->length; i++)
					{
						bool found = false;

						for (auto& it : elements)
						{
							if (items[i] == it)
							{
								found = true;
								break;
							}
						}

						if (found)
							removeElements++;
						else
						{
							T element = items[i];

							items[i] = items[i - removeElements];
							items[i - removeElements] = element;
						}
					}

					if (removeElements)
					{
						this->length -= removeElements;

						T* array = new T[this->length];

						for (ULInt i = 0; i < this->length; i++)
							array[i] = items[i];

						delete[] items;

						items = array;
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
							if (notRemoved[j] && (items[i] == it))
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
							T element = items[i];

							items[i] = items[i - removeElements];
							items[i - removeElements] = element;
						}
					}

					if (removeElements)
					{
						this->length -= removeElements;

						T* array = new T[this->length];

						for (ULInt i = 0; i < this->length; i++)
							array[i] = items[i];

						delete[] items;

						items = array;
					}

					delete[] notRemoved;
				}

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Remove);
			}

			/// <summary>
			/// Removing "Element" from dynamic array
			/// </summary>
			/// <param name="Element">- Removed element</param>
			/// <param name="removeAll">- If true removing all elements where Element == items[i], otherwise remove first element where Element == items[i]</param>
			template<bool RemoveAll = false>
			void Remove(const T& element)
			{
				if (!items || !this->length)
					return;

				T* array = new T[this->length];

				if constexpr(RemoveAll)
				{
					ULInt j = 0;
					ULInt removeItems = 0;

					for (ULInt i = 0; i < this->length; i++)
					{
						if (this->items[i] != element)
						{
							array[j] = this->items[i];
							j++;
						}
						else
							removeItems++;
					}

					this->length -= removeItems;
				}
				else
				{
					bool found = false;

					for (ULInt i = 0; i < this->length; i++)
					{
						if (found || this->items[i] != element)
							array[i - found] = this->items[i];
						else
							found = true;
					}

					this->length--;
				}

				delete[] this->items;

				this->items = array;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Remove);
			}

			/// <summary>
			/// Removing elements from "Start" to "End"
			/// </summary>
			/// <param name="Start">- Index from will be removed items</param>
			/// <param name="End">- End index removed items</param>
			void RemoveOnIndex(const ULInt& start, const ULInt& end)
			{
				if (!items || !this->length)
					return;

				if (start > this->length || end > this->length)
					throw CollectionExceptions::OutOfRange;

				if (start > end)
					throw CollectionExceptions::StartIndexGreaterThanEnd;

				T* array = new T[this->length];

				ULInt j = 0;

				for (ULInt i = 0; i < this->length; i++)
				{
					if (!(i >= start && i <= end))
						array[i - j] = items[i];
					else
						j++;
				}

				delete[] items;

				this->length -= (end - start) + 1;

				items = array;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Remove);
			}

			/// <summary>
			/// Remove elements from "Start" index to end
			/// </summary>
			/// <param name="Start">- Index where we start removing elements</param>
			void RemoveOnIndex(const ULInt& start)
			{
				if (!items || !this->length)
					return;

				if (start > this->length)
					throw CollectionExceptions::OutOfRange;

				this->length = start;

				T* array = new T[this->length];

				for (ULInt i = 0; i < this->length; i++)
					array[i] = items[i];

				delete[] items;

				items = array;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Remove);
			}

			Iterator begin() const
			{
				return Iterator(items);
			}

			Iterator end() const
			{
				return Iterator(items + this->length);
			}

			/// <summary>
			/// Clear the dynamic array
			/// </summary>
			virtual void Clear() override
			{
				delete[] items;
				items = nullptr;
				this->length = 0;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Destroy);
			}

			/// <summary>
			/// If "T" is pointer to heap, use this to free memory
			/// </summary>
			void Destroy() const
			{
				for (ULInt i = 0; i < this->length; i++)
					delete this->items[i];
			}

			/// <summary>
			/// Return pointer to first element of list
			/// </summary>
			/// <returns></returns>
			const T* Data() const
			{
				return items;
			}

			/// <summary>
			/// Return pointer to first element of list
			/// </summary>
			/// <returns></returns>
			T* Data()
			{
				return items;
			}

			/// <summary>
			/// Sort list
			/// </summary>
			/// <param name="SortFunc">- If return true "firstElement" will be closer </param>
			void Sort(const bool (*SortFunc)(const T& firstElement, const T& secondElement)) const
			{
				if (!items || !this->length)
					throw CollectionExceptions::CollectionClear;

				if (this->length == 1)
					return;

				for (ULInt i = 1; i < this->length; i++)
				{
					T* firstElement = &items[i - 1];
					T* secondElement = &items[i];

					for (ULInt j = 0; j < i; j++)
					{
						if (!SortFunc(*firstElement, *secondElement))
						{
							const T helpItem = *firstElement;
							*firstElement = *secondElement;
							*secondElement = helpItem;

							firstElement = &items[i - j - 2];
							secondElement = &items[i - j - 1];
						}
						else
							break;
					}
				}
			}

			/// <summary>
			/// Swap items between this->items and "Elements"
			/// </summary>
			/// <param name="Elements"></param>
			void Swap(DynamicArray<T>& elements)
			{
				if (!items || !this->length)
				{
					operator=(elements);
					elements.length = 0;
					delete[] elements.items;
				}

				const ULInt length = this->length;
				T* items = new T[length];

				for (ULInt i = 0; i < length; i++)
					items[i] = this->items[i];

				delete[] this->items;

				this->items = elements.items;
				elements.items = items;

				this->length = elements.length;
				elements.length = length;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, items, TypeOfCallback::Swap);
			}

			/// <summary>
			/// Set this->length to "Length" and destroy data in dynamic array
			/// </summary>
			/// <param name="Length"></param>
			void Resize(const ULInt& length)
			{
				delete[] items;

				items = new T[length];

				this->length = length;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Resize);
			}

			/// <summary>
			/// Set this->length to "Length" and set items to "Value"
			/// </summary>
			/// <param name="Length"></param>
			/// <param name="Value"></param>
			void Resize(const ULInt& length, const T& value)
			{
				delete[] items;

				items = new T[length];

				this->length = length;

				for (ULInt i = 0; i < length; i++)
					items[i] = value;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Resize);
			}

			/// <summary>
			/// Create array and return it with the same data and this->length equals Array !!! REMEMBER use delete[] to destroy it !!!
			/// </summary>
			/// <param name="Length"></param>
			/// <returns></returns>
			T* ToArray(ULInt* length = nullptr) const
			{
				T* array = new T[this->length];

				for (ULInt i = 0; i < this->length; i++)
					array[i] = items[i];

				if (length)
					*length = this->length;

				return array;
			}
		public:
			void operator=(const DynamicArray<T>& elements)
			{
				delete[] this->items;

				items = new T[elements.length];

				this->length = elements.length;

				for (ULInt i = 0; i < this->length; i++)
					items[i] = elements[i];
			}

			bool operator==(const DynamicArray<T>& elements) const
			{
				if (elements.length != this->length)
					return false;

				for (ULInt i = 0; i < this->length; i++)
				{
					if (items[i] != elements[i])
						return false;
				}

				return true;
			}

			bool operator==(const T& element) const
			{
				return Exist(element);
			}

			bool operator!=(const DynamicArray<T>& elements) const
			{
				if (elements.length != this->length)
					return true;

				for (ULInt i = 0; i < this->length; i++)
				{
					if (items[i] != elements[i])
						return true;
				}

				return false;
			}

			bool operator!=(const T& element) const
			{
				return (!Exist(element));
			}

			void operator+=(const DynamicArray<T>& elements)
			{
				AddCollection(elements);
			}

			void operator+=(const T& element)
			{
				Add(element);
			}

			void operator-=(const DynamicArray<T>& elements)
			{
				RemoveCollection(elements);
			}

			void operator-=(const T& element)
			{
				Remove(element);
			}

			virtual T& operator[](const ULInt& index) const override
			{
				return items[index];
			}
		};

		template<typename T>
		struct Iterator<T, DynamicArrayIterator>
		{
		private:
			T* ptr;
		public:
			Iterator(T* ptr)
				: ptr(ptr)
			{
			}
		public:
			T& operator*()
			{
				return *ptr;
			}

			Iterator& operator--(int)
			{
				ptr--;
				return *this;
			}

			Iterator& operator--()
			{
				ptr--;
				return *this;
			}

			Iterator& operator++(int)
			{
				ptr++;
				return *this;
			}

			Iterator& operator++()
			{
				ptr++;
				return *this;
			}

			Iterator& operator-=(const ULInt& offset)
			{
				ptr -= offset;
				return *this;
			}

			Iterator& operator+=(const ULInt& offset)
			{
				ptr += offset;
				return *this;
			}

			Iterator& operator*=(const ULInt& offset)
			{
				ptr *= offset;
				return *this;
			}

			Iterator& operator/=(const ULInt& offset)
			{
				if (!offset)
					throw "Can't devide by 0";

				ptr /= offset;
				return *this;
			}

			bool operator==(const Iterator& other) const
			{
				return ptr == other.ptr;
			}

			bool operator!=(const Iterator& other) const
			{
				return !(*this == other);
			}
		};
	}
}