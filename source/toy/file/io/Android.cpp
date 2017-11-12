#include <cstdlib>
#include <cstring>
#include "toy/file/io/Android.hpp"

using namespace toy;
using namespace file;
using namespace io;


#ifdef TOY_ANDROID

#include <SFML/Window.hpp>

#include <android/native_activity.h>
#include <android/asset_manager.h>

// Take a look.
// https://github.com/fabiensanglard/Shmup/blob/master/engine/android/jni/android/android_main.c
// https://developer.android.com/ndk/reference/group___asset.html

Android::Android()
{
	;
}

static AAssetManager* GetAssetManager()
{
	return sf::getNativeActivity()->assetManager;
}

bool Android::openDir(std::string path)
{
	/*
	ANativeActivity     *activity = sf::getNativeActivity();
	AAssetManager       *assetManager = activity->assetManager;
	AAssetDir    *dir = AAssetManager_openDir(assetManager, "ffg");
	const char  *filename = AAssetDir_getNextFileName(dir);
	*/

	this->close();

	_dir = AAssetManager_openDir(GetAssetManager(), path.c_str());

	return 1;
}

bool Android::open(std::string filepath)
{
	AAssetDir_rewind(_dir);

	const char  *filename;

	while ( (filename = AAssetDir_getNextFileName(_dir)) != nullptr )
	{
		if ( filepath==filename )
		{
			_file = AAssetManager_open(GetAssetManager(), filename, AASSET_MODE_BUFFER);
			_fileSize = AAsset_getLength(_file);

			return 1;
		}
	}

	return 0;
}

uint32_t Android::read(void *file,uint32_t size)
{
	if ( _fileSize < size+_passSize )
	{
		size = _fileSize-_passSize;
	}

	AAsset_read(_file, file, size);

	_passSize+=size;

	return 1;
}

bool Android::write(void*,uint32_t)
{
	// Not ready yet
	toy::Oops(TOY_MARK);
	return 1;
}

bool Android::seek(int option,int32_t offset)
{
	if ( isEmpty() ) return 0;

	AAsset_seek(_file, offset, option);

	return 1;
}

void Android::close()
{
	if ( _file )
	{
		AAsset_close(_file);
		_file = nullptr;
	}

	if ( _dir )
	{
		AAssetDir_close(_dir);
		_dir = nullptr;
	}

	_passSize = 0;
}

bool Android::isEnd()
{
	if ( _passSize == _fileSize )
	{
		return 1;
	}

	return 0;
}

bool Android::isEmpty()
{
	if ( _file != nullptr && _dir != nullptr )
	{
		return 0;
	}

	return 1;
}

#else

Android::Android()
{
	(void)_file;
	(void)_dir;
	(void)_fileSize;
	(void)_passSize;
}
bool Android::openDir(std::string)            { return 1; }
bool Android::open(std::string)               { return 1; }
auto Android::read(void*,uint32_t)->uint32_t  { return 1; }
bool Android::write(void*,uint32_t)           { return 1; }
bool Android::isEnd()                         { return 1; }
bool Android::isEmpty()                       { return 1; }
bool Android::seek(int,int32_t)               { return 1; }
void Android::close(){}

#endif//TOY_ANDROID
