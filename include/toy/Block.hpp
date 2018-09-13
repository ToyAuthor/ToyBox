
#pragma once

#include <cstdint>
#include "toy/Exception.hpp"

namespace toy{

class Block
{
	public:

		Block()
		{
			;
		}

		virtual ~Block()
		{
			;
		}

		virtual uint8_t* data() = 0;

		virtual uint32_t size() const = 0;
};

}
