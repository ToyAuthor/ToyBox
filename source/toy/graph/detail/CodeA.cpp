#include "toy/graph/detail/CodeA.hpp"

static size_t GetFileSize(FILE *file)
{
	std::fseek(file, 0, SEEK_END);
	size_t  size = std::ftell(file);
	std::fseek(file, 0, SEEK_SET);
	return size;
}

class FileStream
{
	public:

		FileStream(){}
		~FileStream(){ release(); }

		int load(std::string filename)
		{
			release();

			#ifdef TOY_WINDOWS
				auto   wfilename = toy::utf::UTF8ToWChar(filename);
				auto   file = ::_wfopen(wfilename.c_str(), L"rb");
			#else
				auto   file = std::fopen(filename.c_str(), "rb");
			#endif

			if ( file==nullptr )
			{
				toy::Oops(TOY_MARK);
				toy::Logger<<"File not found:"<<filename<<toy::NextLine;
				return 0;
			}

			size_t  size = _size = GetFileSize(file);

			//------------------------------------------------------------------

			_buffer = new GLchar[size];

			if ( _buffer==nullptr )
			{
				toy::Oops(TOY_MARK);
				std::fclose(file);
				return 0;
			}

			//------------------------------------------------------------------

			size_t	result = std::fread(_buffer,1,size,file);

			if ( result!=size )
			{
				// Something wrong
				toy::Oops(TOY_MARK);
			}

			std::fclose(file);

			return 1;
		}

		const GLchar* data()
		{
			return _buffer;
		}

		GLint size()
		{
			return _size;
		}

	private:

		void release()
		{
			if ( _buffer!=nullptr )
			{
				delete [] _buffer;
				_buffer = nullptr;
			}
		}

		GLchar*   _buffer = nullptr;
		GLint	  _size = 0;
};

static bool CompileShader( GLuint shader, const GLchar* str, GLint size )
{
	const GLchar** data = &str;

	glShaderSource(shader, 1, data, &size);
	glCompileShader(shader);

	GLint	result;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if ( GL_TRUE!=result )
	{
		GLchar		message[2048];
		GLsizei		msgLen = 1023;

		glGetShaderInfoLog(shader, size, &msgLen, message);
		toy::Oops(TOY_MARK);
		toy::Log("%s\n", message);

		return false;
	}

	return true;
}

static bool LoadShaderFile(GLuint *shader,std::string filename, GLenum type)
{
	*shader = glCreateShader(type);

	FileStream		stream;

	if ( !stream.load(filename) )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	if ( ! CompileShader( *shader, stream.data(), stream.size() ) )
	{
		toy::Log("%s compile error\n", filename.c_str());
		return false;
	}

	return true;
}

static bool LoadShaderCode(GLuint *shader,toy::Text &code, GLenum type)
{
	*shader = glCreateShader(type);

	bool  result = true;

	if ( ! CompileShader( *shader, code.c_str(), code.size() ) )
	{
		toy::Oops(TOY_MARK);
		result = false;
	}

	return result;
}

using namespace toy;
using namespace graph;
using namespace _detail;

CodeA::CodeA(std::string filename, enum toy::Option ttype)
{
	GLenum   type = ttype==toy::VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

	if ( false == LoadShaderFile( &_shaderID, filename, type ) )
	{
		this->drop();
	}
}

CodeA::CodeA(toy::Text &code, enum toy::Option ttype)
{
	GLenum   type = ttype==toy::VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

	if ( false == LoadShaderCode( &_shaderID, code, type ) )
	{
		this->drop();
	}
}

CodeA::~CodeA()
{
	this->drop();
}

bool CodeA::isExist()
{
	return _shaderID==0 ?false:true;
}

void CodeA::drop()
{
	if ( _shaderID )
	{
		glDeleteShader(_shaderID);
		_shaderID = 0;
	}
}

uint32_t CodeA::getShaderID()
{
	return _shaderID;
}
