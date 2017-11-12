
#include "toy/graph/Standard.hpp"
#include "toy/graph/Program.hpp"
#include "toy/graph/Uniform.hpp"

namespace toy{
namespace graph{
struct UniformBasePrivate
{
	GLint    location = 0;
};
}}

using namespace toy;
using namespace graph;

UniformBase::UniformBase(std::shared_ptr<Program> ptr,const std::string &name):
	_this(new UniformBasePrivate),
	_program(ptr)
{
	_this->location = glGetUniformLocation(_program->_id(), name.c_str());
}

UniformBase::~UniformBase()
{
	delete _this;
}

void Uniform1i::set(int x)
{
	if ( ! _program->isUsed() ) toy::Oops(TOY_MARK);
	glUniform1i(_this->location, x);
}

void Uniform2i::set(int x,int y)
{
	if ( ! _program->isUsed() ) toy::Oops(TOY_MARK);
	glUniform2i(_this->location, x,y);
}

void Uniform3i::set(int x,int y,int z)
{
	if ( ! _program->isUsed() ) toy::Oops(TOY_MARK);
	glUniform3i(_this->location, x,y,z);
}

void Uniform4i::set(int x,int y,int z,int w)
{
	if ( ! _program->isUsed() ) toy::Oops(TOY_MARK);
	glUniform4i(_this->location, x,y,z,w);
}

void Uniform1f::set(float x)
{
	if ( ! _program->isUsed() ) toy::Oops(TOY_MARK);
	glUniform1f(_this->location, x);
}

void Uniform2f::set(float x,float y)
{
	if ( ! _program->isUsed() ) toy::Oops(TOY_MARK);
	glUniform2f(_this->location, x,y);
}

void Uniform3f::set(float x,float y,float z)
{
	if ( ! _program->isUsed() ) toy::Oops(TOY_MARK);
	glUniform3f(_this->location, x,y,z);
}

void Uniform4f::set(float x,float y,float z,float w)
{
	if ( ! _program->isUsed() ) toy::Oops(TOY_MARK);
	glUniform4f(_this->location, x,y,z,w);
}
