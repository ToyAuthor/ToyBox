
#pragma once

#include <cstdint>
#include "lz4.h"

namespace toy{
namespace archive{

class CoreLZ4
{
	public:

		CoreLZ4();
		~CoreLZ4();

		bool compress(  const uint8_t *input, uint8_t *output, uint32_t inputSize, uint32_t *outputSize, uint32_t maxOutputSize);
		bool decompress(const uint8_t *input, uint8_t *output, uint32_t inputSize, uint32_t *outputSize, uint32_t maxOutputSize);
		void init();
		void drop();
/*
	private:

		LZ4_stream_t                  *_encode_t = nullptr;
		LZ4_streamDecode_t            *_decode_t = nullptr;*/
};

}}
