
#pragma once

#include <memory>
#include "toy/Exception.hpp"

namespace toy{
namespace memory{

class Allocator02_MemoryPool
{
	public:

		Allocator02_MemoryPool()
		{
			;
		}

		virtual ~Allocator02_MemoryPool()
		{
			;
		}

		virtual void* malloc(size_t n) =0;
		virtual void  free(void *p)    =0;

	protected:

};

template<typename T>
class Allocator02
{
	public:

		Allocator02()
		{
			;
		}

		virtual ~Allocator02()
		{
			;
		}

		Allocator02(const Allocator02 &other)
		{
			copy_mykind(const_cast<Allocator02&>(other));
		}

		Allocator02 operator = (const Allocator02 &other)
		{
			copy_mykind(const_cast<Allocator02&>(other));
			return *this;
		}

		virtual T* allocate(std::size_t n)
		{
			/*
			T* obj = (T*)_pool.malloc(sizeof(T)*n);
			new (obj) T();     // or obj->T::T();
			return obj;
			*/

			T* obj = (T*)_pool->malloc(sizeof(T)*n);
			const auto objE = obj + n;

			for ( auto objC = obj ; objC!=objE ; ++objC )
			{
				new (objC) T();
			}

			return obj;
		}

		virtual void deallocate(T* p, std::size_t n)
		{
			const auto objE = p + n;

			for ( auto objC = p ; objC!=objE ; ++objC )
			{
				objC->~T();
			}

			_pool->free((void*)p);
		}

	protected:

		inline void copy_mykind(Allocator02&)
		{
			// This object not support clone itself.
			throw toy::Exception(TOY_MARK);
		}

		std::shared_ptr<::toy::memory::Allocator02MemoryPool>   _pool;
};


}//namespace memory
}//namespace toy
