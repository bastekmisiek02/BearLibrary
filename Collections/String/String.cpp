#include "String.h"

#include "Math/Math/Math.h"

namespace Bear
{
	namespace Collections
	{
		Iterator<char, StringIterator>::Iterator(char* ptr)
			: ptr(ptr)
		{
		}

		char& Iterator<char, StringIterator>::operator*()
		{
			return *ptr;
		}
		
		const char& Iterator<char, StringIterator>::operator*() const
		{
			return *ptr;
		}
		
		Iterator<char, StringIterator>& Iterator<char, StringIterator>::operator--()
		{
			ptr--;
			return *this;
		}
								   
		Iterator<char, StringIterator>& Iterator<char, StringIterator>::operator++()
		{
			ptr++;
			return *this;
		}
		
		Iterator<char, StringIterator>& Iterator<char, StringIterator>::operator-=(const ULInt& offset)
		{
			ptr -= offset;
			return *this;
		}
		
		Iterator<char, StringIterator>& Iterator<char, StringIterator>::operator+=(const ULInt& offset)
		{
			ptr += offset;
			return *this;
		}
		
		bool Iterator<char, StringIterator>::operator==(const Iterator<char, StringIterator>& other)
		{
			return ptr == other.ptr;
		}
		
		const bool Iterator<char, StringIterator>::operator==(const Iterator<char, StringIterator>& other) const
		{
			return ptr == other.ptr;
		}
		
		bool Iterator<char, StringIterator>::operator!=(const Iterator<char, StringIterator>& other)
		{
			return !(*this == other);
		}
		
		const bool Iterator<char, StringIterator>::operator!=(const Iterator<char, StringIterator>& other) const
		{
			return !(*this == other);
		}

		void String::Copy(char* src)
		{
			if (src == nullptr)
				return;

			delete[] strHeap;
			strHeap = nullptr;
			this->length = 0;

			for (ULInt i = 0; ; i++)
			{
				if (src[i] == '\0')
				{
					this->length = i;

					if (i > BEAR_STRING_SIZE)
					{
						strHeap = new char[this->length + 1];
						{
							for (ULInt j = 0; j < this->length; j++)
								strHeap[j] = src[j];
						}
						strHeap[this->length] = '\0';

						str = strHeap;
					}
					else
					{
						for (ULInt j = 0; j < this->length; j++)
							strStack[j] = src[j];

						strStack[this->length] = '\0';

						str = strStack;
					}

					return;
				}
			}
		}

		String::String()
			: strHeap(nullptr), strStack(), str(strStack)
		{
		}

		String::String(const char* src)
			: strHeap(nullptr), strStack(), str(strStack)
		{
			Copy((char*)src);
		}

		String::String(char* src)
			: strHeap(nullptr), strStack(), str(strStack)
		{
			Copy(src);
		}

		String::String(const String& other)
			: strHeap(nullptr), strStack(), str(strStack)
		{
			this->length = other.length;
			
			if (other.str == nullptr)
				return;
		
			if (other.length > BEAR_STRING_SIZE)
			{
				str = new char[length + 1];

				for (ULInt i = 0; i < length; i++)
					str[i] = other.str[i];

				str[length] = '\0';

				strHeap = str;
			}
			else
			{
				for (ULInt i = 0; i < length; i++)
					strStack[i] = other.str[i];

				strStack[length] = '0';

				str = strStack;
			}
		}

		String::~String()
		{
			Clear();
		}

		String::Iterator String::begin()
		{
			return String::Iterator(str);
		}

		String::Iterator String::end()
		{
			return String::Iterator(str + this->length);
		}

		const String::Iterator String::begin() const
		{
			return String::Iterator(str);
		}

		const String::Iterator String::end() const
		{
			return String::Iterator(str + this->length);
		}

		const LInt String::ToInt() const
		{
			if (!length)
				return 0;

			LInt value = 0;

			bool isSigned = false;
			bool broke = false;
			ULInt lastValue = 0;

			if (str[0] == '-')
				isSigned = true;

			for (ULInt i = isSigned; i < length; i++)
			{
				if (!(str[i] >= '0' && str[i] <= '9'))
				{
					broke = true;
					break;
				}

				lastValue = (Math::Pow<ULInt>(10, length - i - 1));
				value += lastValue * (str[i] - '0');
			}

			if (broke && lastValue)
				value /= lastValue;

			if (isSigned)
				value *= (-1);

			return value;
		}

		const ULInt String::ToUInt() const
		{
			if (!length)
				return 0;

			ULInt value = 0;

			bool broke = false;
			ULInt lastValue = 0;

			for (ULInt i = 0; i < length; i++)
			{
				if (!(str[i] >= '0' && str[i] <= '9'))
				{
					broke = true;
					break;
				}

				lastValue = (Math::Pow<ULInt>(10, length - i - 1));
				value += lastValue * (str[i] - '0');
			}

			if (broke && lastValue)
				value /= lastValue;

			return value;
		}

		const float String::ToFloat() const
		{
			return (float)ToDouble();
		}

		const double String::ToDouble() const
		{
			if (!length)
				return 0;

			double returnValue = 0;
			LInt i = 0;

			if (str[0] == '-' && str[1] == '.')
				i = 1;

			for (; ; i++)
			{
				if (str[i] == '.' || str[i] == '\0')
				{
					for (LInt j = i; j > 0; j--)
					{
						if (str[j - 1] != '-')
							returnValue += ((Math::Pow<LInt>(10, Math::Abs<LInt>(j - i))) * (str[j - 1] - '0'));
					}

					break;
				}
			}

			if (str[i] != '\0')
			{
				for (LInt j = i + 1; ; j++)
				{
					if (str[j] == '\0')
						break;

					returnValue += (Math::Pow<double>(0.1, j - i) * (str[j] - '0'));
				}
			}

			if (str[0] == '-')
				returnValue = -returnValue;

			return returnValue;
		}

		const char* const String::ToCharPtr() const
		{
			return str;
		}

		void String::Clear()
		{
			delete[] strHeap;
			strHeap = nullptr;
			str = nullptr;

			strStack[0] = '\0';
			length = 0;

			if (onCollectionLengthChanged)
				onCollectionLengthChanged(this, nullptr, TypeOfCallback::Destroy);
		}

		const bool String::Exist(const char& element, ULInt* index) const
		{
			for (ULInt i = 0; i < this->length; i++)
			{
				if (str[i] == element)
				{
					if (index)
						*index = i;

					return true;
				}
			}

			return false;
		}

		void String::Add(const char& element)
		{
			operator+=(element);
		}

		bool String::operator==(const String& other) const
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

		bool String::operator!=(const String& other) const
		{
			if (other.length != length)
				return true;

			for (ULInt i = 0; i < length; i++)
			{
				if (str[i] != other.str[i])
					return true;
			}

			return false;
		}

		void String::operator+=(const char& other)
		{
			if ((this->length + 1) <= BEAR_STRING_SIZE)
			{
				strStack[length] = other;
				strStack[length + 1] = '\0';
			}
			else
			{
				char* newString = new char[length + 2];
				{
					for (ULInt i = 0; i < length; i++)
						newString[i] = str[i];

					newString[length] = other;
					newString[length + 1] = '\0';

					delete[] strHeap;
				}

				strHeap = newString;

				str = strHeap;
			}

			length++;

			if (onCollectionLengthChanged)
				onCollectionLengthChanged(this, (void*)&other, TypeOfCallback::Add);
		}

		void String::operator+=(char* other)
		{
			operator+=((const char*)other);
		}

		void String::operator+=(const char* other)
		{
			ULInt addedLength = 0;

			for (ULInt i = 0; ; i++)
			{
				if (other[i] == '\0')
				{
					if (!i)
						return;

					addedLength = i;

					break;
				}
			}

			if (length + addedLength > BEAR_STRING_SIZE)
			{
				char* newStr = new char[addedLength + length + 1];
				{
					for (ULInt i = 0; i < length; i++)
						newStr[i] = str[i];

					for (ULInt i = 0; i < addedLength; i++)
						newStr[i + length] = other[i];
				}
				delete[] strHeap;

				strHeap = newStr;
				str = strHeap;

				length += addedLength;
			}
			else
			{
				for (ULInt i = 0; i < addedLength; i++)
				{
					strStack[length] = other[i];
					length++;
				}
			}

			str[length] = '\0';

			if (onCollectionLengthChanged)
				onCollectionLengthChanged(this, (void*)other, TypeOfCallback::Add);
		}

		void String::operator+=(const String& other)
		{
			//Tu teraz
			ULInt newLength = length + other.length;

			char* newString = new char[newLength + 1];
			{
				for (ULInt i = 0; i < newLength; i++)
				{
					if (i >= length)
					{
						for (ULInt j = 0; j < other.length; j++)
							newString[i + j] = other.str[j];

						break;
					}

					newString[i] = str[i];
				}

				length = newLength;

				newString[length] = '\0';

				delete[] str;
			}
			str = newString;

			if (onCollectionLengthChanged)
				onCollectionLengthChanged(this, (void*)&other, TypeOfCallback::Add);
		}

		String String::operator+(const char& other)
		{
			String value(*this);

			value += other;

			return value;
		}

		String String::operator+(char* other)
		{
			String value(*this);

			value += other;

			return value;
		}

		String String::operator+(const char* other)
		{
			String value(*this);

			value += other;

			return value;
		}

		String String::operator+(const String& other)
		{
			String value(*this);

			value += other;

			return value;
		}

		char& String::operator[](const ULInt& index) const
		{
			return str[index];
		}

		ULInt String::GetLength(char* src)
		{
			if (src == nullptr || src[0] == '\0')
				return 0;

			for (ULInt i = 1; ; i += 2)
			{
				if (src[i - 1] == '\0')
					return i - 1;

				if (src[i] == '\0')
					return i;
			}
		}

		ULInt String::GetLength(const char* src)
		{
			return GetLength((char*)src);
		}

		void String::Copy(const char* src, char* dst)
		{
			for (ULInt i = 0; ; i++)
			{
				if (src[i] == '\0')
				{
					dst[i] = '\0';
					break;
				}

				dst[i] = src[i];
			}
		}

		bool String::Compare(char* first, char* second)
		{
			ULInt i = 0;

			while (true)
			{
				if (first[i] == '\0' || second[i] == '\0')
				{
					if (first[i] == second[i])
						return true;

					return false;
				}

				if (first[i] != second[i])
					return false;

				i++;
			}
		}

		bool String::Compare(const char* first, char* second)
		{
			return Compare((char*)first, (char*)second);
		}

		bool String::Compare(char* first, const char* second)
		{
			return Compare((char*)first, (char*)second);
		}

		bool String::Compare(const char* first, const char* second)
		{
			return Compare((char*)first, (char*)second);
		}

		/*ToString*/

		/*char*/
		template<>
		String String::ToString(const char& value)
		{
			typedef char Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2]{ '0','\0' };
				returnValue.length = 1;

				return returnValue;
			}

			char* ptr = nullptr;

			if (value > 0)
			{
				returnValue.str = new char[4];
				ptr = returnValue.str;
			}
			else
			{
				returnValue.str = new char[5];
				returnValue.str[0] = '-';
				returnValue.length++;
				ptr = &returnValue.str[1];
			}

			Type tmp = Math::Abs<Type>(value);
			Type multiplier = 100;
			Type result = tmp / multiplier;
			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			multiplier = 10;

			result = tmp / multiplier;

			if (result || pass)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;
				tmp -= (result * multiplier);
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;

			*ptr = '\0';

			return returnValue;
		}

		/*UChar*/
		template<>
		String String::ToString(const UChar& value)
		{
			typedef UChar Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2]{ '0','\0' };
				returnValue.length = 1;

				return returnValue;
			}

			returnValue.str = new char[4];
			char* ptr = returnValue.str;

			Type tmp = value;
			Type multiplier = 100;
			Type result = tmp / multiplier;
			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			multiplier = 10;

			result = tmp / multiplier;

			if (result || pass)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;
				tmp -= (result * multiplier);
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;

			*ptr = '\0';

			return returnValue;
		}

		/*SInt*/
		template<>
		String String::ToString(const SInt& value)
		{
			typedef SInt Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2]{ '0', '\0' };
				returnValue.length = 1;

				return returnValue;
			}

			char* ptr = nullptr;

			if (value > 0)
			{
				returnValue.str = new char[6];
				ptr = returnValue.str;
			}
			else
			{
				returnValue.str = new char[7];
				returnValue.str[0] = '-';
				returnValue.length++;
				ptr = &returnValue.str[1];
			}

			Type tmp = Math::Abs<Type>(value);
			Type multiplier = 10000;
			Type result = tmp / multiplier;
			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			while (multiplier > 10)
			{
				multiplier /= 10;

				result = tmp / multiplier;

				if (result || pass)
				{
					*ptr = (result + '0');
					returnValue.length++;
					ptr++;
					tmp -= (result * multiplier);
					pass = true;
				}
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;

			*ptr = '\0';

			return returnValue;
		}

		/*USInt*/
		template<>
		String String::ToString(const USInt& value)
		{
			typedef USInt Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2]{ '0', '\0' };
				returnValue.length = 1;

				return returnValue;
			}

			returnValue.str = new char[6];

			char* ptr = returnValue.str;

			Type tmp = value;
			Type multiplier = 10000;
			Type result = tmp / multiplier;
			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			while (multiplier > 10)
			{
				multiplier /= 10;

				result = tmp / multiplier;

				if (result || pass)
				{
					*ptr = (result + '0');
					returnValue.length++;
					ptr++;
					tmp -= (result * multiplier);
					pass = true;
				}
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;

			*ptr = '\0';

			return returnValue;
		}

		/*int*/
		template<>
		String String::ToString(const int& value)
		{
			typedef int Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2]{ '0', '\0' };
				returnValue.length = 1;

				return returnValue;
			}

			char* ptr = nullptr;

			if (value > 0)
			{
				returnValue.str = new char[11];
				ptr = returnValue.str;
			}
			else
			{
				returnValue.str = new char[12];
				returnValue.str[0] = '-';
				returnValue.length++;
				ptr = &returnValue.str[1];
			}

			Type tmp = Math::Abs<Type>(value);
			Type multiplier = 1000000000;
			Type result = tmp / multiplier;
			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			while (multiplier > 10)
			{
				multiplier /= 10;

				result = tmp / multiplier;

				if (result || pass)
				{
					*ptr = (result + '0');
					returnValue.length++;
					ptr++;
					tmp -= (result * multiplier);
					pass = true;
				}
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;

			*ptr = '\0';

			return returnValue;
		}

		/*UInt*/
		template<>
		String String::ToString(const UInt& value)
		{
			typedef UInt Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2]{ '0', '\0' };
				returnValue.length = 1;

				return returnValue;
			}

			returnValue.str = new char[11];

			char* ptr = returnValue.str;

			Type tmp = value;
			Type multiplier = 1000000000;
			Type result = tmp / multiplier;
			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			while (multiplier > 10)
			{
				multiplier /= 10;

				result = tmp / multiplier;

				if (result || pass)
				{
					*ptr = (result + '0');
					returnValue.length++;
					ptr++;
					tmp -= (result * multiplier);
					pass = true;
				}
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;

			*ptr = '\0';

			return returnValue;
		}

		/*LInt*/
		template<>
		String String::ToString(const LInt& value)
		{
			typedef LInt Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2]{ '0', '\0' };
				returnValue.length = 1;

				return returnValue;
			}

			char* ptr = nullptr;

			if (value > 0)
			{
				returnValue.str = new char[20];
				ptr = returnValue.str;
			}
			else
			{
				returnValue.str = new char[21];
				returnValue.str[0] = '-';
				returnValue.length++;
				ptr = &returnValue.str[1];
			}

			Type tmp = Math::Abs<Type>(value);
			Type multiplier = 1000000000000000000;
			Type result = tmp / multiplier;
			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			while (multiplier > 10)
			{
				multiplier /= 10;

				result = tmp / multiplier;

				if (result || pass)
				{
					*ptr = (result + '0');
					returnValue.length++;
					ptr++;
					tmp -= (result * multiplier);
					pass = true;
				}
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;

			*ptr = '\0';

			return returnValue;
		}

		/*ULInt*/
		template<>
		String String::ToString(const ULInt& value)
		{
			typedef ULInt Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2]{ '0', '\0' };
				returnValue.length = 1;

				return returnValue;
			}

			returnValue.str = new char[21];

			char* ptr = returnValue.str;

			Type tmp = value;
			Type multiplier = 10000000000000000000;
			Type result = tmp / multiplier;
			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			while (multiplier > 10)
			{
				multiplier /= 10;

				result = tmp / multiplier;

				if (result || pass)
				{
					*ptr = (result + '0');
					returnValue.length++;
					ptr++;
					tmp -= (result * multiplier);
					pass = true;
				}
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;

			*ptr = '\0';

			return returnValue;
		}

		/*float*/
		template<>
		String String::ToString(const float& value)
		{
			typedef float Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2] { '0', '\0' };
				returnValue.length = 1;

				return returnValue;
			}

			char* ptr = nullptr;
			ULInt size = 86;

			if (value > 0)
			{
				returnValue.str = new char[size];
				ptr = returnValue.str;
			}
			else
			{
				returnValue.str = new char[size + 1];
				returnValue.str[0] = '-';
				returnValue.length++;
				ptr = &returnValue.str[1];
			}

			Type tmp = Math::Abs<Type>(value);
			Type multiplier = 1.0e+38f;
			ULInt result = tmp / multiplier;

			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			while (multiplier > 10)
			{
				multiplier /= 10;

				result = tmp / multiplier;

				if (result || pass)
				{
					*ptr = (result + '0');
					returnValue.length++;
					ptr++;
					tmp -= (result * multiplier);
					pass = true;
				}
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;
			
			tmp -= (ULInt)tmp;

			if (tmp == 0)
			{
				*ptr = '\0';
				return returnValue;
			}

			//float
			*ptr = '.';
			ptr++;
			returnValue.length++;

			char* last = nullptr;

			size += (ULInt)(returnValue.str - 1);

			while ((ULInt)ptr < size)
			{
				tmp *= 10.f;
				result = tmp;
				tmp -= result;

				if (!result)
				{
					if (!last)
						last = ptr;
				}
				else
					last = nullptr;

				*ptr = result + '0';
				ptr++;

				returnValue.length++;

				if (!tmp)
					break;
			}

			if (last)
			{
				returnValue.length += ptr - last;

				if (*(last - 1) == '.')
					ptr = last - 1;
				else
					ptr = last;
			}

			*ptr = '\0';

			return returnValue;
		}

		/*double*/
		template<>
		String String::ToString(const double& value)
		{
			typedef double Type;

			String returnValue;

			if (!value)
			{
				returnValue.str = new char[2] { '0', '\0' };
				returnValue.length = 1;

				return returnValue;
			}

			char* ptr = nullptr;
			ULInt size = 636;

			if (value > 0)
			{
				returnValue.str = new char[size];
				ptr = returnValue.str;
			}
			else
			{
				returnValue.str = new char[size + 1];
				returnValue.str[0] = '-';
				returnValue.length++;
				ptr = &returnValue.str[1];
			}

			Type tmp = Math::Abs<Type>(value);
			Type multiplier = 1.0e+308;
			ULInt result = tmp / multiplier;

			bool pass = false;

			if (result)
			{
				*ptr = (result + '0');
				returnValue.length++;
				ptr++;

				tmp -= (result * multiplier);
				pass = true;
			}

			while (multiplier > 10)
			{
				multiplier /= 10;

				result = tmp / multiplier;

				if (result || pass)
				{
					*ptr = (result + '0');
					returnValue.length++;
					ptr++;
					tmp -= (result * multiplier);
					pass = true;
				}
			}

			*ptr = tmp + '0';
			ptr++;
			returnValue.length++;

			tmp -= (ULInt)tmp;

			if (tmp == 0)
			{
				*ptr = '\0';
				return returnValue;
			}

			//float
			*ptr = '.';
			ptr++;
			returnValue.length++;

			char* last = nullptr;

			size += (ULInt)(returnValue.str - 1);

			while ((ULInt)ptr < size)
			{
				tmp *= 10.f;
				result = tmp;
				tmp -= result;

				if (!result)
				{
					if (!last)
						last = ptr;
				}
				else
					last = nullptr;

				*ptr = result + '0';
				ptr++;

				returnValue.length++;

				if (!tmp)
					break;
			}

			if (last)
			{
				returnValue.length += ptr - last;

				if (*(last - 1) == '.')
					ptr = last - 1;
				else
					ptr = last;
			}

			*ptr = '\0';

			return returnValue;
		}

		/*ConvertTo*/

		/*LInt*/
		template<>
		const LInt String::ConvertTo(char* value)
		{
			const ULInt length = GetLength(value);

			if (!length)
				return 0;

			LInt returnValue = 0;

			bool isSigned = false;
			bool broke = false;
			ULInt lastValue = 0;

			if (value[0] == '-')
				isSigned = true;

			for (ULInt i = isSigned; i < length; i++)
			{
				if (!(value[i] >= '0' && value[i] <= '9'))
				{
					broke = true;
					break;
				}

				lastValue = (Math::Pow<ULInt>(10, length - i - 1));
				returnValue += lastValue * (value[i] - '0');
			}

			if (broke && lastValue)
				returnValue /= lastValue;

			if (isSigned)
				returnValue *= (-1);

			return returnValue;
		}

		template<>
		const LInt String::ConvertTo(const char* value)
		{
			return ConvertTo<LInt>((char*)value);
		}

		/*ULInt*/
		template<>
		const ULInt String::ConvertTo(char* value)
		{
			const ULInt length = GetLength(value);

			if (!length)
				return 0;

			ULInt returnValue = 0;

			bool broke = false;
			ULInt lastValue = 0;

			for (ULInt i = 0; i < length; i++)
			{
				if (!(value[i] >= '0' && value[i] <= '9'))
				{
					broke = true;
					break;
				}

				lastValue = (Math::Pow<ULInt>(10, length - i - 1));
				returnValue += lastValue * (value[i] - '0');
			}

			if (broke && lastValue)
				returnValue /= lastValue;

			return returnValue;
		}

		template<>
		const ULInt String::ConvertTo(const char* value)
		{
			return ConvertTo<ULInt>((char*)value);
		}

		/*char*/
		template<>
		const char String::ConvertTo(char* value)
		{
			return (char)ConvertTo<LInt>(value);
		}

		template<>
		const char String::ConvertTo(const char* value)
		{
			return (char)ConvertTo<LInt>(value);
		}

		/*UChar*/
		template<>
		const UChar String::ConvertTo(char* value)
		{
			return (UChar)ConvertTo<ULInt>(value);
		}

		template<>
		const UChar String::ConvertTo(const char* value)
		{
			return (UChar)ConvertTo<ULInt>(value);
		}

		/*USInt*/
		template<>
		const USInt String::ConvertTo(char* value)
		{
			return (USInt)ConvertTo<ULInt>(value);
		}

		template<>
		const USInt String::ConvertTo(const char* value)
		{
			return (USInt)ConvertTo<ULInt>(value);
		}

		/*SInt*/
		template<>
		const SInt String::ConvertTo(char* value)
		{
			return (SInt)ConvertTo<LInt>(value);
		}

		template<>
		const SInt String::ConvertTo(const char* value)
		{
			return (SInt)ConvertTo<LInt>(value);
		}

		/*UInt*/
		template<>
		const UInt String::ConvertTo(char* value)
		{
			return (UInt)ConvertTo<ULInt>(value);
		}

		template<>
		const UInt String::ConvertTo(const char* value)
		{
			return (UInt)ConvertTo<ULInt>(value);
		}

		/*double*/
		template<>
		const double String::ConvertTo(char* value)
		{
			const ULInt length = GetLength(value);

			if (!length)
				return 0;

			double returnValue = 0;
			LInt i = 0;

			if (value[0] == '-' && value[1] == '.')
				i = 1;

			for (; ; i++)
			{
				if (value[i] == '.' || value[i] == '\0')
				{
					for (LInt j = i; j > 0; j--)
					{
						if (value[j - 1] != '-')
							returnValue += ((Math::Pow<LInt>(10, Math::Abs<LInt>(j - i))) * (value[j - 1] - '0'));
					}

					break;
				}
			}

			if (value[i] != '\0')
			{
				for (LInt j = i + 1; ; j++)
				{
					if (value[j] == '\0')
						break;

					returnValue += (Math::Pow<double>(0.1, j - i) * (value[j] - '0'));
				}
			}

			if (value[0] == '-')
				returnValue = -returnValue;

			return returnValue;
		}

		template<>
		const double String::ConvertTo(const char* value)
		{
			return ConvertTo<double>((char*)value);
		}

		/*float*/
		template<>
		const float String::ConvertTo(char* value)
		{
			return (float)ConvertTo<double>(value);
		}

		template<>
		const float String::ConvertTo(const char* value)
		{
			return (float)ConvertTo<double>(value);
		}
	}
}