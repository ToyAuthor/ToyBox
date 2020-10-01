#pragma once

#include <memory>
#include <luapp.hpp>

namespace toy{
	namespace io{
		class Stream;
		template<typename T>
		class Writer;
	}
}

class WriterWrapper
{
	public:

		WriterWrapper(lua::Str filename);
		~WriterWrapper();

		void print(lua::Str str);
		void printf(lua::Str str);
		void newLine();
		void drop();

	private:

		auto newText(lua::Str filename)->lua::Bool;

		std::shared_ptr<toy::io::Writer<toy::io::Stream>>   _writer;
};
