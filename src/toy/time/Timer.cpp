#include <cstdint>
#include "toy/time/Timer.hpp"

#if defined(TOY_WINDOWS)
	#include "toy/Oops.hpp"
	#include "toy/Windows.hpp"
#elif defined(TOY_MAC)
	#include <mach/mach_time.h>
#else
	#include <sys/time.h>
#endif

namespace toy{
namespace time{

struct TimerPrivate
{
	#if defined(TOY_WINDOWS)
		int64_t   timerStart = 0;  // LARGE_INTEGER is 64bit signed integer.
	#else
		// For Linux and Mac
		uint64_t  timerStart = 0;
	#endif
};

#if defined(TOY_WINDOWS)

class TimerFrequency
{
	public:

		TimerFrequency()
		{
			int64_t     frequency;

			if ( ! QueryPerformanceFrequency( (LARGE_INTEGER*)(&frequency) ) )
			{
				// QueryPerformanceCounter doesn't work.
				toy::Oops(TOY_MARK);
				return;
			}

			_frequency = ( float )( double(1)/double(frequency) );
		}

		~TimerFrequency(){}

		auto data() const ->float
		{
			return _frequency;
		}

	private:

		float _frequency = float(0);
};

#elif defined(TOY_MAC)

class TimerFrequency
{
	public:

		TimerFrequency()
		{
			mach_timebase_info(&_frequency);
		}

		~TimerFrequency(){}

		auto data() const ->const mach_timebase_info_data_t*
		{
			return &_frequency;
		}

	private:

		mach_timebase_info_data_t _frequency = {0, 0};
};

#endif

#if defined(TOY_WINDOWS) || defined(TOY_MAC)

static auto GetFrequency()->const TimerFrequency*
{
	static TimerFrequency frequency;
	return &frequency;
}

#endif

}}

using namespace toy;
using namespace time;

#if defined(TOY_WINDOWS)

static inline int64_t GetSystemCurrentTime()
{
	int64_t    result;

	QueryPerformanceCounter( (LARGE_INTEGER*)(&result) );

	return result;
}

static inline float RawTimeDataToSeconds(uint64_t raw)
{
	return ((float)raw) * ::toy::time::GetFrequency()->data();
}

#elif defined(TOY_MAC)

static inline uint64_t GetSystemCurrentTime()
{
	return mach_absolute_time();
}

static inline float RawTimeDataToSeconds(uint64_t raw)
{
	double result = double(raw) * double(::toy::time::GetFrequency()->data()->numer)
		/ double(::toy::time::GetFrequency()->data()->denom) / double(1000000);

	return result;
}

#else

// Power by <sys/time.h>
static inline uint64_t GetSystemCurrentTime()
{
	struct ::timeval   timenow;

	::gettimeofday(&timenow,nullptr);

	return (static_cast<uint64_t>(timenow.tv_sec) * uint64_t(1000000)) + static_cast<uint64_t>(timenow.tv_usec);
}

// Power by <time.h>
/*
static inline uint64_t GetSystemCurrentTime()
{
	struct ::timespec  timenow;
    ::clock_gettime(CLOCK_MONOTONIC, &timenow);

	return (static_cast<uint64_t>(timenow.tv_sec) * uint64_t(1000000)) + ( static_cast<uint64_t>(timenow.tv_nsec) / uint64_t(1000));
}
*/

static inline float RawTimeDataToSeconds(uint64_t raw)
{
	return double(raw) / double(1000000);
}

#endif

Timer::Timer():_this(new TimerPrivate)
{
	;
}

Timer::~Timer()
{
	;
}

float Timer::restart()
{
	auto  oldTimerStart = _this->timerStart;

	return RawTimeDataToSeconds((_this->timerStart = GetSystemCurrentTime()) - oldTimerStart);
}

float Timer::elapsed() const
{
	return RawTimeDataToSeconds(GetSystemCurrentTime() - (_this->timerStart));
}

void Timer::restart(Timer::RawType *num)
{
	auto  oldTimerStart = _this->timerStart;

	*num = (_this->timerStart = GetSystemCurrentTime()) - oldTimerStart;
}

void Timer::elapsed(Timer::RawType *num) const
{
	*num = GetSystemCurrentTime() - (_this->timerStart);
}

float Timer::ToSeconds(const Timer::RawType &num)
{
	return RawTimeDataToSeconds(num);
}
