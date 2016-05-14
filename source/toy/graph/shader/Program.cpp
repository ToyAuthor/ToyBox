#include "toy/graph/shader/Program.hpp"

using namespace toy;
using namespace graph;
using namespace shader;



Program::Program()
{
	;
}

Program::~Program()
{
	_vertex.drop();
	_fragment.drop();

	if ( _program )
	{
		glDeleteProgram(_program);
		_program=0;
	}
}

int Program::loadShader(const char *fileVertex,const char *fileFragment)
{
	_vertex.loadShader(fileVertex,GL_VERTEX_SHADER);
	_fragment.loadShader(fileFragment,GL_FRAGMENT_SHADER);

	return (int)1;
}

void Program::use()
{
	glUseProgram(_program);
}

void Program::create()
{
	_program = glCreateProgram();

	if ( _vertex.isExist() )
	{
		glAttachShader(_program, _vertex._shader);
	}

	if ( _fragment.isExist() )
	{
		glAttachShader(_program, _fragment._shader);
	}

	glLinkProgram(_program);
}
