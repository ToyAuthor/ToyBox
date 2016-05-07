
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>


static const GLfloat g_cube[] =
{
	-20, -20, -20,  0, 0,
	-20,  20, -20,  1, 0,
	-20, -20,  20,  0, 1,
	-20, -20,  20,  0, 1,
	-20,  20, -20,  1, 0,
	-20,  20,  20,  1, 1,

	 20, -20, -20,  0, 0,
	 20,  20, -20,  1, 0,
	 20, -20,  20,  0, 1,
	 20, -20,  20,  0, 1,
	 20,  20, -20,  1, 0,
	 20,  20,  20,  1, 1,

	-20, -20, -20,  0, 0,
	 20, -20, -20,  1, 0,
	-20, -20,  20,  0, 1,
	-20, -20,  20,  0, 1,
	 20, -20, -20,  1, 0,
	 20, -20,  20,  1, 1,

	-20,  20, -20,  0, 0,
	 20,  20, -20,  1, 0,
	-20,  20,  20,  0, 1,
	-20,  20,  20,  0, 1,
	 20,  20, -20,  1, 0,
	 20,  20,  20,  1, 1,

	-20, -20, -20,  0, 0,
	 20, -20, -20,  1, 0,
	-20,  20, -20,  0, 1,
	-20,  20, -20,  0, 1,
	 20, -20, -20,  1, 0,
	 20,  20, -20,  1, 1,

	-20, -20,  20,  0, 0,
	 20, -20,  20,  1, 0,
	-20,  20,  20,  0, 1,
	-20,  20,  20,  0, 1,
	 20, -20,  20,  1, 0,
	 20,  20,  20,  1, 1
};

class Cube
{
	public:

		Cube(){}
		~Cube(){}

		void set_vertex()
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), g_cube);
			glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), g_cube + 3);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
		}

		void follow_cursor(std::shared_ptr<sf::RenderWindow> window)
		{
			float x =  sf::Mouse::getPosition(*window).x * 200.0f / window->getSize().x - 100.0f;
			float y = -sf::Mouse::getPosition(*window).y * 200.0f / window->getSize().y + 100.0f;

			glLoadIdentity();
			glTranslatef(x, y, -100.f);
			glRotatef(clock.getElapsedTime().asSeconds() * 50.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(clock.getElapsedTime().asSeconds() * 30.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(clock.getElapsedTime().asSeconds() * 90.0f, 0.0f, 0.0f, 1.0f);
		}

		void render()
		{
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

	private:

		sf::Clock   clock;
};

static std::shared_ptr<sf::RenderWindow> CreateWindowS()
{
	sf::ContextSettings      contextSettings;
	contextSettings.depthBits = 24;

	auto window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(800, 600),
		L"SFML 範例",
		sf::Style::Default,
		contextSettings);

	window->setVerticalSyncEnabled(true);

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

static GLuint GenTextures(std::string filename)
{
	GLuint    texture;
	sf::Image image;

	if ( ! image.loadFromFile(filename) )
	{
		return 0;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return texture;
}

template<typename T>
static void DrawStuff(std::shared_ptr<sf::RenderWindow> window,T &stuff)
{
	window->pushGLStates();
	window->draw(stuff);
	window->popGLStates();
}

int main()
{
	std::string   my_path(TOY_RESOURCE_PATH);

	auto          window = CreateWindowS();

	sf::Texture   backgroundTexture;

	if ( ! backgroundTexture.loadFromFile(my_path+"/001.png") )
	{
		return EXIT_FAILURE;
	}

	sf::Sprite    background(backgroundTexture);

	sf::Font      font;

	if (!font.loadFromFile(my_path+"/font/unifont-8.0.01.ttf"))
	{
		return EXIT_FAILURE;
	}

	sf::Text      text(L"Hello;哈囉;こんにちは;안녕하세요;नमस्ते", font);

	text.setPosition(50.0f, 450.0f);

	window->setActive();

	auto          texture = GenTextures(my_path+"/002.png");

	if ( texture==0 )
	{
		return EXIT_FAILURE;
	}

	SetDefaultGL();
	SetCamera(window->getSize().x, window->getSize().y);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	Cube    cube;
	cube.set_vertex();


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

		DrawStuff(window,background);

		cube.follow_cursor(window);
		cube.render();

		DrawStuff(window,text);

		window->display();
	}

	glDeleteTextures(1, &texture);

	return EXIT_SUCCESS;
}
