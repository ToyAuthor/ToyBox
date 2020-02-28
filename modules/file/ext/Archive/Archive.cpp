#include <memory>
#include <toy/Environment.hpp>
#include <toy/Oops.hpp>
#include <toy/file/Archiver.hpp>
#include <luapp.hpp>

namespace toy{
namespace luamodule{
namespace archive{

class ArchiverWrapper
{
	public:

		ArchiverWrapper(lua::Str option)
		{
			if ( option=="zip" )
			{
				_core.reset(new toy::file::Archiver(toy::ZIP));
			}
			else if ( option=="7z" )
			{
				_core.reset(new toy::file::Archiver(toy::SEVEN_ZIP));
			}
			else
			{
				toy::Oops(TOY_MARK);
				_core.reset(new toy::file::Archiver(toy::ZIP));
			}
		}

		~ArchiverWrapper(){}

		lua::Bool compress(lua::Str input, lua::Str output)
		{
			return _core->compress(input,output);
		}

		lua::Bool decompress(lua::Str input, lua::Str output)
		{
			return _core->decompress(input,output);
		}

	private:

		std::unique_ptr<toy::file::Archiver>       _core;
};

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_file_archive(lua::NativeState L)
{
	namespace module = ::toy::luamodule::archive;

	lua::State<>    lua(L);

	lua.bindMethod("compress",     &module::ArchiverWrapper::compress);
	lua.bindMethod("decompress",   &module::ArchiverWrapper::decompress);
	lua.bindClass1ArgEx<module::ArchiverWrapper,lua::Str>("new_archiver");

	lua.cleanUnusedResource<module::ArchiverWrapper>();

	return 1;
}
