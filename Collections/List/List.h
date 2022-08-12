#pragma once

#include "../Base.h"

namespace Bear
{
	namespace Collections
	{
		struct ListIterator
		{
		};

		template<typename T>
		class List : public Base<T>
		{
		private:
			using Iterator = Iterator<T, ListIterator>;
			friend Iterator;
		private:
			struct ListElement
			{
				T element;

				ListElement* next;
				ListElement* previous;

				ListElement()
					: next(nullptr), previous(nullptr), element()
				{
				}

				~ListElement()
				{
					next = nullptr;

					previous = nullptr;
				}
			};
		private:
			ListElement* firstElement;
			ListElement* lastElement;
		public:
			List()
				: firstElement(nullptr), lastElement(nullptr)
			{
			}

			List(const std::initializer_list<T>& list)
				: firstElement(nullptr), lastElement(nullptr)
			{
				for (const auto& element : list)
					Add(element);
			}

			List(const List<T>& elements)
				: firstElement(nullptr), lastElement(nullptr)
			{
				for (const auto& element : elements)
					Add(element);
			}

			~List()
			{
				Clear();
			}
		public:
			Iterator begin()
			{
				return Iterator(firstElement);
			}

			Iterator end()
			{
				return Iterator(nullptr);
			}

			const Iterator begin() const
			{
				return Iterator(firstElement);
			}

			const Iterator end() const
			{
				return Iterator(nullptr);
			}
		public:
			void Add(const T& element)
			{
				if(firstElement)
				{
					lastElement->next = new ListElement();
					lastElement->next->previous = lastElement;

					lastElement = lastElement->next;
					lastElement->element = element;
					lastElement->next = nullptr;
				}
				else
				{
					firstElement = new ListElement();
					firstElement->element = element;
					firstElement->next = nullptr;
					firstElement->previous = nullptr;

					lastElement = firstElement;
				}

				this->length++;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, (void*)&element, TypeOfCallback::Add);
			}

			void AddCollection(const List<T>& elements)
			{
				for (const auto& item : elements)
					Add(item);
			}

			template<typename Collection>
			void AddCollection(const Collection& colection)
			{
				for (auto& element : colection)
					Add(element);
			}

			template<bool RemoveAll = false>
			void Remove(const T& element)
			{
				if (!this->length)
					return;

				if (this->length == 1)
				{
					delete firstElement;
					firstElement = nullptr;
					lastElement = nullptr;

					this->length = 0;

					return;
				}

				ListElement* it = firstElement;
				bool removed = false;
				ULInt removeCount = 1;

				if constexpr(!RemoveAll)
				{
					if (it->element == element)
					{
						firstElement = it->next;
						firstElement->previous = nullptr;
						delete it;

						removed = true;
					}
					else
					{
						while (it)
						{
							if (it->element == element)
							{
								if (it == lastElement)
								{
									lastElement = it->previous;
									lastElement->next = nullptr;

									delete it;

									removed = true;

									break;
								}

								it->previous->next = it->next;
								it->next->previous = it->previous;

								delete it;

								removed = true;

								break;
							}

							it = it->next;
						}
					}
				}
				else
				{
					while (it)
					{
						bool next = true;

						if (it->element == element)
						{
							if (it == firstElement)
							{
								firstElement = it->next;
								firstElement->previous = nullptr;
								delete it;

								it = firstElement;
							}
							else if (it == lastElement)
							{
								lastElement = it->previous;
								lastElement->next = nullptr;
								delete it;

								it = nullptr;
							}
							else
							{
								ListElement* next = it->next;
								ListElement* previous = it->previous;

								delete it;
								it = next;

								next->previous = previous;
								previous->next = next;
							}

							next = false;
							removed = true;
							removeCount++;
						}

						if(next)
							it = it->next;
					}
				}

				if (removed)
				{
					this->length -= removeCount;

					if(this->onCollectionLengthChanged)
						this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Remove);
				}
			}

			void RemoveOnIndex(const ULInt& index)
			{
				if (!this->length)
					return;

				if (index >= this->length)
					throw CollectionExceptions::OutOfRange;

				ListElement* it = firstElement;

				ULInt i = 0;

				if (index == 0)
				{
					firstElement = it->next;
					firstElement->previous = nullptr;
					delete it;

					it = nullptr;
				}
				else if (index == (this->length - 1))
				{
					it = lastElement;

					lastElement = it->previous;
					lastElement->next = nullptr;

					delete it;

					it = nullptr;
				}

				while (it)
				{
					if (i == index)
					{
						it->previous->next = it->next;
						it->next->previous = it->previous;

						delete it;

						break;
					}

					it = it->next;
					i++;
				}

				this->length--;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Remove);
			}

			template<bool RemoveAll = false>
			void RemoveCollection(const List<T>& elements)
			{
				if (!elements.length)
					return;

				ListElement* it = nullptr;

				if constexpr(!RemoveAll)
				{
					it = elements.firstElement;

					while (it)
					{
						Remove(it->element);

						it = it->next;
					}
				}
				else
				{
					it = firstElement;

					while (it)
					{
						bool removed = false;

						for (ListElement* index = elements.firstElement; index != elements.end(); index = index->next)
						{
							if (it->element == index->element)
							{
								ListElement* deleteItem = it;

								if (it != firstElement)
								{
									it->previous->next = it->next;

									if (it != lastElement)
										it->next->previous = it->previous;
									else
										lastElement = it->previous;

									it = it->next;
								}
								else
								{
									if (this->length > 1)
									{
										it->next->previous = nullptr;

										firstElement = it->next;
									}
									else
									{
										firstElement = nullptr;
										lastElement = nullptr;
									}

									it = firstElement;
								}

								delete deleteItem;

								this->length--;

								removed = true;

								break;
							}
						}

						if (!removed)
							it = it->next;
					}
				}
			}

			template<bool RemoveAll = false>
			void RemoveCollection(const Base<T>* elements)
			{
				//TODO: Dokoñczyæ
			}

			virtual void Clear() override
			{
				while (this->length)
				{
					ListElement* it = lastElement->previous;

					delete lastElement;

					lastElement = it;

					this->length--;
				}

				firstElement = nullptr;

				if (this->onCollectionLengthChanged)
					this->onCollectionLengthChanged(this, nullptr, TypeOfCallback::Destroy);
			}

			void Sort(const bool (*SortFunc)(const T& firstElement, const T& secondElement)) const
			{
				if (!this->length)
					throw CollectionExceptions::CollectionClear;

				if (this->length == 1)
					return;

				ListElement* first = firstElement;
				ListElement* second = first->next;

				ULInt i = 0;

				ListElement* lastElement = nullptr;

				while (first && second)
				{
					for (ULInt j = 0; j < i; j++)
					{
						if (!SortFunc(first->element, second->element))
						{
							const T helpItem = first->element;
							first->element = second->element;
							second->element = helpItem;

							if(!lastElement)
								lastElement = first;

							first = first->previous;
							second = second->previous;
						}
						else
							break;
					}

					if (lastElement)
					{
						first = lastElement;
						second = first->next;

						lastElement = nullptr;
					}

					first = first->next;
					second = second->next;

					i++;
				}
			}

			const bool Exist(const T& element, ULInt* index = nullptr) const
			{
				ListElement* it = firstElement;
				ULInt i = 0;

				while (it)
				{
					if (it->element == element)
					{
						if (index)
							*index = i;

						return true;
					}

					it = it->next;
					i++;
				}

				return false;
			}
		public:
			T& operator[](const ULInt& index) const override
			{
				ListElement* it = firstElement;

				ULInt i = 0;

				while (it)
				{
					if (i == index)
						return it->element;

					i++;
					it = it->next;
				}

				throw CollectionExceptions::OutOfRange;
			}
		};

		template<typename T>
		struct Iterator<T, ListIterator>
		{
		private:
			List<T>::ListElement* value;
		public:
			Iterator(List<T>::ListElement* value)
				: value(value)
			{
			}
		public:
			T& operator*()
			{
				return value->element;
			}

			const T& operator*() const
			{
				return value->element;
			}

			Iterator& operator--()
			{
				value = value->previous;
				return *this;
			}

			Iterator& operator++()
			{
				value = value->next;
				return *this;
			}

			Iterator& operator-=(const ULInt& offset)
			{
				for (ULInt i = 0; i < offset; i++)
					value = value->previous;

				return *this;
			}

			Iterator& operator+=(const ULInt& offset)
			{
				for (ULInt i = 0; i < offset; i++)
					value = value->next;

				return *this;
			}

			bool operator==(const Iterator& other)
			{
				return this->value == other.value;
			}

			const bool operator==(const Iterator& other) const
			{
				return this->value == other.value;
			}

			bool operator!=(const Iterator& other)
			{
				return !(*this == other);
			}

			const bool operator!=(const Iterator& other) const
			{
				return !(*this == other);
			}
		};
	}
}