#include "Timer.h"

#include <thread>
#include <chrono>

namespace Bear
{
	static void TimerFunction(const ULInt time, const bool* stop, void(*callbackFunction)(), const Timer::Duration duration)
	{
		while (!(*stop))
		{
			switch (duration)
			{
				case Timer::Duration::Nanoseconds:
				{
					std::this_thread::sleep_for((std::chrono::nanoseconds)time);
					break;
				}
				case Timer::Duration::Microseconds:
				{
					std::this_thread::sleep_for((std::chrono::microseconds)time);
					break;
				}
				case Timer::Duration::Milliseconds:
				{
					std::this_thread::sleep_for((std::chrono::milliseconds)time);
					break;
				}
				case Timer::Duration::Seconds:
				{
					std::this_thread::sleep_for((std::chrono::seconds)time);
					break;
				}
				case Timer::Duration::Minutes:
				{
					std::this_thread::sleep_for((std::chrono::minutes)time);
					break;
				}
				case Timer::Duration::Hours:
				{
					std::this_thread::sleep_for((std::chrono::hours)time);
					break;
				}
				default:
					break;
			}

			callbackFunction();
		}
	}

	Timer::Timer()
		: stop(nullptr), thread(nullptr), start(new std::chrono::steady_clock::time_point(std::chrono::high_resolution_clock::now()))
	{
	}

	Timer::Timer(const ULInt& time, void(*callback)(), const Duration& duration)
		: stop(new bool(false)), thread(new std::thread(TimerFunction, time, stop, callback, duration)), start(new std::chrono::steady_clock::time_point(std::chrono::high_resolution_clock::now()))
	{
	}

	Timer::~Timer()
	{
		if (thread)
		{
			if (((std::thread*)thread)->joinable())
			{
				((std::thread*)thread)->join();
				delete thread;
				delete stop;
			}
		}

		delete start;
	}

	void Timer::Reset()
	{
		*(std::chrono::steady_clock::time_point*)start = std::chrono::high_resolution_clock::now();
	}

	void Timer::Stop() const
	{
		if(stop)
			*stop = true;
	}

	ULInt Timer::GetTime(const Duration& duration) const
	{
		auto&& diffrence = std::chrono::high_resolution_clock::now() - *(std::chrono::steady_clock::time_point*)start;

		switch (duration)
		{
			case Timer::Duration::Nanoseconds:
				return (std::chrono::duration_cast<std::chrono::nanoseconds>(diffrence)).count();
			case Timer::Duration::Microseconds:
				return (std::chrono::duration_cast<std::chrono::microseconds>(diffrence)).count();
			case Timer::Duration::Milliseconds:
				return (std::chrono::duration_cast<std::chrono::milliseconds>(diffrence)).count();
			case Timer::Duration::Seconds:
				return (std::chrono::duration_cast<std::chrono::seconds>(diffrence)).count();
			case Timer::Duration::Minutes:
				return (std::chrono::duration_cast<std::chrono::minutes>(diffrence)).count();
			case Timer::Duration::Hours:
				return (std::chrono::duration_cast<std::chrono::hours>(diffrence)).count();
			default:
				break;
		}
	}
}