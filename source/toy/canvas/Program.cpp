#include "toy/canvas/Program.hpp"
#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Factory.hpp"

namespace toy{
namespace canvas{

struct ProgramPrivate
{
	std::unique_ptr<toy::canvas::_detail::Program>   detail;
};

}}

using namespace toy;
using namespace canvas;

Program::Program(std::shared_ptr<Code> vs,std::shared_ptr<Code> fs):
	_this(new ProgramPrivate),
	_vertex(vs),
	_fragment(fs)
{
	_brush = vs->brush();

	if ( _brush != fs->brush() )
	{
		toy::Oops(TOY_MARK);
	}

	_this->detail.reset(_brush->_getFactory()->createProgram(vs,fs));
}

Program::~Program()
{
	this->disuse();
}

auto Program::brush()->std::shared_ptr<Brush>
{
	return _brush;
}

void Program::use()
{
	_brush->_useProgram(this);
}


void Program::disuse()
{
	if ( this->isUsed() )
	{
		_brush->_useProgram(nullptr);
	}
}

bool Program::isUsed()
{
	if ( _brush->_isSameProgram(this) )
	{
		return true;
	}
	return false;
}

auto Program::getVertexShader()->std::shared_ptr<Code>
{
	return _vertex;
}

auto Program::getFragmentShader()->std::shared_ptr<Code>
{
	return _fragment;
}

void Program::_use()
{
	_this->detail->use();
}

auto Program::_id()->uint32_t
{
	return _this->detail->getProgramID();
}
