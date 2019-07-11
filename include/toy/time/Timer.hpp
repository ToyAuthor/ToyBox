
#pragma once

#include <memory>
#include "toy/time/Export.hpp"

namespace toy{
namespace time{

struct TimerPrivate;

class TOY_API_TIME Timer
{
	public:

		#if defined(TOY_WINDOWS)
		typedef int64_t  RawType;
		#else
		// For Linux and Mac
		typedef uint64_t RawType;
		#endif

		Timer();
		~Timer();

		float restart();        // Calculate the seconds that has elapsed and put the time counter back to zero.
		float elapsed() const;  // Calculate the seconds that has elapsed.
		void  restart(RawType *);
		void  elapsed(RawType *) const;

		static float ToSeconds(const RawType &);

	private:

		std::unique_ptr<TimerPrivate>   _this;
};

}}
