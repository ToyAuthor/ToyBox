#include "toy/archive/CoreLZ4.hpp"

using namespace toy;
using namespace archive;

CoreLZ4::CoreLZ4()
{
	;
}

CoreLZ4::~CoreLZ4()
{
	;
}

void CoreLZ4::init()
{/*
	if ( _encode_t==nullptr )
	{
		_encode_t = LZ4_createStream();
	}

	if ( _decode_t==nullptr )
	{
		_decode_t = LZ4_createStreamDecode();
	}*/
}

void CoreLZ4::drop()
{/*
	if ( _encode_t )
	{
		LZ4_freeStream(_encode_t);
		_encode_t = nullptr;
	}

	if ( _decode_t )
	{
		LZ4_freeStreamDecode(_decode_t);
		_decode_t = nullptr;
	}*/
}

bool CoreLZ4::compress( const uint8_t* input,
                        uint8_t*       output,
                        uint32_t       inputSize,
                        uint32_t*      outputSize,
                        uint32_t       maxOutputSize )
{
	/*if ( _encode_t==nullptr )
	{
		_encode_t = LZ4_createStream();
	}*/

	int returnSize = LZ4_compress_fast( (const char*)input,
	                                    (char*)output,
	                                    inputSize,
	                                    maxOutputSize,
	                                    1 );

	if ( returnSize>0 )
	{
		*outputSize = returnSize;
		return true;
	}

	return false;
}

bool CoreLZ4::decompress( const uint8_t* input,
                          uint8_t*       output,
                          uint32_t       inputSize,
                          uint32_t*      outputSize,
                          uint32_t       maxOutputSize )
{
	/*if ( _decode_t==nullptr )
	{
		_decode_t = LZ4_createStreamDecode();
	}*/

	int returnSize = LZ4_decompress_safe( (const char*)input,
	                                      (char*)output,
	                                      inputSize,
	                                      maxOutputSize );

	if ( returnSize>0 )
	{
		*outputSize = returnSize;
		return true;
	}

	return false;
}
