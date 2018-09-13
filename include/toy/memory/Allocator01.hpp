
#pragma once

#include <cstdlib>
#include <cstring>
#include "toy/Math.hpp"

namespace toy{
namespace memory{

using ::toy::math::Exp1;

// The memory size of Allocator01 always base of 2.
template<typename T>
class Allocator01
{
	public:

		Allocator01()
		{
			;
		}

		~Allocator01()
		{
			free();
		}

		Allocator01(const Allocator01 &other)
		{
			copy_mykind(const_cast<Allocator01&>(other));
		}

		Allocator01 operator = (const Allocator01 &other)
		{
			copy_mykind(const_cast<Allocator01&>(other));
			return *this;
		}

		T* allocate(std::size_t n)
		{
			(void)n;
		}

		void deallocate(T* p, std::size_t n)
		{
			(void)n;
			(void)p;
		}

	private:

		bool copy(void *p,size_t s)
		{
			size(s);
			std::memcpy(_data,p,s);
			return 1;
		}

		void free()
		{
			if(_data)
			{
				std::free(_data);
				_data = nullptr;
				_size = 0;
				_trueSize = 0;
			}
		}

		// Allocate memory for user.
		bool size(size_t s)
		{
			_size = s;

			if ( s>_trueSize )
			{
				size_t		new_size=Exp1<size_t>(s);

				if ( _data==nullptr )
				{
					_data = std::malloc(new_size);
				}
				else
				{
					_data = std::realloc(_data,new_size);
				}
				_trueSize = new_size;
			}

			return 1;
		}

		// Allocate memory for user, and release the memory unused.
		bool fitSize(size_t s)
		{
			_size = s;

			size_t		new_size = Exp1<size_t>(s);

			if ( new_size>_trueSize )
			{
				if(_data==nullptr)
				{
					_data = std::malloc(new_size);
				}
				else
				{
					_data = std::realloc(_data,new_size);
				}
				_trueSize = new_size;
			}
			else if ( new_size<_trueSize )
			{
				_data = std::realloc(_data,new_size);
				_trueSize = new_size;
			}

			return 1;
		}

		void* data() const
		{
			return _data;
		}

		size_t size() const
		{
			return _size;
		}

		void*          _data = nullptr;
		std::size_t    _size = 0;
		std::size_t    _trueSize = 0;

		inline void copy_mykind(Allocator01 &other)
		{
			free();
			_size     = other._size;
			_trueSize = other._trueSize;
			_data = std::malloc(_trueSize);
			std::memcpy(_data,other._data,_size);
		}
};


}//namespace memory
}//namespace toy
