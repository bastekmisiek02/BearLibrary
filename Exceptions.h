#pragma once

namespace Bear
{
	enum class CollectionExceptions : char
	{
		/// <summary>
		/// It's throwing when start index is greater than last index
		/// </summary>
		StartIndexGreaterThanEnd = 0,
		/// <summary>
		/// It's throwing when index is greater than this->count
		/// </summary>
		OutOfRange = 1,
		/// <summary>
		/// It's throwing when index is lower than 0
		/// </summary>
		IndexLower = 2,
		/// <summary>
		/// It's throwing when dynamic array is clear
		/// </summary>
		CollectionClear = 3
	};
}