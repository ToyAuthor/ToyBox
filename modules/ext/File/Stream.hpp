
#pragma once

#include <memory>
#include <luapp.hpp>
#include <SFML/System.hpp>
#include <toy/File.hpp>

namespace toy{
	class File;
	class ImageBuffer;
}

namespace toy{
namespace luamodule{
namespace file{

class FileStream : public sf::InputStream
{
	public:

		FileStream(std::shared_ptr<toy::File> file):_file(file){};
		~FileStream(){}

		virtual sf::Int64 read(void* data, sf::Int64 size)
		{
			return _file->read(data,size);
		}

		virtual sf::Int64 seek(sf::Int64 position)
		{
			_position = position;
			_file->seek(SEEK_SET, position);

			// It's not a good idea, but I don't have better one.
			return _position;
		}

		virtual sf::Int64 tell()
		{
			return _position;  // This index not always correct. I can't help!
		}

		virtual sf::Int64 getSize()
		{
			/*
			 * Very bad idea.
			 * But I can't get the correct file size all the time.
			 * So ...
			 */
			//toy::Oops(TOY_MARK);
			return 0;
		}

	private:

		sf::Int64                    _position;
		std::shared_ptr<toy::File>   _file;
};

class Stream
{
	public:

		Stream(lua::Var var);
		~Stream();

		void openDir(lua::Str path);
		void open(lua::Str filename);
		void close();
		void closeDir();
	//	auto read(lua::Ptr file,lua::Int size)->lua::Int;
		void loadImage(lua::Obj<toy::ImageBuffer>);
		auto makeImage()->lua::Obj<toy::ImageBuffer>;
		auto makeStream()->lua::Obj<std::shared_ptr<sf::InputStream>>;
		auto core()->lua::Obj<std::shared_ptr<toy::File>>;

	private:

		std::shared_ptr<toy::File>   _file;
};

}}}
