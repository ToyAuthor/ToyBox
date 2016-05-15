
#include "toy/File.hpp"
#include "toy/Image.hpp"
#include "toy/file/loader/Png.hpp"
#include "toy/graph/OpenGL.hpp"
#include <SFML/Window.hpp>


static int LoadImage(std::string file,toy::Image *image)
{
	toy::File       dev;

	if(!dev.open(file))
	{
		toy::Log("Image file not find!\n");
		return 0;
	}

	if(!toy::file::loader::Png::Load(&dev,image))
	{
		toy::Log("Image load failed!\n");
	}

	if( image->getData() )
	{
		toy::Log("Image load success!\n");
	}
	else
	{
		toy::Log("Image load nothing!\n");
		return 0;
	}

	return 1;
}

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

int main()
{
	std::string   path(TOY_RESOURCE_PATH);

	toy::Image     image;
	LoadImage(path+"/002.png",&image);

	auto    window = CreateWindowS();

	window->setActive();


	glTexImage2D(GL_TEXTURE_2D,0,3,image.getWidth(),image.getHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.getData());
	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	float   rate;
	glViewport( 0, 0, 800, 600);
	rate = (float)800/(float)600;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45, rate, 1.0, 500.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glClearColor( 1.0, 1.0, 1.0, 1.0 );

	while ( window->isOpen() )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode (GL_BACK, GL_LINE);

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

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt( 0, 0, 30.0, 0, 0, 0, 0, 1, 0);
	//	glTranslatef( 0, 0, distance);
	//	glRotatef( (float)rot_y + (float)record_y, 1.0, 0.0, 0.0);
	//	glRotatef( (float)rot_x + (float)record_x, 0.0, 1.0, 0.0);

		glBegin(GL_QUADS);
		glNormal3f(0,0,1);
			glTexCoord2f(0,1);glVertex3f(-11, 11,0);
			glTexCoord2f(0,0);glVertex3f(-11,-11,0);
			glTexCoord2f(1,0);glVertex3f( 11,-11,0);
			glTexCoord2f(1,1);glVertex3f( 11, 11,0);
		glEnd();

		window->display();
	}

	return EXIT_SUCCESS;
}
