#include <SFML/Window.hpp>
#include "ToySimpleWindow.hpp"
#include "HandleSystemEvent.hpp"

#define TOY_NO_ERROR_MESSAGE "good"

struct WindowConfig
{
	lua::Str   title      = "ToyBox";
	lua::Int   width      = 800;
	lua::Int   height     = 600;
	lua::Bool  fullscreen = false;
	lua::Bool  visiable   = true;
};

inline static void CopyWindowConfig(WindowConfig *output,const lua::Var &input)
{
	lua::TryCopyVar(output->title,      input>>"title");
	lua::TryCopyVar(output->width,      input>>"width");
	lua::TryCopyVar(output->height,     input>>"height");
	lua::TryCopyVar(output->fullscreen, input>>"fullscreen");
	lua::TryCopyVar(output->visiable,   input>>"visiable");
}

inline static sf::String UTF8ToSfString(std::string str)
{
	return sf::String::fromUtf8( str.begin(), str.end() );
}

ToySimpleWindow::ToySimpleWindow(lua::Var table):_errorMessage(TOY_NO_ERROR_MESSAGE)
{
	try
	{
		WindowConfig   config;

		CopyWindowConfig(&config,table);

		auto  style = sf::Style::Default;

		if ( config.fullscreen )
		{
			style = sf::Style::Fullscreen;
		}

		_window = std::make_shared<sf::Window>(
				sf::VideoMode(config.width, config.height),
				UTF8ToSfString(config.title),
				style,
				sf::ContextSettings(24) );
	}
	catch(std::exception &e)
	{
		_errorMessage = e.what();
	}
}

lua::Bool ToySimpleWindow::good()
{
	if ( _errorMessage==TOY_NO_ERROR_MESSAGE )
	{
		return true;
	}

	return false;
}

lua::Bool ToySimpleWindow::isOpen()
{
	return _window->isOpen();
}

void ToySimpleWindow::handleEvent()
{
	sf::Event   event;

	while ( _window->pollEvent(event) )
	{
		HandleSystemEvent( event, &_functorList, [this](){_window->close();} );
	}
}

void ToySimpleWindow::display()
{
	_window->display();
}

#undef TOY_NO_ERROR_MESSAGE
