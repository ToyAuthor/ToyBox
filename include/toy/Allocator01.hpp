
#pragma once


#include <cstdlib>
#include <cstring>
#include "toy/Math.hpp"

namespace toy
{

using math::exp1;



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
			Free();
		}

		bool Copy(void *p,size_t s)
		{
			SetSize(s);
			memcpy(mData,p,s);
			return 1;
		}

		void Free()
		{
			if(mData)
			{
				free(mData);
				mData=0;
				mSize=0;
				mTrueSize=0;
			}
		}

		// Allocate memory for user.
		bool SetSize(size_t s)
		{
			mSize=s;
			if(s>mTrueSize)
			{
				size_t		new_size=exp1<size_t>(s);

				if(mData==0)
				{
					mData=malloc(new_size);
				}
				else
				{
					mData=realloc(mData,new_size);
				}
				mTrueSize=new_size;
			}

			return 1;
		}

		// Almost same as SetSize(). It can release the memory unused.
		bool FitSize(size_t s)
		{
			mSize=s;
			size_t		new_size=exp1<size_t>(s);

			if(new_size>mTrueSize)
			{
				if(mData==0)
				{
					mData=malloc(new_size);
				}
				else
				{
					mData=realloc(mData,new_size);
				}
				mTrueSize=new_size;
			}
			else if(new_size<mTrueSize)
			{
				mData=realloc(mData,new_size);
				mTrueSize=new_size;
			}

			return 1;
		}

		void* GetData() const
		{
			return mData;
		}

		size_t GetSize() const
		{
			return mSize;
		}

	private:

		void*   mData = nullptr;
		size_t  mSize = 0;
		size_t  mTrueSize = 0;
};


}//namespace toy
