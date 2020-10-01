
#pragma once

#include <cstdlib>
#include <cstring>
#include "toy/Math.hpp"

namespace toy{

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
			_copy(other);
		}

		Manager02 operator = (const Manager02 &other)
		{
			_copy(other);
			return *this;
		}

		bool copy(void *p,size_t s)
		{
			if ( ! size(s) )
			{
				return false;
			}

			std::memcpy(_data,p,s);
			return true;
		}

		void free()
		{
			if ( _data )
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
			if ( s>_trueSize )
			{
				void*    ptr     = nullptr;
				size_t   newSize = ::toy::math::Exp1<size_t>(s);

				if ( _data==nullptr )
				{
					ptr = std::malloc(newSize);
				}
				else
				{
					ptr = std::realloc(_data,newSize);
				}

				if ( ptr==nullptr )
				{
					return false;
				}

				_data     = ptr;
				_trueSize = newSize;
			}

			_size = s;

			return true;
		}

		// Allocate memory for user, and release the memory unused.
		bool fitSize(size_t s)
		{
			void*    ptr     = nullptr;
			size_t   newSize = ::toy::math::Exp1<size_t>(s);

			if ( newSize>_trueSize )
			{
				if ( _data==nullptr )
				{
					ptr = std::malloc(newSize);
				}
				else
				{
					ptr = std::realloc(_data,newSize);
				}
			}
			else if ( newSize<_trueSize )
			{
				ptr = std::realloc(_data,newSize);
			}
			else
			{
				_size = s;
				return true;
			}

			if ( ptr==nullptr )
			{
				return false;
			}

			_data     = ptr;
			_trueSize = newSize;
			_size     = s;

			return true;
		}

		void* data() const
		{
			return _data;
		}

		size_t size() const
		{
			return _size;
		}

		size_t realSize() const
		{
			return _trueSize;
		}

	private:

		void*   _data = nullptr;
		size_t  _size = 0;
		size_t  _trueSize = 0;

		void _copy(const Manager02 &other)
		{
			free();
			_size     = other._size;
			_trueSize = other._trueSize;
			_data = std::malloc(_trueSize);
			std::memcpy(_data,other._data,_size);
		}
};

}}
