#include <toy/Environment.hpp>
#include "ToySimpleWindow.hpp"

static void BindSimpleWindow(lua::State<> *lua)
{
	lua->bindMethod( "handleEvent", &ToySimpleWindow::handleEvent );
	lua->bindMethod( "isOpen",      &ToySimpleWindow::isOpen );
	lua->bindMethod( "display",     &ToySimpleWindow::display );
	lua->bindMethod( "fullscreen",  &ToySimpleWindow::fullscreen );
	lua->bindMethod( "good",        &ToySimpleWindow::good );
	lua->bindMethod( "error",       &ToySimpleWindow::error );

	lua->bindClass1ArgEx<ToySimpleWindow,lua::Var>("createWindow");
}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_window(lua::NativeState L)
{
	lua::State<>    lua(L);

	BindSimpleWindow(&lua);

	return 1;
}
