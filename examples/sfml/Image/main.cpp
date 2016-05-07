
#include <string>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


static std::shared_ptr<sf::Window> CreateWindowS()
{
	sf::ContextSettings      contextSettings;
	contextSettings.depthBits = 24;

	auto    window = std::make_shared<sf::Window>(
		sf::VideoMode(800, 600),
		L"ToyBox;玩具箱;おもちゃ箱;장난감 상자;खिलौनो का बक्सा",
		sf::Style::Default,
		contextSettings);

	return window;
}

static void SetDefaultGL()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
}

static void SetCamera(unsigned int x,unsigned int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat    ratio = static_cast<float>(x) / y;

	glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
	glMatrixMode(GL_MODELVIEW);
}

int main()
{
	auto    window = CreateWindowS();

	window->setActive();

	SetDefaultGL();
	SetCamera(window->getSize().x, window->getSize().y);

	glEnable(GL_TEXTURE_2D);

	while ( window->isOpen() )
	{
		glClear(GL_DEPTH_BUFFER_BIT);

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

					glViewport(0, 0, event.size.width, event.size.height);
					break;

				default:
					break;
			}
		}

		window->display();
	}

	return EXIT_SUCCESS;
}
