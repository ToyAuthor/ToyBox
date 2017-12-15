
#pragma once

#include "toy/time/Export.hpp"

namespace toy{
namespace time{

struct TimerPrivate;

class TOY_API_TIME Timer
{
	public:

		Timer();
		~Timer();

		float restart();        // Calculate the seconds that has elapsed and put the time counter back to zero.
		float elapsed() const;  // Calculate the seconds that has elapsed.

	private:

		TimerPrivate *_this = nullptr;
};

}}
