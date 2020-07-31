#include <toy/Exception.hpp>
#include <toy/ImageBuffer.hpp>
#include <toy/File.hpp>
#include "Image.hpp"

namespace toy{
namespace luamodule{
namespace file{

int ExportPngFile(lua::NativeState L)
{
	lua::Str                        filename;
	lua::Obj<::toy::ImageBuffer>    buffer;

	lua::PullArgs( L, filename, buffer );

	if ( false == ::toy::file::loader::png::Save(filename,buffer.ptr()) )
	{
		throw toy::Exception(TOY_MARK);
	}

	return 0;
}

int ExportBmpFile(lua::NativeState L)
{
	lua::Str                        filename;
	lua::Obj<::toy::ImageBuffer>    buffer;

	lua::PullArgs( L, filename, buffer );

	toy::path::Status   path(filename);

	::toy::File   dev;

	dev.openDir(path.location());
	dev.open(path.name());

	if ( false == ::toy::file::loader::bmp::Save(&dev,static_cast<const ::toy::ImageBuffer*>(buffer.ptr())) )
	{
		throw toy::Exception(TOY_MARK);
	}

	return 0;
}

}}}
