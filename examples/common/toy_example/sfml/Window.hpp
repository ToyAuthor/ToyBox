
#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <SFML/Window.hpp>
#include <toy/Environment.hpp>
#include <toy/Utf.hpp>

namespace toy{
namespace example{

static inline auto CreateWindow( std::string title, uint32_t width, uint32_t height )->std::shared_ptr<sf::Window>
{
	sf::ContextSettings  settings(24);

	#if defined(TOY_WINDOWS)
		settings.antialiasingLevel = 8;
	#endif

	return std::make_shared<sf::Window>(
			sf::VideoMode(width, height),
			sf::String(toy::utf::UTF8ToWChar( title ).c_str()),
			sf::Style::Default,
			settings );
}

static inline auto CreateWindow( std::wstring title, uint32_t width, uint32_t height )->std::shared_ptr<sf::Window>
{
	sf::ContextSettings  settings(24);

	#if defined(TOY_WINDOWS)
		settings.antialiasingLevel = 8;
	#endif

	return std::make_shared<sf::Window>(
			sf::VideoMode(width, height),
			sf::String(title),
			sf::Style::Default,
			settings );
}

}}
