#include <cstdint>
#include <chrono>
#include <thread>
#include "toy/Oops.hpp"
#include "toy/time/Sleep.hpp"

void toy::time::Sleep(float sec)
{
	if ( sec!=float(0) )
	{
		if ( sec<float(0) )
		{
			toy::Oops(TOY_MARK);
		}
		else if ( sec<float(4294967) )
		{
			std::this_thread::sleep_for(std::chrono::duration<uint32_t,std::ratio<1,1000>>(static_cast<uint32_t>(sec*float(1000))));
		}
		else
		{
			// 4294967 seconds is over than 49 days. Why sleep so long?
			toy::Oops(TOY_MARK);
		}
	}
}
