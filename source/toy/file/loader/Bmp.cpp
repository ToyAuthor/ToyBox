#include "toy/ImageBuffer.hpp"
#include "toy/file/loader/Bmp.hpp"
#include "toy/file/File.hpp"




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
	uint32_t     bfOffBits;  // bfOffBits == sizeof(BMP_Head) + sizeof(BMP_Info)
};
#pragma pack(pop)       // Restore original setting.

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
	uint8_t      rgb_Blue;
	uint8_t      rgb_Green;
	uint8_t      rgb_Red;
	uint8_t      rgb_Reserved;
};


static inline bool Compare2Pixel(uint8_t *pix1,uint8_t *pix2)
{
	if( pix1[0]==pix2[0] &&
	    pix1[1]==pix2[1] &&
	    pix1[2]==pix2[2] )
		return 1;
	else
		return 0;
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

static inline void BGR_to_RGBA(toy::ImageBuffer *image)
{
	uint32_t    size = image->size()*3;   // 1 pixel == 3 byte.
	uint8_t*    data = image->_data();

	BGR_to_RGB(data,size);
	RGB_to_RGBA(data,size,0);
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
	int32_t      width  = info.biWidth;
	int32_t      height = info.biHeight;

	if( (width*height*3) != (int32_t)size )
	{
		// May be BMP file not correct.
		Oops(TOY_MARK);
	}

	image->_setHeight(height);
	image->_setWidth(width);
	image->_getAllocator()->size((size/3)*4);  // Allocate more memory. May be we need it later.

	// I need to checkout memory enough over here.

	pIO->read(image->_data(),size);
}

bool loader::bmp::Load(toy::File *pIO,toy::ImageBuffer *image)
{
//	pIO->Seek(File::SET,0);   May be it will crash system. But it's much safe.

	LoadImage( pIO, image );

	BGR_to_RGBA(image);

	return 1;
}

// no good
bool loader::bmp::Save(toy::File *pIO,toy::ImageBuffer *map)
{
	struct BMP_Head     head;
	struct BMP_Info     info;
	int32_t             width = map->width();
	int32_t             height= map->height();

	pIO->seek(SEEK_SET,0);

	info.biSize = sizeof(struct BMP_Head);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;
	info.biSizeImage = width * height * 3;
	info.biBitCount = 24;

	head.bfType = 0x4d42;
	head.bfOffBits = sizeof(struct BMP_Head) + sizeof(struct BMP_Info);
	head.bfSize = head.bfOffBits + info.biSizeImage;
	head.bfReserved1 = head.bfReserved2 = 0;

	char *pBuf = (char*)malloc(info.biSizeImage);

	// handle pBuf

	pIO->write(&head, sizeof(struct BMP_Head));
	pIO->write(&info, sizeof(struct BMP_Info));

	pIO->write(pBuf, info.biSizeImage);

	free(pBuf);

	return 1;
}

}//namespace file
}//namespace toy
