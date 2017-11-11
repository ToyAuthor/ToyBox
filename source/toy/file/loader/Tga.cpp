#include <cstdlib>
#include "toy/ImageBuffer.hpp"
#include "toy/file/loader/Tga.hpp"
#include "toy/file/File.hpp"




namespace toy{
namespace file{

#pragma pack(push,1)   // Save the present setting, then memory align by 1 byte.
struct TGA_Head
{
	int8_t      idlength;           // We want it be 0.
	int8_t      colourmaptype;      // We want it be 0.
	int8_t      datatypecode;       // We want it be 2. that means uncompressed RGB image.
	int16_t     colourmaporigin;    // Ignored if colourmaptype == 0
	int16_t     colourmaplength;    // Ignored if colourmaptype == 0
	int8_t      colourmapdepth;     // Ignored if colourmaptype == 0
	int16_t     x_origin;           // 0
	int16_t     y_origin;           // 0
	uint16_t    width;              // Width of image.
	uint16_t    height;             // Height of image.
	int8_t      bitsperpixel;       // We want it be 32. that means GBRA format.
	int8_t      imagedescriptor;
};
#pragma pack(pop)      // Restore origin setting.

static inline void BGR_to_RGB( uint8_t* data,   // The address of image.
                               uint32_t size)   // The size of image.
{
	uint8_t    temp;

	for( decltype(size) i=0 ; i<size ; i+=3)
	{
		temp=data[i+2];
		data[i+2]=data[i];
		data[i]=temp;
	}
}

static inline void BGRA_to_RGBA( uint8_t* data,   // The address of image.
                                 uint32_t size)   // The size of image.
{
	uint8_t    temp;

	for( decltype(size) i=0 ; i<size ; i+=4)
	{
		temp=data[i+2];
		data[i+2]=data[i];
		data[i]=temp;
	}
}

static inline bool Compare2Pixel(uint8_t *pix1,uint8_t *pix2)
{
	if( pix1[0]==pix2[0] &&
	    pix1[1]==pix2[1] &&
	    pix1[2]==pix2[2] )
		return 1;
	else
		return 0;
}

static inline void RGB_to_RGBA(    uint8_t* data,   // The address of image.
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
	pp1[2] = pp2[2];
	pp1[1] = pp2[1];
	pp1[0] = pp2[0];

	if(color && Compare2Pixel(pp1,color))
		pp1[3] = 0x00;
	else
		pp1[3] = 0xff;
}

bool loader::tga::Load(File *pIO,ImageBuffer *image)
{
	struct TGA_Head    header;

	pIO->seek(SEEK_SET,0);

	pIO->read(&header, sizeof(struct TGA_Head));

	uint32_t    width =(uint32_t)header.width;
	uint32_t    height=(uint32_t)header.height;

/*
	toy::Log("struct TGA_Head\n");
	toy::Log("{\n"));
	toy::Log("    idlength       :%d\n", header.idlength);
	toy::Log("    colourmaptype  :%d\n", header.colourmaptype);
	toy::Log("    datatypecode   :%d\n", header.datatypecode);
	toy::Log("    x_origin       :%d\n", header.x_origin);
	toy::Log("    y_origin       :%d\n", header.y_origin);
	toy::Log("    width          :%d\n", header.width);
	toy::Log("    height         :%d\n", header.height);
	toy::Log("    bitsperpixel   :%d\n", header.bitsperpixel);
	toy::Log("    imagedescriptor:%d\n", header.imagedescriptor);
	toy::Log("};\n");
*/

	if(header.idlength!=0)       return 0;
	if(header.colourmaptype!=0)  return 0;
	if(header.datatypecode!=2)   return 0;

	if(header.bitsperpixel!=24 &&
	   header.bitsperpixel!=32)  return 0;


	image->_setWidth(width);
	image->_setHeight(height);

	if(header.bitsperpixel==32)//GBRA format
	{
		uint32_t   size = width * height * 4;

		image->_getAllocator()->size(size);

		uint8_t*   data=(uint8_t*)image->_data();

		if( (header.imagedescriptor & 0x20) == 0)// bottom-left
		{
			pIO->read(data,size);
			BGRA_to_RGBA(data,size);
		}
		else// top-left(upside down)
		{
			uint8_t*   temp=(uint8_t*)malloc(size);

			pIO->read(temp,size);

			width*=4;

			for( int32_t k=0,j=size-width ; j>=0 ; j-=width,k+=width)
			{
				for( decltype(width) i=0 ; i<width ; i+=4)
				{
					data[i+k]  =temp[i+j+2];
					data[i+k+1]=temp[i+j+1];
					data[i+k+2]=temp[i+j];
					data[i+k+3]=temp[i+j+3];
				}
			}

			free(temp);
		}
	}
	else if(header.bitsperpixel==24)//GBR format
	{
		uint32_t   size = width * height * 3;

		image->_getAllocator()->size(width*height*4);// Finally, we want RBGA format not RBG.

		uint8_t*   data=(uint8_t*)image->_data();

		if( (header.imagedescriptor & 0x20) == 0)// bottom-left
		{
			pIO->read(data,size);

			BGR_to_RGB(data,size);
			RGB_to_RGBA(data,size,0);
		}
		else// top-left(upside down)
		{
			uint8_t*   temp=(uint8_t*)malloc(size);

			pIO->read(temp,size);

			width*=3;

			for( int32_t k=0,j=size-width ; j>=0 ; j-=width,k+=width)
			{
				for( uint32_t i=0 ; i<width ; i+=3)
				{
					data[i+k]  =temp[i+j+2];
					data[i+k+1]=temp[i+j+1];
					data[i+k+2]=temp[i+j];
				}
			}

			free(temp);
			RGB_to_RGBA(data,size,0);
		}
	}

	return 1;
}

bool loader::tga::Save(toy::File *pIO,toy::ImageBuffer *map)
{
	pIO->seek(SEEK_SET,0);

	uint32_t    width =map->width();
	uint32_t    height=map->height();

	struct TGA_Head    header;

	header.idlength=0;
	header.colourmaptype=0;
	header.datatypecode=2;
	header.x_origin=0;
	header.y_origin=0;
	header.width=width;
	header.height=height;
	header.bitsperpixel=32;
	header.imagedescriptor=8;

	uint32_t   size = width * height * 4;

	uint8_t*   data=(uint8_t*)malloc(size);

	memcpy(data,(uint8_t*)map->data(),size);

	uint8_t    temp;

	// RGBA -> BGRA
	for( decltype(size) i=0 ; i<size ; i+=4)
	{
		temp=data[i+2];
		data[i+2]=data[i];
		data[i]=temp;
	}

	pIO->write(&header,sizeof(struct TGA_Head));
	pIO->write(data,size);

	free(data);

	return 1;
}

}//namespace file
}//namespace toy
