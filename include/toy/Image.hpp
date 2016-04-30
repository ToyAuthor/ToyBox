#pragma once

#include "toy/Standard.hpp"
#include "toy/Allocator01.hpp"


namespace toy{

class ImageOpener;


// It's a container of image file.
class TOY_API Image
{
	public:
		friend class toy::ImageOpener;

		Image();
		~Image();

		void    Clean();

		// Give you a memory about the image data. Return NULL if it's a empty object.
		uint8_t* GetData() const
		{
			return (uint8_t*)(mData.GetData());
		}

		int32_t GetHeight() const
		{
			return mHeight;
		}

		int32_t GetWidth() const
		{
			return mWidth;
		}

		int32_t GetSize() const
		{
			return mWidth * mHeight;
		}

	private:

		Allocator01     mData;      // Saving a image data on memory.
		int32_t         mHeight = 0;
		int32_t         mWidth = 0;
};

// You can use it to modify the inside of Image.
class ImageOpener
{
	public:

		ImageOpener(Image *core):mCore(core)
		{
			;
		}

		~ImageOpener(){}

		Allocator01* GetAllocator()
		{
			return &(mCore->mData);
		}

		uint8_t* GetData() const
		{
			return mCore->GetData();
		}

		int32_t GetHeight() const
		{
			return mCore->mHeight;
		}

		int32_t GetWidth() const
		{
			return mCore->mWidth;
		}

		int32_t GetSize() const
		{
			return mCore->GetSize();
		}

		void SetSize(size_t n)
		{
			mCore->mData.SetSize(n);
		}

		void SetHeight(int32_t n)
		{
			mCore->mHeight=n;
		}

		void SetWidth(int32_t n)
		{
			mCore->mWidth=n;
		}

	private:

		Image   *mCore;
};

}//namespace toy
