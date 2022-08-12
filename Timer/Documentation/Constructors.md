//////////////////////////////////////////without arguments//////////////////////////////////////////////////////

Timer()

Example:

```C++
Bear::Timer timer;
```

//////////////////////////////////////////with arguments//////////////////////////////////////////////////////

Timer(const ULInt& time, void(*callback)(), const Duration& duration = Duration::Milliseconds);

time - time that "Callback" will call
callback - function which will be call then time = 0
duration - duration of time

Example:

```C++
void foo()
{
	system("cls");
	printf("E\n");
}

int main()
{
	Bear::Timer time(100, foo);
	
	for (size_t i = 0; i < 3500; i++)
		std::cout << "Hello World!\n";
	
	std::cout << "Time: " << time.GetTime() << "\n";
	
	time.Stop();
}
```