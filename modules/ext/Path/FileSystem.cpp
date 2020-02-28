/*
 * Remove file,copy file,create folder, etc.(base on boost.filesystem)
 */

#include <luapp.hpp>
#include <toy/Standard.hpp>
#include <toy/Exception.hpp>
#include <toy/math/SafeInt.hpp>

namespace toy{
namespace luamodule{
namespace path{

class StackGuard
{
	public:

		StackGuard(lua::NativeState h,int stackSize):_size(stackSize),_handle(h)
		{
			;
		}

		~StackGuard()
		{
			lua::Pop(_handle,_size);
		}

		void add(int num)
		{
			_size += num;
		}

		void del(int num)
		{
			if ( num>_size )
			{
				toy::Oops(TOY_MARK);
				num = _size;
			}

			_size -= num;
		}

	private:

		int               _size;
		lua::NativeState  _handle;
};

#ifdef TOY_WINDOWS
	static inline std::wstring LuaToPath(std::string str)
	{
		return toy::utf::UTF8ToWChar(str);
	}

	static inline std::string PathToLua(boost::filesystem::path str)
	{
		return toy::utf::WCharToUTF8(str.wstring());
	}
#else
	static inline std::string LuaToPath(std::string str)
	{
		return str;
	}

	static inline std::string PathToLua(boost::filesystem::path str)
	{
		return str.string();
	}
#endif

class SystemPath
{
	public:

		SystemPath(lua::Str str)
		{
			_path = LuaToPath(str);
		}

		~SystemPath(){}

		lua::Str str()
		{
			return PathToLua(_path);
		}

		void strcat(lua::Str str)
		{
			_path = _path/LuaToPath(str);
		}

		lua::Str parent()
		{
			return PathToLua(_path.parent_path());
		}

		lua::Str filename()
		{
			return PathToLua(_path.filename());
		}

		lua::Str stem()
		{
			return PathToLua(_path.stem());
		}

		lua::Str extension()
		{
			return PathToLua(_path.extension());
		}

	private:

		boost::filesystem::path   _path;
};

static int Remove(lua::NativeState L)
{
	lua::Str    filename;
	lua::PullArgs( L, filename );
	boost::filesystem::remove_all( LuaToPath(filename) );

	return 0;
}

static int Rename(lua::NativeState L)
{
	lua::Str    old_p_str;
	lua::Str    new_p_str;

	lua::PullArgs( L, old_p_str, new_p_str );

	auto   old_p = LuaToPath(old_p_str);
	auto   new_p = LuaToPath(new_p_str);

	boost::filesystem::rename( old_p, new_p );

	return 0;
}

static int Exists(lua::NativeState L)
{
	lua::Bool   isExist = false;
	lua::Str    filename;

	lua::PullArgs( L, filename );
	isExist = boost::filesystem::exists( LuaToPath(filename) );

	lua::PushVarToLua( L, isExist );

	return 1;
}

static int GetCurrentPath(lua::NativeState L)
{
	lua::Str    str = "none";

	str = PathToLua(boost::filesystem::current_path());

	lua::PushVarToLua( L, str );

	return 1;
}

static int CreateDirectories(lua::NativeState L)
{
	lua::Str    path;
	lua::Bool   result = false;

	try
	{
		lua::PullArgs( L, path );
		result = boost::filesystem::create_directories(LuaToPath(path));
	}
	catch ( std::exception &e )
	{
		lua::PushVarToLua( L, result );
		toy::Logger<<toy::NewLine<<"Failed to create this folder:"<<path<<toy::NewLine;
		toy::Oops(TOY_MARK);
		throw;
	}

	lua::PushVarToLua( L, result );

	return 1;
}

static int IsFile(lua::NativeState L)
{
	lua::Bool   isFile = false;
	lua::Str    path;

	lua::PullArgs( L, path );
	isFile = boost::filesystem::is_regular_file(LuaToPath(path));

	lua::PushVarToLua( L, isFile );

	return 1;
}

static int IsFolder(lua::NativeState L)
{
	lua::Bool   isFolder = false;
	lua::Str    path;

	lua::PullArgs( L, path );
	isFolder = boost::filesystem::is_directory(LuaToPath(path));

	lua::PushVarToLua( L, isFolder );

	return 1;
}

static int VisitFolder(lua::NativeState L)
{
	if ( ! lua::IsType<lua::Func>(L,-1) )
	{
		throw toy::Exception(TOY_MARK);
	}

	{
		StackGuard   stackGuard(L,2);

		namespace boost_fs = boost::filesystem;

		lua::Str    path;
		lua::CheckVarFromLua(L,&path,-2);

		for ( auto it = boost_fs::directory_iterator(LuaToPath(path)) ; it != boost_fs::directory_iterator() ; it++ )
		{
			lua::PushValue(L,-1);   stackGuard.add(1);

			lua::Str    name = PathToLua(it->path().filename());  // File name only

			lua::PushVarToLua( L, name );   stackGuard.add(1);
			lua::PCall(L,1,0,0);
			stackGuard.del(2);
		}
	}

	return 0;
}

static int VisitFolderWithPath(lua::NativeState L)
{
	if ( ! lua::IsType<lua::Func>(L,-1) )
	{
		throw toy::Exception(TOY_MARK);
	}

	{
		StackGuard   stackGuard(L,2);

		namespace boost_fs = boost::filesystem;

		lua::Str    path;

		lua::CheckVarFromLua(L,&path,-2);

		for ( auto it = boost_fs::directory_iterator(LuaToPath(path)) ; it != boost_fs::directory_iterator() ; it++ )
		{
			lua::PushValue(L,-1);    stackGuard.add(1);

			lua::Str    name = PathToLua(it->path());   // Path and file name.

			lua::PushVarToLua( L, name );   stackGuard.add(1);
			lua::PCall(L,1,0,0);
			stackGuard.del(2);
		}
	}

	return 0;
}

static int CopyFile(lua::NativeState L)
{
	lua::Str    sourceStr;
	lua::Str    targetStr;
	lua::PullArgs( L, sourceStr, targetStr );

	boost::filesystem::path   target(LuaToPath(targetStr));
	auto                      targetParent = target.parent_path();

	if ( boost::filesystem::exists(targetParent) )
	{
		if ( boost::filesystem::is_regular_file(targetParent) || ! boost::filesystem::is_directory(targetParent) )
		{
			boost::filesystem::remove_all( targetParent );
			boost::filesystem::create_directories(targetParent);
		}
	}
	else
	{
		boost::filesystem::create_directories(targetParent);
	}

	boost::filesystem::copy_file( LuaToPath(sourceStr), target, boost::filesystem::copy_option::overwrite_if_exists );

	return 0;
}

/* It just only able to copy an empty directory.
static int CopyFolder(lua::NativeState L)
{
	lua::Str    file;
	lua::Str    path;
	lua::PullArgs( L, file, path );

	boost::filesystem::copy_directory( LuaToPath(file), LuaToPath(path) );

	return 0;
}*/

static void CopyFolder(boost::filesystem::path src,boost::filesystem::path trg)
{
	namespace boost_fs = boost::filesystem;

	boost_fs::path  name = "Not even create a directory";

	boost_fs::create_directories(trg);

	for ( auto it = boost_fs::directory_iterator(src) ; it != boost_fs::directory_iterator() ; it++ )
	{
		name = it->path();

		if ( boost_fs::is_directory(name) )
		{
			boost_fs::create_directories(trg);
			CopyFolder(name,trg/name.filename());
		}
		else
		{
			boost_fs::copy_file(name,trg/name.filename(),boost_fs::copy_option::overwrite_if_exists);
		}
	}
};

static int CopyFolder(lua::NativeState L)
{
	lua::Str    file;
	lua::Str    path;
	lua::PullArgs( L, file, path );

	boost::filesystem::path   source = LuaToPath(file);
	boost::filesystem::path   target = LuaToPath(path);

	// "target" must be a directory that already exist.
	CopyFolder(source,target);

	return 0;
}

static lua::Bool IsFolderHasChild(const lua::Str &path)
{
	if ( ! boost::filesystem::is_directory(path) )
	{
		return false;
	}

	boost::filesystem::directory_iterator    endIt;
	boost::filesystem::directory_iterator    it(path);

	if ( it == endIt )
	{
		return false;
	}

	return true;
}

static int IsFolderHasChild(lua::NativeState L)
{
	lua::Str    path;
	lua::PullArgs( L, path );
	lua::PushVarToLua( L, IsFolderHasChild(path) );

	return 1;
}

static lua::Bool IsEmptyFolder(const lua::Str &path)
{
	if ( ! boost::filesystem::is_directory(path) )
	{
		return false;
	}

	boost::filesystem::directory_iterator    endIt;
	boost::filesystem::directory_iterator    it(path);

	if ( it == endIt )
	{
		return true;
	}

	return false;
}

static int IsEmptyFolder(lua::NativeState L)
{
	lua::Str    path;
	lua::PullArgs( L, path );
	lua::PushVarToLua( L, IsEmptyFolder(path) );

	return 1;
}

static int GetFileSize(lua::NativeState L)
{
	lua::Str    path;
	lua::PullArgs( L, path );

	lua::PushVarToLua( L, toy::math::SafeInt<lua::Int>(boost::filesystem::file_size(path),TOY_MARK) );

	return 1;
}

static int OpenFolder(lua::NativeState L)
{
	lua::Str    path;
	lua::Bool   result = true;
	lua::PullArgs( L, path );

	result = toy::path::OpenFolder(path);

	lua::PushVarToLua( L, result );

	return 1;
}

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_path(lua::NativeState L)
{
	namespace module = ::toy::luamodule::path;

	lua::State<>    lua(L);

	lua.setFunc( "remove",                             module::Remove );
	lua.setFunc( "rename",                             module::Rename );
	lua.setFunc( "exists",                             module::Exists );
	lua.setFunc( "get_file_size",                      module::GetFileSize );
	lua.setFunc( "get_current_path",                   module::GetCurrentPath );
	lua.setFunc( "build_folder",                       module::CreateDirectories );
	lua.setFunc( "is_file",                            module::IsFile );
	lua.setFunc( "is_folder",                          module::IsFolder );
	lua.setFunc( "copy_file",                          module::CopyFile );
	lua.setFunc( "copy_folder",                        module::CopyFolder );
	lua.setFunc( "is_folder_has_child",                module::IsFolderHasChild );
	lua.setFunc( "is_empty_folder",                    module::IsEmptyFolder );
	lua.setFunc( "visit_folder",                       module::VisitFolder );
	lua.setFunc( "visit_folder_with_path",             module::VisitFolderWithPath );
	lua.setFunc( "open_folder",                        module::OpenFolder );

	lua.bindMethod( "str",             &module::SystemPath::str );
	lua.bindMethod( "strcat",          &module::SystemPath::strcat );
	lua.bindMethod( "parent",          &module::SystemPath::parent );
	lua.bindMethod( "filename",        &module::SystemPath::filename );
	lua.bindMethod( "stem",            &module::SystemPath::stem );
	lua.bindMethod( "extension",       &module::SystemPath::extension );

	lua.bindClass1ArgEx<module::SystemPath,lua::Str>("create_path");

	lua.cleanUnusedResource<module::SystemPath>();

	return 1;
}
