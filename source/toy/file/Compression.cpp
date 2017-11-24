#include "lz4.h"
#include "toy/file/Compression.hpp"

namespace toy{
namespace file{

int CompressExt( toy::file::CompressionStream* stream,
                 const char* inputBuffer,
                 char*       outputBuffer,
                 int         inputSize,
                 int         maxOutputSize )
{
	return LZ4_compress_fast_extState( stream->_get(),
	                                   inputBuffer,
	                                   outputBuffer,
	                                   inputSize,
	                                   maxOutputSize,
	                                   1 );
}

int Decompress( const char* inputBuffer,
                char*       outputBuffer,
                int         inputSize,
                int         maxOutputSize )
{
	return LZ4_decompress_safe( inputBuffer, outputBuffer, inputSize, maxOutputSize );
}

}}

using namespace toy;
using namespace file;

CompressionStream::CompressionStream():_this(LZ4_createStream())
{
	;
}

CompressionStream::~CompressionStream()
{
	LZ4_freeStream(static_cast<LZ4_stream_t*>(_this));
}

void* CompressionStream::_get()
{
	return _this;
}
