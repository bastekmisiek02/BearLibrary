"AddCollection" - add elements to DynamicArray

//////////////////////////////////////////DynamicArray/////////////////////////////////////////////////////////////

AddCollection(const DynamicArray<T>& Elements)

Elements - other DynamicArray<T> from which copy data to this DynamicArray

Example:

```C++
DynamicArray<float> firstArray(3);
firstArray[0] = 1.0f;
firstArray[1] = 1000.0f;
firstArray[2] = 20.0f;

DynamicArray<float> array;

array.AddCollection(firstArray);
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////