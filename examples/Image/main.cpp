/*
 * Load a image file and display it at default position.
 */

#include <toy/Canvas.hpp>
#include <toy/photo/Tools.hpp>
#include <toy_example/File.hpp>
#include <toy_example/sfml/Window.hpp>

static bool HandleEvent( std::shared_ptr<sf::Window> window )
{
	sf::Event event;

	while ( window->pollEvent(event) )
	{
		switch ( event.type )
		{
			case sf::Event::Closed:

				window->close();
				return false;

			case sf::Event::KeyPressed:

				if ( event.key.code == sf::Keyboard::Escape )
				{
					window->close();
					return false;
				}
				break;

			default:
				break;
		}
	}

	return true;
}

static auto CreateImage(std::shared_ptr<toy::canvas::Brush> brush)->std::shared_ptr<toy::canvas::Image>
{
	toy::ImageBuffer   image;

	if ( ! toy::example::LoadImage(std::string(TOY_RESOURCE_PATH),"001.png",&image) )
	{
		toy::Oops(TOY_MARK);
		throw std::runtime_error("Oops");
	}

	toy::photo::UpsideDown(&image);

	auto    texture = brush->newTexture(image);

	return std::make_shared<toy::canvas::Image>(brush,0, 0,image.width(),image.height(),texture);
}

static void SetCamera(std::shared_ptr<toy::canvas::Brush> brush,uint32_t width,uint32_t height)
{
	auto   projection = toy::math::MakeOrtho<float>( width, height, 100, -100);
	auto   modelview  = toy::math::LookAt( toy::math::Vector3<float>( 0.0, 0.0, 3.0 ),
	                                       toy::math::Vector3<float>( 0.0, 0.0, 0.0 ),
	                                       toy::math::Vector3<float>( 0.0, 1.0, 0.0 ) );

	brush->setProjection( projection );
	brush->setModelview( modelview );
}

static void InitScene(std::shared_ptr<toy::canvas::Brush> brush,uint32_t width,uint32_t height)
{
	brush->viewport(width,height);
	brush->setClearColor(0.5, 0.5, 0.5, 0);

	SetCamera(brush,width,height);
}

static void MainLoop( std::shared_ptr<sf::Window>         window,
                      std::shared_ptr<toy::canvas::Brush> brush )
{
	while ( HandleEvent( window ) && window->isOpen() )
	{
		brush->clear();
		brush->render();
		window->display();
	}
}

static int main2()
{
	const uint32_t  width  = 1024;
	const uint32_t  height = 768;

	auto   window = toy::example::CreateWindow("example:Image",width,height);
	auto   brush  = std::make_shared<toy::canvas::Brush>();

	InitScene(brush,width,height);

	auto   image = CreateImage(brush);

	image->visible(true);

	MainLoop(window,brush);

	return EXIT_SUCCESS;
}

int main()
{
	int result = EXIT_FAILURE;

	try
	{
		result = main2();
	}
	catch(std::exception &e)
	{
		toy::Log(e);
	}

	return result;
}
