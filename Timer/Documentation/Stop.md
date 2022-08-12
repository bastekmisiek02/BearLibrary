void Stop() const

This function stop the callback if you created by given time

Example:

```C++
void foo()
{
	system("cls");
	printf("foo\n");
}

int main()
{
	Bear::Timer time(100, foo);

	for (size_t i = 0; i < 3500; i++)
		std::cout << "Hello World!\n";
	
	time.Stop();
}
```