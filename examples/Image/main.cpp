/*
 * Load a image file and display it at default position.
 */

#include <toy/Graph.hpp>
#include <toy/Scene.hpp>
#include <toy_example/File.hpp>
#include <toy_example/sfml/Window.hpp>

static void HandleEvent( std::shared_ptr<sf::Window> window )
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

			default:
				break;
		}
	}
}

static auto CreateImage(std::shared_ptr<toy::Scene> scene)->std::shared_ptr<toy::scene::object::Image>
{
	toy::ImageBuffer   image;

	if ( ! toy::example::LoadImage(std::string(TOY_RESOURCE_PATH),"001.png",&image) )
	{
		toy::Oops(TOY_MARK);
		throw std::runtime_error("Oops");
	}

	return scene->newObject(toy::scene::IMAGE,image);
}

static void SetCamera(std::shared_ptr<toy::Scene> scene,uint32_t width,uint32_t height)
{
	toy::scene::CameraConfig   camera;

	camera.ortho( width, height, 100, -100);

	camera.lookat( toy::math::Vector3<float>( 0, 0, 3 ),
	               toy::math::Vector3<float>( 0, 0, 0 ),
	               toy::math::Vector3<float>( 0, 1, 0 ) );

	scene->setCamera( camera );
}

static void InitScene(std::shared_ptr<toy::Scene> scene,uint32_t width,uint32_t height)
{
	auto   brush = scene->brush();

	brush->viewport(0,0,width,height);
	brush->setClearColor(0.5, 0.5, 0.5, 0);

	SetCamera(scene,width,height);
}

static void MainLoop( std::shared_ptr<sf::Window> window,
                      std::shared_ptr<toy::Scene> scene )
{
	auto   brush = scene->brush();

	while ( window->isOpen() )
	{
		HandleEvent( window );

		brush->clear();
		brush->sorting();
		brush->render();
		window->display();
	}
}

static int main2()
{
	const uint32_t  width  = 1024;
	const uint32_t  height = 768;

	auto   window = toy::example::CreateWindow("example:Image",width,height);
	auto   scene  = std::make_shared<toy::Scene>();

	InitScene(scene,width,height);

	auto   image = CreateImage(scene);

	image->visible(true);

	MainLoop(window,scene);

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
