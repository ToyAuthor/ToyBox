#include "toy/graph/detail/ProgramA.hpp"
#include "toy/graph/Code.hpp"

using namespace toy;
using namespace graph;
using namespace _detail;


ProgramA::ProgramA( std::shared_ptr<toy::graph::Code> vs,
		                        std::shared_ptr<toy::graph::Code> fs )
{
	_program = glCreateProgram();

	if ( vs->isExist() )
	{
		glAttachShader(_program, vs->_getShaderID());
	}
	else
	{
		toy::Oops(TOY_MARK);
	}

	if ( fs->isExist() )
	{
		glAttachShader(_program, fs->_getShaderID());
	}
	else
	{
		toy::Oops(TOY_MARK);
	}

	glLinkProgram(_program);
}

ProgramA::~ProgramA()
{
	if ( _program )
	{
		glDeleteProgram(_program);
		_program = 0;
	}
}

void ProgramA::use()
{
	glUseProgram(_program);
}

auto ProgramA::getProgramID()->uint32_t
{
	return _program;
}
