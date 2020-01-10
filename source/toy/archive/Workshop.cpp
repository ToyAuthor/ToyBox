#include "toy/Exception.hpp"
#include "toy/archive/Workshop.hpp"
#include "toy/io/Stream.hpp"
#include "toy/math/SafeInt.hpp"
#include "toy/path/Status.hpp"
#include "toy/path/Browser.hpp"
#include "toy/gadget/Endianness.hpp"
#include "toy/gadget/VariableLengthInteger.hpp"
#include "toy/memory/Manager02.hpp"

#define TOY_ARCHIVE_VERSION 1
// Max:32767 (don't bigger than it)
#define TOY_ARCHIVE_BLOCK_SIZE 1024

namespace toy{
namespace archive{

class FileGuard
{
	public:

		FileGuard(const std::string &output):_file(output)
		{
			;
		}

		~FileGuard()
		{
			if ( _oops )
			{
				_file.remove();
			}
		}

		void disable()
		{
			_oops = false;
		}

	private:

		bool                _oops = true;
		toy::path::Status   _file;
};

union MyBitFields
{
	struct
	{
		uint8_t field_1:1;
		uint8_t field_2:1;
		uint8_t field_3:1;
		uint8_t field_4:1;
		uint8_t field_5:1;
		uint8_t field_6:1;
		uint8_t field_7:1;
		uint8_t field_8:1;
	};

	char      ch;
	uint8_t   num;
};

}}

using namespace toy;
using namespace archive;

Workshop::Workshop()
{
	;
}

Workshop::~Workshop()
{
	;
}

static bool WriteConfig(const ::toy::archive::Config& config,toy::io::Stream *target)
{
	archive::MyBitFields    block[3];

	target->rewind();

	block[0].ch = 'T';
	block[1].ch = 'O';
	block[2].ch = 'Y';
	if ( false==target->write(block,3) ) return false;

	block[0].num = 0;
	block[1].num = 0;
	block[2].num = 0;

	block[0].field_6 = 1;

	int level = 1;
	//---------------------------------------------
	if ( config.isSingleFile )
	{
		block[0].field_2 = 1;
	}

	if ( config.isHaveMD5 )
	{
		block[0].field_3 = 1;
	}
	//---------------------------------------------
	if ( config.isMultiVolume )
	{
		level = 2;
		block[0].field_8 = 1;
		block[1].field_3 = 1;
	}
	//---------------------------------------------

	if ( false==target->write(block,level) ) return false;

	return true;
}

static bool ReadConfig(::toy::archive::Config *config,toy::io::Stream *target)
{
	target->rewind();

	{
		std::string  buffer("AAA");

		if ( 3!= target->read(const_cast<char*>(buffer.data()),3) ) return false;
		if ( buffer!="TOY" ) return false;
	}

	archive::MyBitFields    block;

	if ( 1!=target->read(&block,1) ) return false;

	config->isSingleFile = (block.field_2==1)?true:false;
	config->isHaveMD5 = (block.field_3==1)?true:false;

	if ( block.field_8==1 )
	{
		if ( 1!=target->read(&block,1) ) return false;

		config->isMultiVolume = (block.field_3==1)?true:false;

		if ( block.field_8==1 )
		{
			if ( 1!=target->read(&block,1) ) return false;
		}
	}

	return true;
}

static bool WriteVariableNumber(uint64_t number,toy::io::Stream *target)
{
	std::function<bool(uint8_t)>  inputFunc = [target](uint8_t num)->bool
	{
		return target->write(&num,1);
	};

	return toy::gadget::WriteUnsignedVariableLengthInteger(number,inputFunc);
}

static bool ReadVariableNumber(uint64_t *number,toy::io::Stream *target)
{
	std::function<bool(uint8_t*)>  inputFunc = [target](uint8_t *num)->bool
	{
		return (1==target->read(num,1))?true:false;
	};

	return toy::gadget::ReadUnsignedVariableLengthInteger(number,inputFunc);
}

bool Workshop::compress(const toy::Block &input,const std::string &output)
{
	if ( input.size()==0 )
	{
		return false;
	}

	if ( toy::path::IsExist(output) )
	{
		return false;
	}

	toy::archive::Config  config;

	config.isSingleFile = true;

	toy::io::Stream          stream(output);
	toy::archive::FileGuard  guard(output);

	if ( false==WriteConfig(config,&stream) ) return false;

	WriteVariableNumber(TOY_ARCHIVE_VERSION,&stream);
	WriteVariableNumber(0,&stream);

	uint8_t    buffer[LZ4_COMPRESSBOUND(TOY_ARCHIVE_BLOCK_SIZE)+2];
	uint32_t   outsize = 0;
	uint32_t   insizeSum = input.size();
	uint32_t   insize = 0;
	int16_t    outsize2 = 0;

	const uint8_t *ptr = input.cdata();

	_core.drop();

	while ( insizeSum!=0 )
	{
		if ( insizeSum<TOY_ARCHIVE_BLOCK_SIZE )
		{
			insize = insizeSum;
			insizeSum = 0;

		}
		else
		{
			insize = TOY_ARCHIVE_BLOCK_SIZE;
			insizeSum = insizeSum-TOY_ARCHIVE_BLOCK_SIZE;
		}

		if ( false==_core.compress(ptr,&(buffer[2]),insize,&outsize,LZ4_COMPRESSBOUND(TOY_ARCHIVE_BLOCK_SIZE)) )
		{
			return false;
		}

		ptr += insize;

		outsize2 = toy::math::SafeInt<int16_t>(outsize,TOY_MARK);

		if ( insizeSum!=0 )
		{
			outsize2 *= -1;
		}

		toy::gadget::LittleEndian(&outsize2);
		std::memcpy(buffer,&outsize2,2);

		if ( false==stream.write(buffer,outsize+2) )
		{
			return false;
		}
	}

	_core.drop();
	guard.disable();

	return true;
}

std::shared_ptr<toy::Block> Workshop::decompress(const std::string &input)
{
	toy::io::Stream          stream;

	if ( false==stream.open(input,toy::READ_ONLY) )
	{
		return nullptr;
	}

	toy::archive::Config  config;

	if ( false==ReadConfig(&config,&stream) ) return nullptr;

	if ( false==config.isSingleFile )
	{
		return nullptr;
	}

	{
		uint64_t  versionNum = 0;
		if ( false==ReadVariableNumber(&versionNum,&stream) ) return nullptr;
		if ( versionNum!=TOY_ARCHIVE_VERSION ) return nullptr;
	}

	if ( config.isHaveMD5 )
	{
		uint8_t  buffer[16];

		if ( 16!=stream.read(buffer,16) ) return nullptr;
	}

	uint64_t   fileNameSize = 0;

	if ( false==ReadVariableNumber(&fileNameSize,&stream) ) return nullptr;

	stream.seek(SEEK_CUR,fileNameSize);

	int16_t  blockSize = 0;
	uint8_t  bufferZip[LZ4_COMPRESSBOUND(TOY_ARCHIVE_BLOCK_SIZE)];
	uint8_t  bufferUnzip[LZ4_COMPRESSBOUND(TOY_ARCHIVE_BLOCK_SIZE)];
	uint32_t outputSize = 0;
	uint32_t sumOutputSize = 0;

	toy::memory::Manager02  sumBuffer;

	_core.drop();

	for ( int quit=0 ; quit==0 ; )
	{
		if ( 2!=stream.read(&blockSize,2) ) return nullptr;

		toy::gadget::LittleEndianToCorrect(&blockSize);

		if ( blockSize<0 )
		{
			blockSize *= -1;
		}
		else
		{
			quit++;
		}

		if ( static_cast<uint32_t>(blockSize)!=stream.read(bufferZip,blockSize) ) return nullptr;
		if ( false==_core.decompress(bufferZip, bufferUnzip, blockSize, &outputSize, LZ4_COMPRESSBOUND(TOY_ARCHIVE_BLOCK_SIZE)) ) return nullptr;

		uint32_t temp = sumOutputSize;
		sumOutputSize += outputSize;
		sumBuffer.size(sumOutputSize);
		std::memcpy(((uint8_t*)(sumBuffer.data()))+temp,bufferUnzip,outputSize);
	}

	_core.drop();

	auto result = toy::MarkBlock(sumOutputSize);

	std::memcpy(result->data(),sumBuffer.data(),sumOutputSize);

	return result;
}

static void VisitFolderFunc( const std::string&        dir,
                             std::vector<std::string>& list,
                             std::string               folderName1,
                             std::string&              folderName2,
                             toy::path::Status&        status )
{
	toy::path::Browser   folder(dir);

	bool isEmptyFolder = true;

	for ( auto it = folder.begin() ; it.next() ; )
	{
		const std::string & temp = it.get();

		std::string   currentName = folderName1+temp;

		status = currentName;

	//	toy::Logger<<"Currect file:"<<currentName<<toy::NewLine;

		if ( status.isDirectory() )
		{
			std::string  folderN2 = folderName2;
			folderName2 = folderN2+temp+"/";

			VisitFolderFunc(currentName,list,currentName+"/",folderName2,status);
			isEmptyFolder = false;
		}
		else if ( status.isFile() )
		{
			list.push_back(folderName2+temp);
			folderName2 = "";
			isEmptyFolder = false;
		}
		else
		{
			toy::Logger<<"Something can't compress:"<<currentName<<toy::NewLine;
		}
	}

	if ( isEmptyFolder )
	{
		list.push_back(folderName2);
	}
	else
	{
		folderName2 = std::string("/")+folderName2;
	}
}

static void VisitFolder( const std::string&        input,
                         std::vector<std::string>* list,
                         std::string*              folderName,
                         toy::path::Status*        status )
{
	VisitFolderFunc(input,*list,input+"/",*folderName,*status);
}

bool Workshop::compress( const std::string &input,
                         const std::string &output,
                         const ::toy::archive::Config& config)
{
	if ( toy::path::IsEmptyFolder(input) )
	{
		return false;
	}

	if ( ! toy::path::IsFolder(input) )
	{
		return false;
	}

	toy::io::Stream   target;

	if ( target.open(output) )
	{
		WriteConfig(config,&target);
	}
	else
	{
		return false;
	}

	std::vector<std::string>   fileList;

	{
		std::string                folderName = "";
		toy::path::Status          status("/");

		VisitFolder(input,&fileList,&folderName,&status);
	}

	std::string       fileListBuffer;
	std::string       fileName = input + "/";

	for ( auto &cc : fileList )
	{
		fileName = input + "/" + cc;
		fileListBuffer += cc;
	}

	uint32_t   fileNameListSize = toy::math::SafeInt<uint32_t>(fileListBuffer.size(),TOY_MARK);

	toy::gadget::LittleEndian(&fileNameListSize);

	return true;
}

bool Workshop::decompress( const std::string &input,
                           const std::string &output,
                           ::toy::archive::Config *config)
{
	(void)input;
	(void)output;
	(void)config;
	return false;
}

void Workshop::init()
{
	;
}

void Workshop::drop()
{
	;
}
