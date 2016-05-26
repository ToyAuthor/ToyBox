
#include <toy/Image.hpp>
#include <toy/File.hpp>
#include <toy/file/Loader.hpp>
#include <SFML/Window.hpp>
#include "Render.hpp"


static int LoadImage(std::string file,toy::Image *image)
{
	toy::File       dev;

	if ( ! dev.open(file) )
	{
		toy::Log("Image file not find!\n");
	}
	else if ( ! toy::file::loader::Load(&dev,image) )
	{
		toy::Log("Image load failed!\n");
	}
	else if ( image->getData()==nullptr )
	{
		toy::Log("Image load nothing!\n");
	}
	else
	{
		toy::Log("Image load success!\n");
		return 1;
	}

	return 0;
}

static void HandleEvent(std::shared_ptr<sf::Window> window)
{
	sf::Event event;

	while ( window->pollEvent(event) )
	{
		switch ( event.type )
		{
			case sf::Event::Closed:

				window->close();
				break;

			case sf::Event::KeyPressed:

				if ( event.key.code == sf::Keyboard::Escape )
				{
					window->close();
				}
				break;

			case sf::Event::Resized:

				Render::Resize(event.size.width, event.size.height);
				break;

			default:
				break;
		}
	}
}

static sf::String Utf8ToUtf32(std::string str)
{
	return sf::String::fromUtf8(str.begin(),str.end());
}

static std::shared_ptr<sf::Window> CreateWindowS( std::string titleA, uint32_t width, uint32_t height )
{
	sf::String    titleW = Utf8ToUtf32(titleA);

	auto    window = std::make_shared<sf::Window>(
			sf::VideoMode(width, height),
			titleW.getData(),
			sf::Style::Default,
			sf::ContextSettings(24) );

	return window;
}

int main()
{
	std::string   path(TOY_RESOURCE_PATH);

	toy::Image     image;

	if ( ! LoadImage(path+"/002.png",&image) )
	{
		return EXIT_FAILURE;
	}

	auto    window = CreateWindowS("ToyBox;玩具箱;おもちゃ箱;장난감 상자;खिलौनो का बक्सा",800,600);

	window->setActive();

	Render::AddImage(image);

	while ( window->isOpen() )
	{
		HandleEvent(window);
		Render::DrawImage();
		window->display();
	}

	return EXIT_SUCCESS;
}
