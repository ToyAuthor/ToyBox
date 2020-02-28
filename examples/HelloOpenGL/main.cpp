/*
 * It just a sample code for OpenGL developer.
 * And implement a trackball in OpenGL.
 */

//#include <glm/glm.hpp>            // If you need it.
#include <toy/canvas/OpenGL.hpp>    // Include OpenGL API
#include <toy/Canvas.hpp>
#include <toy_example/sfml/Window.hpp>
#include <toy_example/TrackballMatirx.hpp>

class MyTriangle
{
	public:

		MyTriangle()
		{
			const GLfloat vertexData[] = {
				-100.0f, -100.0f, 0.0f,
				 100.0f, -100.0f, 0.0f,
				 0.0f,   73.205f, 0.0f,
			};

			glGenBuffers(1, &_handle);
			glBindBuffer(GL_ARRAY_BUFFER, _handle);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		}

		~MyTriangle()
		{
			glDeleteBuffers(1, &_handle);
		}

		void render()
		{
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, _handle);

			glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDisableVertexAttribArray(0);
		}

	private:

		GLuint   _handle = 0;
};

static bool HandleEvent( std::shared_ptr<sf::Window> window, toy::example::TrackballMatirx *camera )
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

			case sf::Event::MouseButtonPressed:

				camera->setMousePosition(event.mouseButton.x, -event.mouseButton.y,true);
				break;

			case sf::Event::MouseButtonReleased:

				camera->setMousePosition(event.mouseButton.x, -event.mouseButton.y,false);
				break;

			case sf::Event::MouseMoved:
				camera->setMouseMovePosition(event.mouseMove.x, -event.mouseMove.y);
				break;

			default:
				break;
		}
	}

	return true;
}

static auto BuildShader(std::shared_ptr<toy::canvas::Brush> ogl)->std::shared_ptr<toy::canvas::Program>
{
	toy::Text  vertexCode(R"(
		void main()
		{
			gl_Position = ftransform();
		}
	)");

	toy::Text  fragmentCode(R"(
		void main()
		{
			gl_FragColor = vec4(1,0,0,0);
		}
	)");

	auto   vs = std::make_shared<toy::canvas::Code>(ogl,vertexCode,   toy::VERTEX_SHADER);
	auto   fs = std::make_shared<toy::canvas::Code>(ogl,fragmentCode, toy::FRAGMENT_SHADER);

	return std::make_shared<toy::canvas::Program>(vs,fs);
}

static void MainLoop(std::shared_ptr<sf::Window> window, toy::example::TrackballMatirx *camera)
{
	glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );

	MyTriangle   obj;

	while ( HandleEvent( window, camera ) && window->isOpen() )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glLoadMatrixf((const float*)(camera->projection().data));
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf((const float*)(camera->modelview().data));

		obj.render();
		window->display();
	}
}

static int main2()
{
	const uint32_t  width  = 800;
	const uint32_t  height = 600;

	auto   window = toy::example::CreateWindow("HelloOpenGL",width,height);
	auto   ogl    = std::make_shared<toy::canvas::Brush>();    // Init OpenGL

	window->setVerticalSyncEnabled(true);

	auto   program = BuildShader(ogl);
	program->use();

	glViewport(0,0,width,height);

	toy::example::TrackballMatirx    camera;

	camera.setScreenSize(width,height);

	MainLoop(window,&camera);

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
