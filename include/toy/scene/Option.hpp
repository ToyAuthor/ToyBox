
#pragma once

namespace toy{
namespace scene{



enum Option:int
{
	_OPTION_START_OR_BEGIN = 0,

	_IMAGE,
	_LINE,
	_CAMERA,
	_SKYBOX,

	SCREEN,
	SMOKE,
};

template<int I> struct _OptionTemplate{};

inline _OptionTemplate<_IMAGE>         IMAGE()         { return _OptionTemplate<_IMAGE>(); }
inline _OptionTemplate<_LINE>          LINE()          { return _OptionTemplate<_LINE>(); }
inline _OptionTemplate<_CAMERA>        CAMERA()        { return _OptionTemplate<_CAMERA>(); }
inline _OptionTemplate<_SKYBOX>        SKYBOX()        { return _OptionTemplate<_SKYBOX>(); }

typedef _OptionTemplate<_IMAGE>        (*IMAGE_T)();
typedef _OptionTemplate<_LINE>         (*LINE_T)();
typedef _OptionTemplate<_CAMERA>       (*CAMERA_T)();
typedef _OptionTemplate<_SKYBOX>       (*SKYBOX_T)();



}}
