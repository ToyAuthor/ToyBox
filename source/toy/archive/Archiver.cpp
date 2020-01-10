#include "toy/Exception.hpp"
#include "toy/archive/Archiver.hpp"
#include "toy/archive/Workshop.hpp"

namespace toy{
namespace archive{

struct ArchiverPrivate
{
	bool                                   isExist = false;
	toy::archive::Workshop                 dev;
};

}}

using namespace toy;

Archiver::Archiver():_this(new struct ::toy::archive::ArchiverPrivate)
{
	;
}

Archiver::~Archiver()
{
	;
}

void Archiver::init()
{
	//_this->init();
}

void Archiver::drop()
{
	//_this->drop();
}

bool Archiver::compress(const toy::Block &input,const std::string &output)
{
	return _this->dev.compress(input,output);
}

std::shared_ptr<toy::Block> Archiver::decompress(const std::string &input)
{
	return _this->dev.decompress(input);
}

#if TOY_OPTION_ENABLE_BETA_API
bool Archiver::compress( const std::string &input,
                         const std::string &output,
                         const ::toy::archive::Config& config)
{
	return _this->dev.compress(input,output,config);
}

bool Archiver::decompress( const std::string &input,
                           const std::string &output,
                           ::toy::archive::Config *config)
{
	return _this->dev.decompress(input,output,config);
}

std::shared_ptr<::toy::archive::Stream> Archiver::makeStream(const std::string &name) const
{
	(void)name;
	return std::make_shared<::toy::archive::Stream>();
}

::toy::archive::Stream* Archiver::makeStreamRawPtr(const std::string &name) const
{
	(void)name;
	return new ::toy::archive::Stream;
}

//------------------------------------------------------------------------------

#include "toy/io/Stream.hpp"

namespace toy{
namespace archive{

void Compress(const std::string &input,const std::string &output)
{
	toy::io::Stream  streamRead;
	toy::io::Stream  streamWrite;

	if ( false==streamRead.open(input,toy::READ_ONLY) )
	{
		throw toy::Exception(TOY_MARK);
	}

	if ( false==streamWrite.open(output,toy::DEFAULT) )
	{
		throw toy::Exception(TOY_MARK);
	}

	char bufferIn[128];
	char bufferOut[128];

	auto streamPtr = LZ4_createStream();

	uint64_t   readSize = 0;
	uint64_t   compressSize = 0;
	uint8_t    compressSize2 = 0;

	for(;;)
	{
		readSize = streamRead.read(bufferIn,64);

		if (readSize==0)
		{
			break;
		}

		compressSize = LZ4_compress_fast_continue(streamPtr, bufferIn, bufferOut, readSize, 64, 1);
	//	compressSize = LZ4_compress_fast_continue(streamPtr, bufferIn, bufferOut, readSize, LZ4_compressBound(readSize), 1);

		compressSize2 = compressSize;
		streamWrite.write(&compressSize2,1);
		streamWrite.write(bufferOut,compressSize);
	}

	LZ4_freeStream(streamPtr);
}

void Decompress(const std::string &input,const std::string &output)
{
	toy::io::Stream  streamRead;
	toy::io::Stream  streamWrite;

	if ( false==streamRead.open(input,toy::READ_ONLY) )
	{
		throw toy::Exception(TOY_MARK);
	}

	if ( false==streamWrite.open(output,toy::DEFAULT) )
	{
		throw toy::Exception(TOY_MARK);
	}

	char bufferIn[128];
	char bufferOut[128];

	auto streamPtr = LZ4_createStreamDecode();

	uint64_t   readSize = 0;
	uint64_t   compressSize = 0;
	uint8_t    bolckSize = 0;

	for(;;)
	{
		readSize = streamRead.read(&bolckSize,1);

		if (readSize==0)
		{
			break;
		}

		readSize = streamRead.read(bufferIn,bolckSize);

		if (readSize<bolckSize)
		{
			break;
		}

		compressSize = LZ4_decompress_safe_continue(streamPtr, bufferIn, bufferOut, readSize, 64);

		streamWrite.write(bufferOut,compressSize);
	}

	LZ4_freeStreamDecode(streamPtr);
}

}}

#endif
