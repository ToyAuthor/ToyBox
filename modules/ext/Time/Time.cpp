#include <luapp.hpp>
#include <toy/time/Timer.hpp>
#include <toy/time/Clock.hpp>
#include <toy/time/Sleep.hpp>

namespace toy{
namespace luamodule{
namespace time{

class Timer
{
	public:

		Timer(){}
		~Timer(){}

		lua::Num restart()
		{
			return _timer.restart();
		}

		lua::Num passed()
		{
			return _timer.elapsed();
		}

	private:

		toy::time::Timer   _timer;
};

class Clock
{
	public:

		Clock(){}
		~Clock(){}

		void update()
		{
			_clock.update();
		}

		lua::Int year()  { return _clock.year();   }
		lua::Int month() { return _clock.month();  }
		lua::Int day()   { return _clock.day();    }
		lua::Int wday()  { return _clock.wday();   }
		lua::Int hour()  { return _clock.hour();   }
		lua::Int minute(){ return _clock.minute(); }
		lua::Int second(){ return _clock.second(); }

	private:

		toy::time::Clock   _clock;
};

static int Sleep(lua::NativeState L)
{
	lua::Num   sec;

	lua::CheckVarFromLua(L,&sec,1);
	lua::Pop(L,1);

	toy::time::Sleep(sec);

	return 0;
}

}}}

#if defined(_WIN32)
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_time(lua::NativeState L)
{
	lua::State<>    lua(L);

	lua.setFunc( "sleep", ::toy::luamodule::time::Sleep );

	lua.bindMethod("restart", &::toy::luamodule::time::Timer::restart);
	lua.bindMethod("passed",  &::toy::luamodule::time::Timer::passed);
	lua.bindClassEx<::toy::luamodule::time::Timer>("new_timer");

	lua.bindMethod("update", &::toy::luamodule::time::Clock::update);
	lua.bindMethod("year",   &::toy::luamodule::time::Clock::year);
	lua.bindMethod("month",  &::toy::luamodule::time::Clock::month);
	lua.bindMethod("day",    &::toy::luamodule::time::Clock::day);
	lua.bindMethod("wday",   &::toy::luamodule::time::Clock::wday);
	lua.bindMethod("hour",   &::toy::luamodule::time::Clock::hour);
	lua.bindMethod("minute", &::toy::luamodule::time::Clock::minute);
	lua.bindMethod("second", &::toy::luamodule::time::Clock::second);
	lua.bindClassEx<::toy::luamodule::time::Clock>("new_clock");

	lua.cleanUnusedResource<::toy::luamodule::time::Timer>();
	lua.cleanUnusedResource<::toy::luamodule::time::Clock>();

	return 1;
}
