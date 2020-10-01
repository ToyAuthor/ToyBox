#include <luapp.hpp>
#include <toy/Environment.hpp>
#include "ReaderWrapper.hpp"
#include "WriterWrapper.hpp"

static void BindReaderWrapper(lua::State<> *lua)
{
	lua->bindMethod( "next_line",   &ReaderWrapper::nextLine );
	lua->bindMethod( "open",        &ReaderWrapper::open );
	lua->bindMethod( "__close",     &ReaderWrapper::drop );

	lua->bindClass1ArgEx<ReaderWrapper,lua::Str>("new_reader");
}

static void BindWriterWrapper(lua::State<> *lua)
{
	lua->bindMethod( "new_line",    &WriterWrapper::newLine );
	lua->bindMethod( "print",       &WriterWrapper::print );
	lua->bindMethod( "printf",      &WriterWrapper::printf );
	lua->bindMethod( "__close",     &WriterWrapper::drop );

	lua->bindClass1ArgEx<WriterWrapper,lua::Str>("new_writer");
}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_txtio(lua::NativeState L)
{
	lua::State<>    lua(L);

	BindReaderWrapper(&lua);
	BindWriterWrapper(&lua);

	lua.cleanUnusedResource<ReaderWrapper>();
	lua.cleanUnusedResource<WriterWrapper>();

	return 1;
}
