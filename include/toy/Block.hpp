
#pragma once

#include <cstdint>
#include <memory>
#include "toy/Exception.hpp"
#include "toy/CompilerConfig.hpp"

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

	//	virtual const uint8_t* data() = 0;   // Doesn't need it. Allow write memory.
		virtual uint8_t* data() = 0;
		virtual const uint8_t* cdata() const = 0;

		virtual uint32_t size() const = 0;

		Block(const Block &other)
		{
			copy_mykind(const_cast<Block&>(other));
		}

		void operator = (const Block &other)
		{
			copy_mykind(const_cast<Block&>(other));
		}

	protected:

		virtual void copy_mykind(Block&)
		{
			// This object not support clone itself.
			throw toy::Exception(TOY_MARK);
		}
};

TOY_API extern auto MarkBlock(uint32_t size)->std::shared_ptr<toy::Block>;

}
