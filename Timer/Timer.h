#pragma once

#include "Bases.h"

namespace Bear
{
	namespace Timer
	{
		enum class Duration
		{
			Nanoseconds,
			Microseconds,
			Milliseconds,
			Seconds,
			Minutes,
			Hours
		};

		class Timer
		{
		private:
			void* start;

			bool* stop;
			void* thread;
		public:
			Timer();
			Timer(const Timer& timer) = delete;
			Timer(const Timer&& timer) = delete;
			Timer(const ULInt& time, void(*callback)(), const Duration& duration = Duration::Milliseconds);
			~Timer();
		public:
			void Reset();
		public:
			void Stop() const;

			ULInt GetTime(const Duration& duration = Duration::Milliseconds) const;
		};
	}
}