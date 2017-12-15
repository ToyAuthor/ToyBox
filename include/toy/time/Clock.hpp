
#pragma once

#include "toy/time/Export.hpp"

namespace toy{
namespace time{

struct ClockPrivate;

class TOY_API_TIME Clock
{
	public:

		Clock();
		~Clock();

		void update();         // Get system time.

		int year() const;      // Common Era
		int month() const;     // 1~12
		int day() const;       // 1~31
		int wday() const;      // 0~6 (Sunday~Saturday)
		int hour() const;      // 0~23
		int minute() const;    // 0~59
		int second() const;    // 0~59 (It is 0~60 for leap seconds in certain systems)

	private:

		ClockPrivate *_this = nullptr;
};

}}
