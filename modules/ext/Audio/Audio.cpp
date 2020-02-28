#include <luapp.hpp>
#include <toy/Exception.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

namespace toy{
namespace luamodule{
namespace audio{

class SoundBuffer
{
	public:

		SoundBuffer(lua::Obj<std::shared_ptr<sf::InputStream>> stream)
		{
			auto  &dd = *(stream.ref().get());

			if ( ! _buffer.loadFromStream(dd) )
			{
				throw toy::Exception(TOY_MARK);
			}
		}

		~SoundBuffer(){}

		sf::SoundBuffer& get()
		{
			return _buffer;
		}

	private:

		sf::SoundBuffer    _buffer;
};

class Sound
{
	public:

		Sound(lua::Obj<audio::SoundBuffer> buffer):_sound(buffer.ref().get())
		{
			;
		}

		~Sound(){}

		void play()
		{
			if ( this->isPaused() || this->isStopped() )
			{
				_sound.play();
			}
		}

		void stop()
		{
			if ( this->isPlaying() )
			{
				_sound.stop();
			}
		}

		void pause()
		{
			if ( this->isPlaying() )
			{
				_sound.pause();
			}
		}

		lua::Bool isPlaying()
		{
			if ( _sound.getStatus() == sf::Music::Playing )
			{
				return true;
			}
			return false;
		}

		lua::Bool isStopped()
		{
			if ( _sound.getStatus() == sf::Music::Stopped )
			{
				return true;
			}
			return false;
		}

		lua::Bool isPaused()
		{
			if ( _sound.getStatus() == sf::Music::Paused )
			{
				return true;
			}
			return false;
		}

	private:

		sf::Sound   _sound;
};

class Music
{
	public:

		Music(lua::Str filename)
		{
			if ( ! _device.openFromFile(filename) )
			{
				throw toy::Exception(TOY_MARK);
			}
		}

		~Music(){}

		void play()
		{
			if ( this->isPaused() || this->isStopped() )
			{
				_device.play();
			}
		}

		void stop()
		{
			if ( this->isPlaying() )
			{
				_device.stop();
			}
		}

		void pause()
		{
			if ( this->isPlaying() )
			{
				_device.pause();
			}
		}

		lua::Bool isPlaying()
		{
			if ( _device.getStatus() == sf::Music::Playing )
			{
				return true;
			}
			return false;
		}

		lua::Bool isStopped()
		{
			if ( _device.getStatus() == sf::Music::Stopped )
			{
				return true;
			}
			return false;
		}

		lua::Bool isPaused()
		{
			if ( _device.getStatus() == sf::Music::Paused )
			{
				return true;
			}
			return false;
		}

	private:

		sf::Music   _device;
};

static int NewSoundBuffer(lua::NativeState L)
{
	//                                                 ... [stream]
	lua::Obj<std::shared_ptr<sf::InputStream>>   stream;
	lua::Str                                     str("_make_sf_stream");

	lua::PushVarToLua( L, str );                    // ... [stream] ["make_stream"]
	lua::GetTable(L,-2);                            // ... [stream] [func]
	lua::PushValue(L,-2);                           // ... [stream] [func] [stream]
	lua::Call(L,1,1);                               // ... [stream] [InputStream]
	lua::CheckVarFromLua(L,&stream,-1);
	lua::Pop(L,2);                                  // ...

	lua::PushClassToLua<SoundBuffer>( L, stream );  // ... [SoundBuffer]

	return 1;
}

}}}

static inline void BindAudioSoundBuffer(lua::State<> *lua)
{
	namespace module = ::toy::luamodule::audio;
	lua->bindClass1ArgEx<module::SoundBuffer,lua::Obj<std::shared_ptr<sf::InputStream>>>("_new_sound_buffer2");
}

static inline void BindAudioSound(lua::State<> *lua)
{
	namespace module = ::toy::luamodule::audio;
	lua->bindMethod("play",       &module::Sound::play);
	lua->bindMethod("stop",       &module::Sound::stop);
	lua->bindMethod("pause",      &module::Sound::pause);
	lua->bindMethod("is_playing", &module::Sound::isPlaying);
	lua->bindMethod("is_stopped", &module::Sound::isStopped);
	lua->bindMethod("is_paused",  &module::Sound::isPaused);
	lua->bindClass1ArgEx<module::Sound,lua::Obj<module::SoundBuffer>>("new_sound");
}

static inline void BindAudioMusic(lua::State<> *lua)
{
	namespace module = ::toy::luamodule::audio;
	lua->bindMethod("play",       &module::Music::play);
	lua->bindMethod("stop",       &module::Music::stop);
	lua->bindMethod("pause",      &module::Music::pause);
	lua->bindMethod("is_playing", &module::Music::isPlaying);
	lua->bindMethod("is_stopped", &module::Music::isStopped);
	lua->bindMethod("is_paused",  &module::Music::isPaused);
	lua->bindClass1ArgEx<module::Music,lua::Str>("new_music");
}

#if defined(_WIN32)
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_audio(lua::NativeState L)
{
	lua::State<>    lua(L);

	BindAudioSoundBuffer(&lua);
	BindAudioSound(&lua);
	BindAudioMusic(&lua);

	namespace module = ::toy::luamodule::audio;
	lua.setFunc( "new_sound_buffer",    module::NewSoundBuffer );

	lua.cleanUnusedResource<module::SoundBuffer>();
	lua.cleanUnusedResource<module::Sound>();
	lua.cleanUnusedResource<module::Music>();

	return 1;
}
