#include "toy/graph/Program.hpp"
#include "toy/graph/Brush.hpp"
#include "toy/graph/Factory.hpp"

namespace toy{
namespace graph{

struct ProgramPrivate
{
	toy::graph::_detail::Program*   detail = nullptr;
};

}}

using namespace toy;
using namespace graph;

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

	_this->detail = _brush->_getFactory()->createProgram(vs,fs);
}

Program::~Program()
{
	this->disuse();

	delete _this->detail;
	delete _this;
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
