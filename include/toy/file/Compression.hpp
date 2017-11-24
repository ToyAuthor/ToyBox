
#pragma once

#include "toy/Standard.hpp"
#include "toy/file/Export.hpp"

namespace toy{
namespace file{

class TOY_API_FILE CompressionStream
{
	public:

		CompressionStream();
		~CompressionStream();

		void* _get();

	private:

		void* _this = nullptr;
};

TOY_API_FILE extern int CompressExt( toy::file::CompressionStream*,
                                     const char* inputBuffer,
                                     char*       outputBuffer,
                                     int         inputSize,
                                     int         maxOutputSize );

inline int Compress( const char* inputBuffer,
                     char*       outputBuffer,
                     int         inputSize,
                     int         maxOutputSize )
{
	toy::file::CompressionStream obj;
	return CompressExt( &obj, inputBuffer, outputBuffer, inputSize, maxOutputSize );
}

TOY_API_FILE extern int Decompress( const char* inputBuffer,
                                    char*       outputBuffer,
                                    int         inputSize,
                                    int         maxOutputSize );

}}
