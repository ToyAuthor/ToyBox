
#pragma once


#include <cstdlib>
#include <cstring>
#include "toy/Math.hpp"

namespace toy
{

using math::Exp1;



/*
 * The memory size of Allocator01 always base of 2.
 * 記憶體大小一直維持為2的n次方
 */
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

		bool copy(void *p,size_t s)
		{
			setSize(s);
			memcpy(_data,p,s);
			return 1;
		}

		void free()
		{
			if(_data)
			{
				::free(_data);
				_data = 0;
				_size = 0;
				_trueSize = 0;
			}
		}

		// Allocate memory for user.
		bool setSize(size_t s)
		{
			_size = s;

			if ( s>_trueSize )
			{
				size_t		new_size=Exp1<size_t>(s);

				if ( _data==0 )
				{
					_data = malloc(new_size);
				}
				else
				{
					_data = realloc(_data,new_size);
				}
				_trueSize = new_size;
			}

			return 1;
		}

		// Almost same as SetSize(). It can release the memory unused.
		bool fitSize(size_t s)
		{
			_size = s;

			size_t		new_size = Exp1<size_t>(s);

			if ( new_size>_trueSize )
			{
				if(_data==0)
				{
					_data = malloc(new_size);
				}
				else
				{
					_data = realloc(_data,new_size);
				}
				_trueSize = new_size;
			}
			else if ( new_size<_trueSize )
			{
				_data = realloc(_data,new_size);
				_trueSize = new_size;
			}

			return 1;
		}

		void* getData() const
		{
			return _data;
		}

		size_t getSize() const
		{
			return _size;
		}

	private:

		void*   _data = nullptr;
		size_t  _size = 0;
		size_t  _trueSize = 0;
};


}//namespace toy
