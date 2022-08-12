const float GetTime() const

Returns the time since the object was created

Example:

```C++
int main()
{
	Bear::Timer time;

	std::cout << "Hello World!\n";

	std::cout << "Time: " << time.GetTime() << "\n";
}
```