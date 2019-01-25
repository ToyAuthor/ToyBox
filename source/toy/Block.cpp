#include "toy/Block.hpp"
#include "toy/Oops.hpp"

namespace toy{

class _BasicBlock : public ::toy::Block
{
	public:

		_BasicBlock(uint32_t size)
		{
			_data = new uint8_t [size];

			if ( _data==nullptr )
			{
				toy::Oops(TOY_MARK);
				return;
			}

			_size = size;
		}

		~_BasicBlock()
		{
			if ( _data!=nullptr )
			{
				delete [] _data;
			}
		}

		uint8_t* data()
		{
			return _data;
		}

		uint32_t size() const
		{
			return _size;
		}

	protected:

		uint32_t    _size = 0;
		uint8_t*    _data = nullptr;
};

auto MarkBlock(uint32_t size)->std::shared_ptr<toy::Block>
{
	auto ptr = std::make_shared<_BasicBlock>(size);
	return ptr;
}

}
