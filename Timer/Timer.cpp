#include "Timer.h"

#include <thread>
#include <chrono>
#include <mutex>

namespace Bear
{
	namespace Timer
	{
		std::mutex m;

		static void TimerFunction(const ULInt time, bool* stop, void(*callbackFunction)(), const Duration duration)
		{
			m.lock();
			{
				while (!(*stop))
				{
					m.unlock();
					
					switch (duration)
					{
						case Duration::Nanoseconds:
						{
							std::this_thread::sleep_for((std::chrono::nanoseconds)time);
							break;
						}
						case Duration::Microseconds:
						{
							std::this_thread::sleep_for((std::chrono::microseconds)time);
							break;
						}
						case Duration::Milliseconds:
						{
							std::this_thread::sleep_for((std::chrono::milliseconds)time);
							break;
						}
						case Duration::Seconds:
						{
							std::this_thread::sleep_for((std::chrono::seconds)time);
							break;
						}
						case Duration::Minutes:
						{
							std::this_thread::sleep_for((std::chrono::minutes)time);
							break;
						}
						case Duration::Hours:
						{
							std::this_thread::sleep_for((std::chrono::hours)time);
							break;
						}
						default:
							break;
					}

					callbackFunction();

					m.lock();
				}
			}
			m.unlock();
		}

		Timer::Timer()
			: stop(true), thread(nullptr), start(new std::chrono::steady_clock::time_point(std::chrono::high_resolution_clock::now()))
		{
		}

		Timer::Timer(const ULInt& time, void(*callback)(), const Duration& duration)
			: stop(false), thread(new std::thread(TimerFunction, time, &stop, callback, duration)), start(new std::chrono::steady_clock::time_point(std::chrono::high_resolution_clock::now()))
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
				}
			}

			delete start;
		}

		void Timer::Reset()
		{
			*(std::chrono::steady_clock::time_point*)start = std::chrono::high_resolution_clock::now();
		}

		void Timer::Stop()
		{
			m.lock();
			{
				stop = true;
			}
			m.unlock();
		}

		ULInt Timer::GetTime(const Duration& duration) const
		{
			auto&& diffrence = std::chrono::high_resolution_clock::now() - *(std::chrono::steady_clock::time_point*)start;

			switch (duration)
			{
				case Duration::Nanoseconds:
					return (std::chrono::duration_cast<std::chrono::nanoseconds>(diffrence)).count();
				case Duration::Microseconds:
					return (std::chrono::duration_cast<std::chrono::microseconds>(diffrence)).count();
				case Duration::Milliseconds:
					return (std::chrono::duration_cast<std::chrono::milliseconds>(diffrence)).count();
				case Duration::Seconds:
					return (std::chrono::duration_cast<std::chrono::seconds>(diffrence)).count();
				case Duration::Minutes:
					return (std::chrono::duration_cast<std::chrono::minutes>(diffrence)).count();
				case Duration::Hours:
					return (std::chrono::duration_cast<std::chrono::hours>(diffrence)).count();
				default:
					break;
			}
		}
	}
}