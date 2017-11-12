
#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <SFML/Window.hpp>

// Remove Microsoft macro
#if defined(_WIN32) && defined(CreateWindow)
	#undef CreateWindow
#endif


namespace toy{
namespace example{


inline static auto CreateWindow( std::string title, uint32_t width, uint32_t height )->std::shared_ptr<sf::Window>
{
	sf::ContextSettings  settings(24);

	settings.antialiasingLevel = 8;  // 0,2,4,8

	return std::make_shared<sf::Window>(
			sf::VideoMode(width, height),
			sf::String::fromUtf8(title.begin(),title.end()),
			sf::Style::Default,
			settings );
}


}}
