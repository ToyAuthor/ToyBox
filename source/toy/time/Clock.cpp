#include <ctime>
#include "toy/time/Clock.hpp"

namespace toy{
namespace time{

struct ClockPrivate
{
	struct tm  date;
	time_t     tick;
	bool       isFormat = false;
};

}}

using namespace toy;
using namespace time;

Clock::Clock():_this(new ClockPrivate)
{
	;
}

Clock::~Clock()
{
	delete _this;
}

void Clock::update()
{
	_this->isFormat = false;
	std::time(&(_this->tick));
}

static inline void UpdateTimeStructure(struct ClockPrivate *member)
{
	if ( member->isFormat==false )
	{
		member->isFormat = true;
		member->date = *(std::localtime( &(member->tick) ));
	}
}

int Clock::year() const
{
	UpdateTimeStructure(_this);
	return _this->date.tm_year + 1900;
}

int Clock::month() const
{
	UpdateTimeStructure(_this);
	return _this->date.tm_mon + 1;
}

int Clock::day() const
{
	UpdateTimeStructure(_this);
	return _this->date.tm_mday;
}

int Clock::wday() const
{
	UpdateTimeStructure(_this);
	return _this->date.tm_wday;
}

int Clock::hour() const
{
	UpdateTimeStructure(_this);
	return _this->date.tm_hour;
}

int Clock::minute() const
{
	UpdateTimeStructure(_this);
	return _this->date.tm_min;
}

int Clock::second() const
{
	UpdateTimeStructure(_this);
	return _this->date.tm_sec;
}
