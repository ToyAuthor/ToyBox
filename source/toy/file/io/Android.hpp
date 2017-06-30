
#pragma once


#include <cstdio>
#include "toy/file/io/Base.hpp"

struct AAssetDir;
struct AAsset;

namespace toy{
namespace file{
namespace io{


class Android : public Base
{
	public:

		Android();
		virtual ~Android(){close();}

		virtual bool    openDir(std::string path);
		virtual bool    open(std::string filepath);
		virtual auto    read(void *file,uint32_t size)->uint32_t;
		virtual bool    write(void *file,uint32_t size);   // Not finish yet.
		virtual bool    seek(int option,int32_t offset);
		virtual void    close();
		virtual bool    isEnd();
		virtual bool    isEmpty();

	private:

		AAsset*      _file = nullptr;
		AAssetDir*   _dir  = nullptr;
		size_t       _fileSize = 0;
		size_t       _passSize = 0;
};

}}}
