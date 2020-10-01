#pragma once

#include <memory>
#include <luapp.hpp>

namespace toy{
	namespace io{
		class Stream;
		template<typename T>
		class Reader;
	}
}

class ReaderWrapper
{
	public:

		ReaderWrapper(lua::Str filename);
		~ReaderWrapper();

		void open(lua::Str filename);
		auto nextLine()->lua::Var;
		void drop();

	private:

		auto loadText(lua::Str filename)->lua::Bool;

		std::shared_ptr<toy::io::Reader<toy::io::Stream>>  _reader;
};
