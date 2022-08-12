"Swap" - swap elements

//////////////////////////////////////////DynamicArray/////////////////////////////////////////////////////////////

void Swap(DynamicArray<T>& elements)

elements - DynamicArray which will be swap elements

Example:

```C++
DynamicArray<int> array(4);
array[0] = 2;
array[1] = 3;
array[2] = 100;
array[3] = 10;

DynamicArray<int> secondArray(3);
secondArray[0] = 2;
secondArray[1] = 100;
secondArray[2] = 20;

array.Swap(secondArray);

for (const auto& item : array)
	std::cout << item << "\n";

std::cout << "---------------------------\n";

for (const auto& item : secondArray)
	std::cout << item << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////