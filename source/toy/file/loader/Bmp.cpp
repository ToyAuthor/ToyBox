#include "toy/ErrorTag.hpp"
#include "toy/Throw.hpp"
#include "toy/Catch.hpp"
#include "toy/Oops.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/file/loader/Bmp.hpp"
#include "toy/file/File.hpp"
#include "toy/math/SafeInt.hpp"

namespace toy{
namespace file{

/*
--------------------------------------------------------
BMP structure is look like this.
BMP_Head and BMP_Info could give you information of image.

┌--------┐
│BMP_Head│
├--------┤
│BMP_Info│
├--------┤
│BitImage│
└--------┘
--------------------------------------------------------
*/

#pragma pack(push,2)    // Let memory aligned to a 2-byte boundary.
struct BMP_Head
{
	uint16_t     bfType;
	uint32_t     bfSize;
	uint16_t     bfReserved1;
	uint16_t     bfReserved2;
	uint32_t     bfOffBits;  // bfOffBits == sizeof(BMP_Head) + sizeof(BMP_Info) + Palette
};

struct BMP_Info
{
	uint32_t     biSize;
	int32_t      biWidth;            // Width of image.
	int32_t      biHeight;           // Height of image.
	uint16_t     biPlanes;
	uint16_t     biBitCount;
	uint32_t     biCompression;
	uint32_t     biSizeImage;        // Size of image.
	int32_t      biXPelsPerMeter;
	int32_t      biYPelsPerMeter;
	uint32_t     biClrUsed;
	uint32_t     biClrImportant;
};
#pragma pack(pop)       // Restore original setting.

static inline bool Compare2Pixel(uint8_t *pix1,uint8_t *pix2)
{
	if( pix1[0]==pix2[0] &&
	    pix1[1]==pix2[1] &&
	    pix1[2]==pix2[2] )
		return true;
	else
		return false;
}

static inline void RGB_to_RGBA( uint8_t* data,   // The address of image.
                                uint32_t size,   // The size of image.
                                uint8_t* color)  // Change this color of image to Alpha.
{
	uint8_t      *pp1 = data + size/3*4 - 4;
	uint8_t      *pp2 = data + size     - 3;

	for( ; pp2 != data ; pp1-=4,pp2-=3 )
	{
		pp1[2] = pp2[2];
		pp1[1] = pp2[1];
		pp1[0] = pp2[0];

		// if( It is the color we want to modify )
		if(color && Compare2Pixel(pp1,color))
			pp1[3] = 0x00;  // Alpha value:0
		else
			pp1[3] = 0xff;  // Alpha value:100
	}

	// Handle the last pixel.
	if(color && Compare2Pixel(pp1,color))
		pp1[3] = 0x00;
	else
		pp1[3] = 0xff;
}

static inline void BGR_to_RGB( uint8_t* data,   // The address of image.
                               uint32_t size)   // The size of image.
{
	uint8_t      temp = 0;

	for( decltype(size) i=0 ; i<size ; i+=3 )
	{
		temp        = data[i];
		data[i]     = data[i+2];
		data[i+2]   = temp;
	}
}

static inline void RGB_to_BGR( uint8_t* data,   // The address of image.
                               uint32_t size)   // The size of image.
{
	BGR_to_RGB(data,size);
}

static inline void BGR_to_RGBA(toy::ImageBuffer *image)
{
	uint32_t    size = image->size()*3;   // 1 pixel == 3 byte.
	uint8_t*    data = image->_data();

	BGR_to_RGB(data,size);
	RGB_to_RGBA(data,size,0);
}

static inline void RGBA_to_BGRA( uint8_t* data,   // The address of image.
                                 uint32_t size)   // The size of image.
{
	uint8_t      *ptr = data + size - 4;

	uint8_t temp = 0;

	for( ; ptr != data ; ptr-=4 )
	{
		temp = ptr[0];
		ptr[0] = ptr[2];
		ptr[2] = temp;
	}
}

static inline void ReadInfo(toy::File *pIO, struct BMP_Info *info)
{
	struct BMP_Head     head;

	pIO->read(&head,sizeof(struct BMP_Head));
	pIO->read(info,head.bfOffBits-sizeof(struct BMP_Head));
}

static inline void LoadImage( toy::File *pIO, toy::ImageBuffer *image )
{
	struct BMP_Info     info;

	ReadInfo(pIO,&info);

	uint32_t     size   = info.biSizeImage;
	uint32_t     width  = info.biWidth;
	uint32_t     height = info.biHeight;

	if( (width*height*3) != size )
	{
		// May be BMP file not correct.
		Oops(TOY_MARK);
	}

	image->_setHeight(height);
	image->_setWidth(width);

	if ( image->_getAllocator()->size((size/3)*4)==false )  // Allocate more memory. May be we need it later.
	{
		toy::Throw(TOY_MARK,toy::MEMORY_ISSUE);
	}

	// I need to checkout memory enough over here.

	pIO->read(image->_data(),size);
}

bool loader::bmp::Load(toy::File *pIO,toy::ImageBuffer *image)
{
//	pIO->Seek(SEEK_SET,0);   It may make system crashed. But it's much safe.

	try
	{
		LoadImage( pIO, image );
	}
	catch ( std::exception &e )
	{
		toy::Catch(e);
		return false;
	}

	BGR_to_RGBA(image);

	return true;
}

static void ExtensionSize(const uint8_t *oldData,uint32_t oldWidth,uint32_t oldHeight,int pixel,uint8_t *newData,uint32_t newWidth, uint32_t newHeight)
{
	if ( oldData != newData )
	{
		std::memcpy(newData,oldData,newWidth*newHeight*pixel);
	}

	if ( newWidth!=oldWidth )
	{
		uint8_t  *data01 = newData + ((newWidth*(oldHeight-1))*pixel);
		uint8_t  *data02 = newData + ((oldWidth*(oldHeight-1))*pixel);

		for ( auto j = oldHeight; j>0 ;--j )
		{
			for ( auto i = oldWidth*pixel; i>0 ;--i )
			{
				data01[i-1] = data02[i-1];
			}

			data01 -= newWidth*pixel;
			data02 -= oldWidth*pixel;
		}
	}
}

bool loader::bmp::Save(toy::File *pIO,toy::ImageBuffer *map)
{
	if ( map->empty() ) return false;

	if ( map->format()!=toy::RGB && map->format()!=toy::BGR && map->format()!=toy::GREY && map->format()!=toy::RGBA )
	{
		return false;
	}

	struct BMP_Head     head;
	struct BMP_Info     info;
	uint32_t            width = map->width();
	uint32_t            height= map->height();

	if ( static_cast<uint32_t>( width)!=map->width()  ) return false;
	if ( static_cast<uint32_t>(height)!=map->height() ) return false;

	pIO->seek(SEEK_SET,0);

	info.biSize = 40;
	info.biWidth = toy::math::SafeInt<int32_t>(width,TOY_MARK);
	info.biHeight = toy::math::SafeInt<int32_t>(height,TOY_MARK);
	info.biPlanes = 1;
	info.biClrImportant = 0;
	info.biCompression = 0;

	info.biXPelsPerMeter = 0;      // 72dpi=2835, 96dpi=3780
	info.biYPelsPerMeter = 0;      // 120dpi=4724, 300dpi=11811

	width = (width+3) & (~3);

	if ( map->format()==toy::GREY )
	{
		info.biSizeImage = width * height;
		info.biBitCount = 8;
		info.biClrUsed = 256;
	}
	else if( map->format()==toy::RGBA )
	{
		info.biSizeImage = width * height * 4;
		info.biBitCount = 32;
		info.biClrUsed = 0;
	}
	else
	{
		info.biSizeImage = width * height * 3;
		info.biBitCount = 24;
		info.biClrUsed = 0;
	}

	head.bfType = 0x4d42;
	head.bfOffBits = sizeof(struct BMP_Head) + sizeof(struct BMP_Info)+((map->format()==toy::GREY)?1024:0);
	head.bfSize = head.bfOffBits + info.biSizeImage;
	head.bfReserved1 = head.bfReserved2 = 0;

	pIO->write(&head, sizeof(struct BMP_Head));
	pIO->write(&info, sizeof(struct BMP_Info));

	if ( map->format()==toy::RGB )
	{
		RGB_to_BGR(map->_data(),map->size());

		if ( width==map->width() )
		{
			map->_setFormat(toy::BGR);
		}
		else
		{
			map->_getAllocator()->size(info.biSizeImage*3);
			ExtensionSize(map->data(),map->width(),height,3,map->_data(),width, height);
		}
	}
	else if ( map->format()==toy::BGR )
	{
		if ( width!=map->width() )
		{
			map->_getAllocator()->size(info.biSizeImage*3);
			ExtensionSize(map->data(),map->width(),height,3,map->_data(),width, height);
		}
	}
	else if ( map->format()==toy::RGBA )
	{
		RGBA_to_BGRA(map->_data(),map->size());

		if ( width==map->width() )
		{
			map->_setFormat(toy::RGBA);
		}
		else
		{
			map->_getAllocator()->size(info.biSizeImage*4);
			ExtensionSize(map->data(),map->width(),height,4,map->_data(),width, height);
		}
	}
	else if ( map->format()==toy::GREY )
	{
		uint8_t buf[4];

		for( int i = 0; i<256 ; ++i )
		{
			buf[0] = static_cast<uint8_t>(i);
			buf[1] = static_cast<uint8_t>(i);
			buf[2] = static_cast<uint8_t>(i);
			buf[3] = 0;
			pIO->write(buf, 4);
		}

		if ( width!=map->width() )
		{
			map->_getAllocator()->size(info.biSizeImage);
			ExtensionSize(map->data(),map->width(),height,1,map->_data(),width, height);
		}
	}
	else
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	pIO->write(map->data(), info.biSizeImage);

	if ( width!=map->width() )
	{
		map->_getAllocator()->free();
	}

	return true;
}

bool loader::bmp::Save(toy::File *pIO,const toy::ImageBuffer *map)
{
	if ( map->empty() ) return false;

	if ( map->format()!=toy::RGB && map->format()!=toy::BGR && map->format()!=toy::GREY && map->format()!=toy::RGBA )
	{
		return false;
	}

	struct BMP_Head     head;
	struct BMP_Info     info;
	uint32_t            width = map->width();
	uint32_t            height= map->height();

	pIO->seek(SEEK_SET,0);

	info.biSize = 40;
	info.biWidth = toy::math::SafeInt<int32_t>(width,TOY_MARK);
	info.biHeight = toy::math::SafeInt<int32_t>(height,TOY_MARK);
	info.biPlanes = 1;
	info.biClrImportant = 0;
	info.biCompression = 0;

	info.biXPelsPerMeter = 0;      // 72dpi=2835, 96dpi=3780
	info.biYPelsPerMeter = 0;      // 120dpi=4724, 300dpi=11811

	width = (width+3) & (~3);

	if ( map->format()==toy::GREY )
	{
		info.biSizeImage = width * height;
		info.biBitCount = 8;
		info.biClrUsed = 256;
	}
	else if( map->format()==toy::RGBA )
	{
		info.biSizeImage = width * height * 4;
		info.biBitCount = 32;
		info.biClrUsed = 0;
	}
	else
	{
		info.biSizeImage = width * height * 3;
		info.biBitCount = 24;
		info.biClrUsed = 0;
	}

	head.bfType = 0x4d42;
	head.bfOffBits = sizeof(struct BMP_Head) + sizeof(struct BMP_Info)+((map->format()==toy::GREY)?1024:0);
	head.bfSize = head.bfOffBits + info.biSizeImage;
	head.bfReserved1 = head.bfReserved2 = 0;

	pIO->write(&head, sizeof(struct BMP_Head));
	pIO->write(&info, sizeof(struct BMP_Info));

	if ( map->format()==toy::RGB )
	{
		uint8_t *pBuf = (uint8_t*)malloc(info.biSizeImage);

		std::memcpy(pBuf,map->data(),map->size()*3);

		RGB_to_BGR(pBuf, map->size());

		if ( width!=map->width() )
		{
			ExtensionSize(pBuf,map->width(),height,3,pBuf,width, height);
		}

		pIO->write(pBuf, info.biSizeImage);

		free(pBuf);
	}
	else if ( map->format()==toy::BGR )
	{
		if ( width==map->width() )
		{
			pIO->write(map->data(), info.biSizeImage);
		}
		else
		{
			uint8_t *pBuf = (uint8_t*)malloc(info.biSizeImage);

			std::memcpy(pBuf,map->data(),map->size()*3);

			ExtensionSize(pBuf,map->width(),height,3,pBuf,width, height);

			pIO->write(pBuf, info.biSizeImage);

			free(pBuf);
		}
	}
	else if ( map->format()==toy::RGBA )
	{
		uint8_t *pBuf = (uint8_t*)malloc(info.biSizeImage);

		std::memcpy(pBuf,map->data(),map->size()*4);

		RGBA_to_BGRA(pBuf, map->size());

		if ( width!=map->width() )
		{
			ExtensionSize(pBuf,map->width(),height,4,pBuf,width, height);
		}

		pIO->write(pBuf, info.biSizeImage);

		free(pBuf);
	}
	else if ( map->format()==toy::GREY )
	{
		uint8_t buf[4];

		for( int i = 0; i<256 ; ++i )
		{
			buf[0] = static_cast<uint8_t>(i);
			buf[1] = static_cast<uint8_t>(i);
			buf[2] = static_cast<uint8_t>(i);
			buf[3] = 0;
			pIO->write(buf, 4);
		}

		if ( width==map->width() )
		{
			pIO->write(map->data(), info.biSizeImage);
		}
		else
		{
			uint8_t *pBuf = (uint8_t*)malloc(info.biSizeImage);

			std::memcpy(pBuf,map->data(),map->size());

			ExtensionSize(pBuf,map->width(),height,1,pBuf,width, height);

			pIO->write(pBuf, info.biSizeImage);

			free(pBuf);
		}

	}
	else
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	return true;
}

}//namespace file
}//namespace toy
