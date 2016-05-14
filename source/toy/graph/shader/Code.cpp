#include "toy/graph/shader/Code.hpp"

using namespace toy;
using namespace graph;
using namespace shader;


class FileStream
{
	public:

		FileStream(){}
		~FileStream(){release();}

		int	load(std::string filename)
		{
			FILE	*file = fopen(filename.c_str(), "rb");

			if ( file==nullptr )
			{
				toy::Oops(TOY_MARK);
				return 0;
			}

			size_t		file_size = 0;

			fseek(file, 0, SEEK_END);
			_size = file_size = ftell(file);
			fseek(file, 0, SEEK_SET);

			_buffer = new GLchar[file_size];

			if ( _buffer==nullptr )
			{
				fclose(file);
				return 0;
			}

			size_t	result;

			result = fread(_buffer,1,file_size,file);

			if ( result!=file_size )
			{
				// Something wrong
				toy::Oops(TOY_MARK);
			}

			fclose(file);

			return 1;
		}

		void	release()
		{
			if ( _buffer!=nullptr )
			{
				delete [] _buffer;
				_buffer = nullptr;
			}
		}

		GLchar		*_buffer = nullptr;
		GLint	    _size = 0;
};

Code::Code()
{
	;
}

Code::~Code()
{
	drop();
}

void Code::drop()
{
	if ( _shader )
	{
		glDeleteShader(_shader);
		_shader=0;
	}
}

int Code::isExist()
{
	return _shader==0 ?0:1;
}

int Code::loadShader(std::string filename, GLenum type)
{
	_shader = glCreateShader(type);

	FileStream		stream;

	if ( !stream.load(filename) )
	{
		toy::Oops(TOY_MARK);
		return 0;
	}

	GLint	size = stream._size;

	glShaderSource(_shader, 1, &(stream._buffer), &size);
	glCompileShader(_shader);

	GLint	result;

	// Checkout GLSL.
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &result);

	if ( GL_TRUE!=result )
	{
		GLchar		message[2048];
		GLsizei		msgLen = 1023;

		glGetShaderInfoLog(_shader, size, &msgLen, message);

		toy::Log("%s compile error\n", filename.c_str());
		toy::Log("%s\n", message);

		glDeleteShader(_shader);
		_shader = 0;
		return 0;
	}

	return 1;
}
