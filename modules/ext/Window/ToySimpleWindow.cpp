#ifdef _MSC_VER
#include <iterator>    // For std::back_inserter
#endif

#include <SFML/Window.hpp>
#include "ToySimpleWindow.hpp"
#include "HandleSystemEvent.hpp"

struct WindowConfig
{
	lua::Str   title      = "ToyBox";
	lua::Int   width      = 800;
	lua::Int   height     = 600;
	lua::Bool  fullscreen = false;
	lua::Bool  visiable   = true;
};

static inline void CopyWindowConfig(WindowConfig *output,const lua::Var &input)
{
	lua::TryCopyVar(output->title,      input>>"title");
	lua::TryCopyVar(output->width,      input>>"width");
	lua::TryCopyVar(output->height,     input>>"height");
	lua::TryCopyVar(output->fullscreen, input>>"fullscreen");
	lua::TryCopyVar(output->visiable,   input>>"visiable");
}

static inline sf::String UTF8ToSfString(std::string str)
{
	return sf::String::fromUtf8( str.begin(), str.end() );
}

ToySimpleWindow::ToySimpleWindow(lua::Var table)
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

lua::Bool ToySimpleWindow::isOpen()
{
	return _window->isOpen();
}

lua::Bool ToySimpleWindow::handleEvent()
{
	sf::Event   event;

	while ( _window->pollEvent(event) )
	{
		if ( ! HandleSystemEvent( event, &_functorList, [this](){_window->close();} ) )
		{
			return false;
		}
	}

	return true;
}

void ToySimpleWindow::display()
{
	_window->display();
}

#undef TOY_NO_ERROR_MESSAGE
