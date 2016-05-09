#include "toy/file/io/Standard.hpp"


using namespace toy;
using namespace file;
using namespace io;

bool Standard::IsEmpty()
{
	if(mFile==0)
		return 1;
	else
		return 0;
}

void Standard::Close()
{
	if(mFile)
	{
		fclose(mFile);
		mFile=0;
		mPath.clear();
	}
}
bool Standard::OpenDir(std::string path)
{
	mPath=path;
	return 1;
}
bool Standard::Open(std::string filepath)
{
	Close();
	mFileName=filepath;
	std::string   path;

	if(mPath.size()==0)
	{
		path=mFileName;
	}
	else
	{
		path=mPath;
		path+=mFileName;
	}

	mFile=fopen(path.c_str(),"rb+");
	if(mFile)
		return 1;
	else
		return 0;
}

bool Standard::Read(void *file,uint32_t size)
{
	#if TOY_OPTION_CHECK
	if(!file)
	{
		Oops(TOY_MARK);
		return 0;
	}
	#endif
	if(IsEmpty())
		return 0;

	size_t	result=fread(file,1,size,mFile);	// "fread(file,size,1,mFile)" was wrong.

	if(result!=size)
	{
		// fread() has wrong
		Oops(TOY_MARK);
		return 0;
	}

	return 1;
}

bool Standard::Write(void *file,uint32_t size)
{
	if(IsEmpty())return 0;
	fwrite(file,(size_t)size,1,mFile);
	return 1;
}

bool Standard::Seek(enum Option option,int32_t offset)
{
	if(IsEmpty())return 0;

	switch (option)
	{
	case Base::SET:
		fseek( mFile, offset, SEEK_SET );
		break;
	case Base::END:
		fseek( mFile, offset, SEEK_END );
		break;
	case Base::CUR:
	default:
		fseek( mFile, offset, SEEK_CUR );
		break;
	}
	return 1;
}
void* Standard::GetFilePointer()
{
	return (void*)mFile;
}
