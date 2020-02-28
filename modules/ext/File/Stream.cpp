#include <toy/File.hpp>
#include <toy/ImageBuffer.hpp>
#include <toy/file/Loader.hpp>
#include "Stream.hpp"

using ::toy::luamodule::file::Stream;

Stream::Stream(lua::Var var)
{
	lua::Str  mode;

	lua::CopyVar(mode,var);

	if ( mode=="default" )
	{
		_file = std::make_shared<toy::File>(toy::DIRECTORY);
	}
	else if ( mode=="zip" )
	{
		_file = std::make_shared<toy::File>(toy::ZIP);
	}
	else if ( mode=="7zip" )
	{
		_file = std::make_shared<toy::File>(toy::SEVEN_ZIP);
	}
	else
	{
		// Get a bad data from lua side.
		toy::Oops(TOY_MARK);
		_file = std::make_shared<toy::File>(toy::DIRECTORY);
	}
}

Stream::~Stream()
{
	;
}

void Stream::openDir(lua::Str path)
{
	if ( ! _file->openDir(path) )
	{
		throw toy::Exception(TOY_MARK);
	}
}

void Stream::open(lua::Str filename)
{
	if ( ! _file->open(filename) )
	{
		throw toy::Exception(TOY_MARK);
	}
}

void Stream::closeDir()
{
	_file->closeDir();
}

void Stream::close()
{
	_file->close();
}

void Stream::loadImage(lua::Obj<toy::ImageBuffer> image)
{
	if ( ! toy::file::loader::Load( _file.get(), image.ptr() ) )
	{
		throw toy::Exception(TOY_MARK);
	}
}

auto Stream::makeImage()->lua::Obj<toy::ImageBuffer>
{
	lua::Obj<toy::ImageBuffer>   image(new toy::ImageBuffer);

	if ( ! toy::file::loader::Load( _file.get(), image.ptr() ) )
	{
		throw toy::Exception(TOY_MARK);
	}

	return image;
}

auto Stream::makeStream()->lua::Obj<std::shared_ptr<sf::InputStream>>
{
	return lua::Obj<std::shared_ptr<sf::InputStream>>(new std::shared_ptr<sf::InputStream>(std::make_shared<luamodule::file::FileStream>(_file)));
}

auto Stream::core()->lua::Obj<std::shared_ptr<toy::File>>
{
	return lua::Obj<std::shared_ptr<toy::File>>(new std::shared_ptr<toy::File>(_file));
}
