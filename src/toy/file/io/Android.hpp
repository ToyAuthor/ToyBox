
#pragma once

#include "toy/file/ArchiveFacade.hpp"

struct AAssetDir;
struct AAsset;

namespace toy{
namespace file{
namespace io{

class Android : public ::toy::file::ArchiveFacade
{
	public:

		Android();
		virtual ~Android(){close();}

		virtual bool    openDir(std::string path);
		virtual void    closeDir();
		virtual bool    open(std::string filepath);
		virtual void    close();
		virtual auto    read(void *file,uint32_t size)->uint32_t;
		virtual bool    write(const void *file,uint32_t size);   // Not finish yet.
		virtual bool    seek(int option,int32_t offset);
		virtual bool    isEnd();
		virtual bool    isEmpty();
		virtual auto    getFileName()->std::string;
		virtual auto    getDirName()->std::string;

	private:

		AAsset*      _file = nullptr;
		AAssetDir*   _dir  = nullptr;
		size_t       _fileSize = 0;
		size_t       _passSize = 0;
};

}}}
