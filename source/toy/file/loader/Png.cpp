#include <cstdlib>
#include "toy/Image.hpp"
#include "toy/file/loader/Png.hpp"
#include "toy/file/File.hpp"

//#define PNG_DEBUG 3
#include <png.h>


#define USING_MEMORY_TO_READ_PNG   0

namespace toy{
namespace file{


static bool IsNotPng(File *pIO)
{
	const int       size = 8;
	unsigned char   header[size];

	if( !pIO->Read(header,size) )
	{
		// Cannot read file.
		Oops(TOY_MARK);
		return 1;
	}

	if( png_sig_cmp(header, 0, size) )
	{
		// It's not a PNG file.
		Oops(TOY_MARK);
		return 1;
	}

	return 0;
}

static inline png_structp CreateReadDevice()
{
	png_structp   handle = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if( !handle )
	{
		Oops(TOY_MARK);
		return NULL;
	}

	return handle;
}
#if !USING_MEMORY_TO_READ_PNG
static png_infop CreateInfo(png_structp handle,File *pIO)
{
	if( !handle )
	{
		Oops(TOY_MARK);
		return NULL;
	}

	png_infop           info;

	info = png_create_info_struct(handle);

	if( !info )
	{
		Oops(TOY_MARK);
		png_destroy_read_struct(&handle, NULL, NULL);
		return NULL;
	}

	#ifdef PNG_SETJMP_SUPPORTED
		if( setjmp(png_jmpbuf(handle)) )
		{
			png_destroy_read_struct(&handle, &info, NULL);
			Oops(TOY_MARK);
			return NULL;
		}
	#endif

	png_init_io(handle, (png_FILE_p)pIO->GetFilePointer());  // Try to remove this way.
	png_set_sig_bytes(handle, 8);   // Let libpng know you have been call png_sig_cmp().
	png_read_info(handle, info);

	return info;
}
#endif

static void CopyImageSize(ImageOpener *image,png_structp handle, png_infop info)
{
	int    height = png_get_image_height(handle, info);
	int    width  = png_get_image_width (handle, info);

	image->SetHeight(height);
	image->SetWidth(width);
	image->GetAllocator()->SetSize( sizeof(png_byte) * 4 * width * height );
}

static int CountRowSize( int width, png_structp handle, png_infop info )
{
	int     rowbytes;

	if (png_get_bit_depth(handle, info) == 16)
	{
		// Not support yet.(Maybe never do)
		Oops(TOY_MARK);
		rowbytes = width * 8;
	}
	else
	{
		rowbytes = width * 4;
	}

	return rowbytes;
}

static png_bytep* NewImageIndex( ImageOpener *image, int rowbytes )
{
	png_bytep*   row_pointers = (png_bytep*)malloc(sizeof(png_bytep)*image->GetHeight());

	uint8_t   *data=(uint8_t*)image->GetData();

	for( int y=image->GetHeight()-1 ; y>=0 ; y--,data+=rowbytes )
	{
		row_pointers[y] = (png_byte*)data;
	}

	return row_pointers;
}

static void LoadImage( ImageOpener *image, png_structp handle, png_infop info )
{
	int    rowbytes = CountRowSize( image->GetWidth(), handle, info );

	png_bytep*   address = NewImageIndex( image, rowbytes );
	png_read_image( handle, address );
	free(address);
}

//typedef unsigned char png_byte;

#if !USING_MEMORY_TO_READ_PNG
bool loader::Png::Load(File *pIO,Image *map)
{
	if( IsNotPng(pIO) )
	{
		return 0;
	}

	png_structp     handle = CreateReadDevice();
	png_infop       info   = CreateInfo(handle,pIO);

	if( !info )
	{
		return 0;
	}

	ImageOpener         image(map);

	CopyImageSize( &image, handle, info );

	LoadImage( &image, handle, info );

	png_destroy_read_struct( &handle, &info, NULL );

	return 1;
}
#endif

#if USING_MEMORY_TO_READ_PNG
//------------------------For reading png from buffer------------------------start

struct DataHandle
{
	//DataHandle():data(png_data),size(png_data_size){}
	DataHandle(png_byte* _data,png_size_t _size):data(_data),size(_size){}

	const png_byte*    data;
	const png_size_t   size;
};

struct ReadDataHandle
{
	ReadDataHandle(png_byte* _data,png_size_t _size,png_size_t _offset)
		:data(_data,_size),offset(_offset){}

	const DataHandle   data;
	png_size_t         offset;
};

struct PngInfo
{
	const png_uint_32    width;
	const png_uint_32    height;
	const int            color_type;
};

static void ReadPngCallback( png_structp png_ptr, png_byte* raw_data, png_size_t length)
{
	ReadDataHandle*    handle   = static_cast<ReadDataHandle*>(png_get_io_ptr(png_ptr));
	const png_byte*    png_file = handle->data.data + handle->offset;

	memcpy(raw_data, png_file, length);
	handle->offset += length;
}

static PngInfo ReadAndUpdateInfo(const png_structp png_ptr, const png_infop info_ptr)
{
	png_uint_32 width, height;
	int bit_depth, color_type;

	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(
		png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

	// Convert transparency to full alpha
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(png_ptr);
	}

	// Convert grayscale, if needed.
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
	{
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	}

	// Convert paletted images, if needed.
	if (color_type == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_palette_to_rgb(png_ptr);
	}

	// Add alpha channel, if there is none.
	// Rationale: GL_RGBA is faster than GL_RGB on many GPUs)
	if (color_type == PNG_COLOR_TYPE_PALETTE || color_type == PNG_COLOR_TYPE_RGB)
	{
		png_set_add_alpha(png_ptr, 0xFF, PNG_FILLER_AFTER);
	}

	// Ensure 8-bit packing
	if (bit_depth < 8)
	{
		png_set_packing(png_ptr);
	}
	else if (bit_depth == 16)
	{
		png_set_scale_16(png_ptr);
	}

	png_read_update_info(png_ptr, info_ptr);

	// Read the new color type after updates have been made.
	color_type = png_get_color_type(png_ptr, info_ptr);

	return (PngInfo) {width, height, color_type};
}

static DataHandle ReadEntirePngImage(
	const png_structp  png_ptr,
	const png_infop    info_ptr,
	const png_uint_32  height )
{
	const png_size_t row_size = png_get_rowbytes(png_ptr, info_ptr);
	const int data_length = row_size * height;
	//assert(row_size > 0);

	png_byte* raw_image = static_cast<png_byte*>( malloc(data_length) );
	//assert(raw_image != NULL);

	png_byte* row_ptrs[height];

	png_uint_32 i;

	for (i = 0; i < height; i++)
	{
		row_ptrs[i] = raw_image + i * row_size;
	}

	png_read_image(png_ptr, &row_ptrs[0]);

	return DataHandle(raw_image, data_length);
}

static png_infop CreateInfo(png_structp handle,File *pIO)
{
	(void)pIO;

	if( !handle )
	{
		Oops(TOY_MARK);
		return NULL;
	}

	png_infop           info;

	info = png_create_info_struct(handle);

	if( !info )
	{
		Oops(TOY_MARK);
		png_destroy_read_struct(&handle, NULL, NULL);
		return NULL;
	}

	#ifdef PNG_SETJMP_SUPPORTED
		if( setjmp(png_jmpbuf(handle)) )
		{
			png_destroy_read_struct(&handle, &info, NULL);
			Oops(TOY_MARK);
			return NULL;
		}
	#endif

	return info;
}

//------------------------For reading png by from buffer------------------------end

bool loader::Png::Load(File *pIO,Image *map)
{
	if( IsNotPng(pIO) )
	{
		return 0;
	}

	png_structp     handle = CreateReadDevice();
	png_infop       info   = CreateInfo(handle,pIO);

	if( !info )
	{
		return 0;
	}

	ImageOpener         image(map);

	CopyImageSize( &image, handle, info );  // Need another version.

	ReadDataHandle   data(0,0,0);  // ( mem_address, mem_size, 0 )
	png_set_read_fn(handle, static_cast<void*>(&data), ReadPngCallback);

	const PngInfo png_info = ReadAndUpdateInfo(handle, info);

	const DataHandle raw_image = ReadEntirePngImage(
		handle, info, png_info.height);

	(void)raw_image;
/*
	image.SetHeight(png_info.height);
	image.SetWidth(png_info.width);
	image.GetAlloctor()->SetSize(raw_image.size);
*/

	LoadImage( &image, handle, info );

	png_read_end(handle, info);
	png_destroy_read_struct( &handle, &info, NULL );

	return 1;
}

#endif

}//namespace file
}//namespace toy
