#include "toy/file/File.hpp"
#include "toy/file/io/Base.hpp"
#include "toy/file/io/Standard.hpp"
#include "toy/file/io/Zlib.hpp"
#include "toy/file/io/Zip7.hpp"


using namespace toy;

File::File(enum Mode mode):mIO(0)
{
	ChangeMode(mode);
}
File::~File()
{
	FreeIO();
}
void File::FreeIO()
{
	if(mIO)
	{
		delete mIO;
		mMode=File::NONE;
		mIO=0;
	}
}
void File::ChangeMode(enum Mode mode)
{
	if(mMode==mode)return;

	FreeIO();
	mMode=mode;

	switch(mode)
	{
		case STD:
			mIO=static_cast<file::io::Base*>(new file::io::Standard);
			break;
		case ZIP7:
			mIO=static_cast<file::io::Base*>(new file::io::Zip7);
			break;
		case ZIP:
			mIO=static_cast<file::io::Base*>(new file::io::Zlib);
			break;
		case NONE:
		default:
			// NONE is not a option.
			Oops(TOY_MARK);
	}
}
bool File::OpenDir(std::string path)
{
	return mIO->OpenDir(path);
}
bool File::Open(std::string filepath)
{
	return mIO->Open(filepath);
}
bool File::Read(void *file,uint32_t size)
{
	return mIO->Read(file,size);
}
bool File::Write(void *file,uint32_t size)
{
	return mIO->Write(file,size);
}
bool File::Seek(enum SeekOption option,int32_t offset)
{
	return mIO->Seek((enum file::io::Base::Option)option,offset);
}
std::string File::GetFileName()
{
	return mIO->GetFileName();
}
bool File::IsEmpty()
{
	return mIO->IsEmpty();
}
void* File::GetFilePointer()
{
	return mIO->GetFilePointer();
}
