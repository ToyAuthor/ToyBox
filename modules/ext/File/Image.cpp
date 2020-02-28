#include <toy/Exception.hpp>
#include <toy/ImageBuffer.hpp>
#include <toy/file/loader/Png.hpp>
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

}}}
