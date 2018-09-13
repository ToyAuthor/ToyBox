
#pragma once


#include <cstdlib>
#include <cstring>
#include "toy/Math.hpp"

namespace toy{

using math::Exp1;
namespace memory{

// The memory size of Manager02 always base of 2.
class Manager02
{
	public:

		Manager02()
		{
			;
		}

		~Manager02()
		{
			free();
		}

		Manager02(const Manager02 &other)
		{
			copy_mykind(const_cast<Manager02&>(other));
		}

		Manager02 operator = (const Manager02 &other)
		{
			copy_mykind(const_cast<Manager02&>(other));
			return *this;
		}

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

	private:

		void*   _data = nullptr;
		size_t  _size = 0;
		size_t  _trueSize = 0;

		inline void copy_mykind(Manager02 &other)
		{
			free();
			_size     = other._size;
			_trueSize = other._trueSize;
			_data = std::malloc(_trueSize);
			std::memcpy(_data,other._data,_size);
		}
};

}}
